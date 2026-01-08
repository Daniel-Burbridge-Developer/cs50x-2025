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
LIMIT 1