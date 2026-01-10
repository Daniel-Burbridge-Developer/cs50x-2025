-- Keep a log of any SQL queries you execute as you solve the mystery.
-- We know the day and location of the crime as a starting point, ensuring to grab ID incase needed later.
-- The crime_scene_reports take this information & will hopefully give the next clue
SELECT id,
    description
FROM crime_scene_reports
WHERE year = 2025
    AND month = 7
    AND day = 28
    AND street = 'Humphrey Street' -- 295|Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. 
    -- Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.
    -- We now know the time & location of the robery. 
    -- We also know there are transcripts. At this point in time we will begin with the security logs as we already have the summary of their interviews may look at interviews if security footage isn't fruitful.
SELECT id,
    activity,
    license_plate
FROM bakery_security_logs
WHERE year = 2025
    AND month = 7
    AND day = 28
    AND hour = 10 -- Some cars entered right before 10:15, but I don't see them leaving, so I'm more interested in the car that left at 16 minutes, and maybe the next couple entries as well. 
    -- 258|entrance|R3G7486|8
    -- 259|entrance|13FNH73|14
    -- 260|exit|5P2BI95|16
    -- 261|exit|94KL13X|18
    -- 262|exit|6P58WS2|18
    -- 263|exit|4328GD8|19
    -- 264|exit|G412CB7|20
    -- 265|exit|L93JTIZ|21
    -- 266|exit|322W7JE|23
    -- 267|exit|0NTHK55|23
    -- 268|exit|1106N58|35
    -- 269|entrance|NRYN856|42
    -- 270|entrance|WD5M8I6|44
    -- 271|entrance|V47T75I|55
SELECT people.*,
    bakery_security_logs.minute
FROM people
    JOIN bakery_security_logs on people.license_plate = bakery_security_logs.license_plate
WHERE year = 2025
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute >= 15
    AND minute <= 35 -- Okay, I have the names now.
    -- 221103|Vanessa|(725) 555-4692|2963008352|5P2BI95|16
    -- 686048|Bruce|(367) 555-5533|5773159633|94KL13X|18
    -- 243696|Barry|(301) 555-4174|7526138472|6P58WS2|18
    -- 467400|Luca|(389) 555-5198|8496433585|4328GD8|19
    -- 398010|Sofia|(130) 555-0289|1695452385|G412CB7|20
    -- 396669|Iman|(829) 555-5269|7049073643|L93JTIZ|21
    -- 514354|Diana|(770) 555-1861|3592750733|322W7JE|23
    -- 560886|Kelsey|(499) 555-9472|8294398571|0NTHK55|23
    -- 449774|Taylor|(286) 555-6063|1988161715|1106N58|35
    -- I think I'm on the correct track, but I'm just gonna take a quick look at the interviews. 
SELECT *
FROM interviews
WHERE year = 2025
    AND month = 7
    AND day = 28 -- Got some good info and more leads! can narrow it down.
    -- 161|Ruth|2025|7|28|Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
    -- 162|Eugene|2025|7|28|I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
    -- 163|Raymond|2025|7|28|As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.
    -- Less then 10 minutes. 
    -- ATM prior to bakery same morning. ATM on leggett Street. (before 10:15). Withdrawal.
    -- Under 60s phone call. just prior to leaving (10m)
    -- earliest flight out of Fiftyville tomorrow (month 7, day 29). --- Unsure about this next part being useful? The thief then asked the person on the other end of the phone to purchase the flight ticket.
SELECT caller
FROM phone_calls
WHERE year = 2025
    AND month = 7
    AND day = 28
    AND duration < 60
    AND caller IN (
        SELECT phone_number
        FROM people
            JOIN bakery_security_logs on people.license_plate = bakery_security_logs.license_plate
        WHERE year = 2025
            AND month = 7
            AND day = 28
            AND hour = 10
            AND minute >= 15
            AND minute <= 35
    ) -- Narrows down even further.
    -- (130) 555-0289
    -- (499) 555-9472
    -- (367) 555-5533
    -- (499) 555-9472
    -- (286) 555-6063
    -- (770) 555-1861
SELECT account_number,
    transaction_type
FROM atm_transactions
WHERE year = 2025
    AND month = 7
    AND day = 28
    AND atm_location = 'Leggett Street' -- okay, so "transaction type" is listed as withdraw or deposit
    -- 'withdraw'
