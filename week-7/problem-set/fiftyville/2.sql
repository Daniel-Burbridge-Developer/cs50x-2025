SELECT id,
    activity,
    license_plate,
    minute
FROM bakery_security_logs
WHERE year = 2025
    AND month = 7
    AND day = 28
    AND hour = 10