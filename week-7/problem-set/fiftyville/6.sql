SELECT account_number,
    transaction_type
FROM atm_transactions
WHERE year = 2025
    AND month = 7
    AND day = 28
    AND atm_location = 'Leggett Street'