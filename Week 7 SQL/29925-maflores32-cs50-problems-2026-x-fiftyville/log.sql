-- Keep a log of any SQL queries you execute as you solve the mystery.

-- First: Look for the crime report from July 28th on Humphrey Street
SELECT * FROM crime_scene_reports
WHERE month = 7 AND day = 28
AND street = 'Humphrey Street';

-- Second: Check witness interviews from July 28th that mention the bakery
SELECT * FROM interviews
WHERE month = 7 AND day = 28
AND transcript LIKE '%bakery%';

-- Third: Follow Ruth's clue - check bakery security logs between 10:15-10:25am
SELECT * FROM bakery_security_logs
WHERE month = 7 AND day = 28
AND hour = 10
AND minute BETWEEN 15 AND 25
AND activity = 'exit';

-- Fourth: Follow Eugene's clue - check ATM withdrawals on Leggett Street on July 28th
SELECT * FROM atm_transactions
WHERE month = 7 AND day = 28
AND atm_location = 'Leggett Street'
AND transaction_type = 'withdraw';

-- Fifth: Follow Raymond's first clue - check phone calls on July 28th that lasted less than 60 seconds
SELECT * FROM phone_calls
WHERE month = 7 AND day = 28
AND duration < 60;

-- Sixth: Follow Raymond's second clue - check earliest flight on July 29th from Fiftyville
SELECT f.*, a_origin.city AS origin_city, a_dest.city AS destination_city
FROM flights f
JOIN airports a_origin ON f.origin_airport_id = a_origin.id
JOIN airports a_dest ON f.destination_airport_id = a_dest.id
WHERE f.month = 7 AND f.day = 29
AND a_origin.city = 'Fiftyville'
ORDER BY f.hour, f.minute
LIMIT 1;

-- Seventh: Combine all clues

SELECT p.name, p.phone_number, p.passport_number, p.license_plate
FROM people p
-- Check bakery security logs (Ruth's clue)
JOIN bakery_security_logs bsl ON p.license_plate = bsl.license_plate
AND bsl.month = 7 AND bsl.day = 28 AND bsl.hour = 10 AND bsl.minute BETWEEN 15 AND 25 AND bsl.activity = 'exit'
-- Check ATM withdrawals (Eugene's clue)
JOIN bank_accounts ba ON p.id = ba.person_id
JOIN atm_transactions atm ON ba.account_number = atm.account_number
AND atm.month = 7 AND atm.day = 28 AND atm.atm_location = 'Leggett Street' AND atm.transaction_type = 'withdraw'
-- Check phone calls (Raymond's first clue)
JOIN phone_calls pc ON p.phone_number = pc.caller
AND pc.month = 7 AND pc.day = 28 AND pc.duration < 60
-- Check flight (Raymond's second clue)
JOIN passengers ps ON p.passport_number = ps.passport_number
WHERE ps.flight_id = 36;  -- Flight ID 36 is the earliest flight to NYC

-- Eighth: Find the accomplice 
SELECT p.name, p.phone_number, p.passport_number
FROM people p
JOIN phone_calls pc ON p.phone_number = pc.receiver
WHERE pc.caller = '(367) 555-5533'
AND pc.month = 7 AND pc.day = 28
AND pc.duration < 60;

-- Ninth: Verify flight details and city
SELECT a.full_name, a.city
FROM airports a
JOIN flights f ON a.id = f.destination_airport_id
WHERE f.id = 36;