SELECT person_id
FROM bank_accounts
WHERE account_number IN (
        SELECT account_number
        FROM atm_transactions
        WHERE year = 2025
            AND month = 7
            AND day = 28
            AND atm_location = 'Leggett Street' -- okay, so "transaction type" is listed as withdraw or deposit
            AND transaction_type = 'withdraw'
    )
    AND person_id IN (
        SELECT people.id
        FROM people
            JOIN bakery_security_logs on people.license_plate = bakery_security_logs.license_plate
            JOIN phone_calls on phone_calls.caller = people.phone_number
        WHERE bakery_security_logs.year = 2025
            AND bakery_security_logs.month = 7
            AND bakery_security_logs.day = 28
            AND hour = 10
            AND minute >= 15
            AND minute <= 35
            AND duration < 60
    ) -- Down to 3 results! (the people who had a less than 60s phone call, and withdrew money on 2025-07-28)
    -- 686048
    -- 514354
    -- 449774
    -- Let's find out a little about the flight data. First flight
SELECT *
FROM flights
    JOIN airports ON flights.origin_airport_id = airports.id
    JOIN passengers ON flights.id = passengers.flight_id
    JOIN people ON passengers.passport_number = people.passport_number
WHERE airports.city = 'Fiftyville'
    AND year = 2025
    AND month = 7
    AND day = 29
    AND people.id IN (
        SELECT person_id
        FROM bank_accounts
        WHERE account_number IN (
                SELECT account_number
                FROM atm_transactions
                WHERE year = 2025
                    AND month = 7
                    AND day = 28
                    AND atm_location = 'Leggett Street' -- okay, so "transaction type" is listed as withdraw or deposit
                    AND transaction_type = 'withdraw'
            )
            AND person_id IN (
                SELECT people.id
                FROM people
                    JOIN bakery_security_logs on people.license_plate = bakery_security_logs.license_plate
                    JOIN phone_calls on phone_calls.caller = people.phone_number
                WHERE bakery_security_logs.year = 2025
                    AND bakery_security_logs.month = 7
                    AND bakery_security_logs.day = 28
                    AND hour = 10
                    AND minute >= 15
                    AND minute <= 35
                    AND duration < 60
            )
    )
ORDER BY minute ASC
LIMIT 1 -- 18|8|6|2025|7|29|16|0|8|CSF|Fiftyville Regional Airport|Fiftyville|18|3592750733|4C|514354|Diana|(770) 555-1861|3592750733|322W7JE
    -- Found you Diana! destination airport is airport with id of 6, let's grab that quickly. 
SELECT full_name
FROM airports
WHERE id = 6 -- Logan International Airport
    -- Since we know the theif is Diana, we can check her calls from the day.
SELECT name
FROM people
WHERE phone_number IN (
        SELECT receiver
        FROM phone_calls
            JOIN people ON people.phone_number = phone_calls.caller
        WHERE people.name = 'Diana'
            AND phone_calls.year = 2025
            AND phone_calls.month = 7
            AND phone_calls.day = 28
            AND phone_calls.duration < 60
    ) -- Found Philip! ...
    -- Oops, I didn't think this through. Logan is an airport, Not a City.
SELECT city
FROM airports
WHERE full_name = "Logan International Airport" -- Boston!
    -- Well, I would have arrested the wrong person.... Back to the drawing board....
    -- OKAY, I see where I went wrong, I was only considering the minute, and not the hour. 
SELECT flights.id,
    flights.hour,
    flights.minute,
    people.name
FROM flights
    JOIN airports ON flights.origin_airport_id = airports.id
    JOIN passengers ON flights.id = passengers.flight_id
    JOIN people ON passengers.passport_number = people.passport_number
WHERE airports.city = 'Fiftyville'
    AND year = 2025
    AND month = 7
    AND day = 29
    AND people.id IN (
        SELECT person_id
        FROM bank_accounts
        WHERE account_number IN (
                SELECT account_number
                FROM atm_transactions
                WHERE year = 2025
                    AND month = 7
                    AND day = 28
                    AND atm_location = 'Leggett Street' -- okay, so "transaction type" is listed as withdraw or deposit
                    AND transaction_type = 'withdraw'
            )
            AND person_id IN (
                SELECT people.id
                FROM people
                    JOIN bakery_security_logs on people.license_plate = bakery_security_logs.license_plate
                    JOIN phone_calls on phone_calls.caller = people.phone_number
                WHERE bakery_security_logs.year = 2025
                    AND bakery_security_logs.month = 7
                    AND bakery_security_logs.day = 28
                    AND hour = 10
                    AND minute >= 15
                    AND minute <= 35
                    AND duration < 60
            )
    )
