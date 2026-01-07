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