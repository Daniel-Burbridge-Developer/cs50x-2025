import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session.get("user_id")
    user_transactions = db.execute(
        "SELECT * FROM transactions WHERE user_id = ?", user_id
    )
    user = db.execute("SELECT * FROM users WHERE id = ?", user_id)[0]

    unique_symbols = {t["symbol"] for t in user_transactions}
    stock_market = {}

    for symbol in unique_symbols:
        curstock = lookup(symbol)
        if symbol in stock_market:
            stock_market[symbol]["price"] = curstock["price"]
            stock_market[symbol]["name"] = curstock["name"]
        else:
            stock_market[symbol] = {
                "price": curstock["price"],
                "name": curstock["name"],
            }
    user_stocks = {}

    for transaction in user_transactions:
        symbol = transaction["symbol"]
        name = stock_market[symbol]["name"]
        price = stock_market[symbol]["price"]
        shares = transaction["shares"]

        if symbol in user_stocks:
            user_stocks[symbol]["holdings"] += shares
            user_stocks[symbol]["total"] = user_stocks[symbol]["holdings"] * price
        else:
            user_stocks[symbol] = {
                "name": name,
                "holdings": shares,
                "price": price,
                "total": shares * price,
            }

    sum = 0
    for name in user_stocks:
        sum += user_stocks[name]["total"]

    total_valuation = sum + user["cash"]

    return render_template(
        "index.html", user_stocks=user_stocks, user=user, pvalue=total_valuation
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        if not symbol:
            return apology("must provide a stock symbol", 403)
        if not shares:
            return apology("must provide amount of shares to buy", 403)
        if int(shares) < 1:
            return apology("shares to buy must be a postive number")
        resp = lookup(symbol)
        if not resp:
            return apology(
                "Error fetching stock, are you sure it's a valid symbol?", 403
            )

        user = session.get("user_id")
        userFundsRow = db.execute("SELECT cash FROM users WHERE id = ?", user)
        userFunds = userFundsRow[0]["cash"]
        stockCost = resp["price"]
        stockSymbol = resp["symbol"]

        transactionCost = float(stockCost) * int(shares)

        if transactionCost > float(userFunds):
            return apology(
                f"You do not have enough funds to make this transaction, transaction cost {usd(transactionCost)}"
            )

        db.execute(
            "UPDATE users SET cash = cash - ? WHERE id = ?", transactionCost, user
        )

        db.execute(
            "INSERT into transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
            user,
            stockSymbol,
            shares,
            stockCost,
        )

        return redirect("/")
    else:
        return render_template("/buy.html")


@app.route("/history")
@login_required
def history():
    user = session.get("user_id")
    transactions = db.execute(
        "SELECT * FROM transactions WHERE user_id = ? ORDER BY timestamp DESC", user
    )

    return render_template("/history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("must provide a stock symbol", 403)

        resp = lookup(symbol)

        if not resp:
            return apology(
                "Error fetching stock, are you sure it's a valid symbol?", 403
            )

        return render_template("quoted.html", data=resp)
    else:
        return render_template("/quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        name = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        if not name:
            return apology("must provide username", 403)
        elif not password:
            return apology("must provide password", 403)
        elif not confirmation:
            return apology("please confirm password", 403)
        elif not (password == confirmation):
            return apology("password and confirmation does not match", 403)

        try:
            id = db.execute(
                "INSERT INTO users (username, hash) VALUES(?, ?)",
                name,
                generate_password_hash(password),
            )
            session["user_id"] = id
        except ValueError:
            return apology("user already exists", 403)

        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        symbol = lookup(symbol)["symbol"]

        if not symbol:
            return apology("must provide a stock symbol", 403)
        if not shares:
            return apology("must provide amount of shares to sell", 403)
        if int(shares) < 1:
            return apology("shares to sell must be a postive number")
        resp = lookup(symbol)
        if not resp:
            return apology(
                "Error fetching stock, are you sure it's a valid symbol?", 403
            )

        user = session.get("user_id")
        ## Check if user owns this stock, if they do not - return apology.
        ## HERE DOWN IS JUST A COPY OF BUY -> PROBS NEED DELETE MOST, GOING TO INDEX FOR NOW

        stockcount = db.execute(
            "SELECT SUM(shares) AS shareCount FROM transactions WHERE symbol = ? AND user_id = ?",
            symbol,
            user,
        )[0]["shareCount"]

        if not stockcount:
            return apology(
                "Sorry, you don't have that stock! ... not sure how that hapened"
            )

        if int(shares) <= 0:
            return apology("Must be a positive number")

        if int(stockcount) < int(shares):
            return apology(f"You don't have that many shares! You have {stockcount}")

        stockCost = resp["price"]
        stockSymbol = resp["symbol"]

        transactionProfit = float(stockCost) * (int(shares))

        db.execute(
            "UPDATE users SET cash = cash + ? WHERE id = ?", transactionProfit, user
        )

        db.execute(
            "INSERT into transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
            user,
            stockSymbol,
            int(shares) * -1,
            stockCost,
        )

        return redirect("/")
    else:
        user_id = session.get("user_id")

        user_transactions = db.execute(
            "SELECT * FROM transactions WHERE user_id = ?", user_id
        )

        unique_symbols = {t["symbol"] for t in user_transactions}

        return render_template("/sell.html", symbols=unique_symbols)
