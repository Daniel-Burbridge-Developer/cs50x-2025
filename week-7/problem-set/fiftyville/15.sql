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
    )