ORDER BY hour,
    minute ASC -- Now to Decide between Bruce and Taylor.
    --     36|8|20|Bruce
    -- 36|8|20|Taylor
    -- 18|16|0|Diana
    -- I can tighten the window based on the interview of "within 10 minutes"
SELECT flights.id,
    flights.hour,
    flights.minute,
    people.name,
    airports.city,
    people.phone_number
FROM flights
    JOIN airports ON flights.origin_airport_id = airports.id
    JOIN passengers ON flights.id = passengers.flight_id
    JOIN people ON passengers.passport_number = people.passport_number
WHERE airports.city = 'Fiftyville'
    AND year = 2025
    AND month = 7
    AND day = 29
    AND people.id IN (
        SELECT person_id
        FROM bank_accounts
        WHERE account_number IN (
                SELECT account_number
                FROM atm_transactions
                WHERE year = 2025
                    AND month = 7
                    AND day = 28
                    AND atm_location = 'Leggett Street' -- okay, so "transaction type" is listed as withdraw or deposit
                    AND transaction_type = 'withdraw'
            )
            AND person_id IN (
                SELECT people.id
                FROM people
                    JOIN bakery_security_logs on people.license_plate = bakery_security_logs.license_plate
                    JOIN phone_calls on phone_calls.caller = people.phone_number
                WHERE bakery_security_logs.year = 2025
                    AND bakery_security_logs.month = 7
                    AND bakery_security_logs.day = 28
                    AND hour = 10
                    AND minute >= 15
                    AND minute <= 25
                    AND duration < 60
            )
    )
ORDER BY hour,
    minute ASC -- Got you Bruce! And the rest should be pretty easy.... 
    -- just redoing what I did for Diana, but with the correct flight and call IDs.
SELECT flights.id,
    flights.hour,
    flights.minute,
    people.name,
    flights.destination_airport_id,
    people.phone_number
FROM flights
    JOIN airports ON flights.origin_airport_id = airports.id
    JOIN passengers ON flights.id = passengers.flight_id
    JOIN people ON passengers.passport_number = people.passport_number
WHERE airports.city = 'Fiftyville'
    AND year = 2025
    AND month = 7
    AND day = 29
    AND people.id IN (
        SELECT person_id
        FROM bank_accounts
        WHERE account_number IN (
                SELECT account_number
                FROM atm_transactions
                WHERE year = 2025
                    AND month = 7
                    AND day = 28
                    AND atm_location = 'Leggett Street' -- okay, so "transaction type" is listed as withdraw or deposit
                    AND transaction_type = 'withdraw'
            )
            AND person_id IN (
                SELECT people.id
                FROM people
                    JOIN bakery_security_logs on people.license_plate = bakery_security_logs.license_plate
                    JOIN phone_calls on phone_calls.caller = people.phone_number
                WHERE bakery_security_logs.year = 2025
                    AND bakery_security_logs.month = 7
                    AND bakery_security_logs.day = 28
                    AND hour = 10
                    AND minute >= 15
                    AND minute <= 25
                    AND duration < 60
            )
    )
ORDER BY hour,
    minute ASC -- Got you Bruce! And the rest should be pretty easy.... just redoing what I did for Diana, but with the correct flight and call IDs.
    -- 36|8|20|Bruce|4|(367) 555 -5533 
    -- 18|16|0|Diana|6|(770) 555-1861
SELECT city
FROM airports
WHERE id = 4 -- New York City
    -- And lastly, who did Bruce call?
SELECT name
FROM people
WHERE phone_number IN (
        SELECT receiver
        FROM phone_calls
            JOIN people ON people.phone_number = phone_calls.caller
        WHERE people.name = 'Bruce'
            AND phone_calls.year = 2025
            AND phone_calls.month = 7
            AND phone_calls.day = 28
            AND phone_calls.duration < 60
    ) -- Robin