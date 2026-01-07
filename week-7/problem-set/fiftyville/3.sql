SELECT people.*,
    bakery_security_logs.minute
FROM people
    JOIN bakery_security_logs on people.license_plate = bakery_security_logs.license_plate
WHERE year = 2025
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute >= 15
    AND minute <= 35