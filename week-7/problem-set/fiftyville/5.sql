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
    )