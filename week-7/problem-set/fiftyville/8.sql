SELECT *
FROM flights
    JOIN airports ON flights.origin_airport_id = airports.id
WHERE airports.city = 'Fiftyville'
    and