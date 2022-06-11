-- QUERY 1: GET THE CRIME REPORT OF THE SPECIFIED DAY
--
-- Let's start with what we know, the date of the crime:
-- July 28, 2021 and took place on Humphrey Street.
-- So let's query for the crime reports on that specific date.
SELECT
    description
FROM
    crime_scene_reports
WHERE
    year = 2021 AND
    month = 7 AND
    day = 28 AND
    Street = "Humphrey Street";
-- RESULTS
-- - Theft took place at 10:15am at the Humphrey Street bakery.
-- - 3 witnesses.
-- - Bakery.
-- POSSIBLE ACTIONS
-- > Look for the interviews in the <interviews> table.




-- QUERY 2: READ THE INTERVIEWS TO THE WITNESSES
-- Now we need to get the names and the testimonials of the
-- witnesses in order to get more information about the crime.
SELECT
    name, transcript
FROM
    interviews
WHERE
    year = 2021 AND
    month = 7 AND
    day = 28;
-- RESULTS
-- - [Ruth] 
--   - Within 10 minutes of the theft, the robber drove away
--     with a car parked in the bakery parking lot.
--   > SEARCH IN bakery_securty_logs TABLE.
-- - [Eugene] 
--   - The robber was using the ATM on Legget Street
--     before entering at Emma's bakery.
--   > QUERY IN atm_transactions TABLE.
-- - [Raymond] 
--   - The thief called someone as he was leaving.
--   - The call lasted less than a minute.
--   - He was planning to take the earliest flight out of Fiftyville
--     of the next day.
--   - The thief has an accomplice.
--   - The accomplice will purchase the flight tickets.
--   > SEARCH IN phone_calls TABLE.




-- QUERY 3: GET THE INFO ABOUT THE CAR USED TO GET AWAY.
-- Let's use the bakery_security_logs to get the plates of the
-- alleged robber.
-- In specific, search for the 10 minutes within the theft, that means
-- within 10:15am and 10:25am
SELECT
    hour, minute, activity, license_plate
FROM
    bakery_security_logs
WHERE
    year = 2021 AND
    month = 7 AND
    day = 28 AND
    hour = 10 AND
    minute >= 5 AND
    minute <= 25;
-- RESULTS:
-- - 8 cars left the parking lot within the 10 minutes interval.
-- - 8 plates obtained.




-- QUERY 4: INVESTIGATE THE ATM TRANSACTIONS MINUTES BEFORE THE THEFT
-- Search for the transactions made on the ATM located at Legget Street
-- the day of the theft (July 28).
-- Get the account number, the transcription_type and the amount.
SELECT
    account_number, transaction_type, amount
FROM
    atm_transactions
WHERE
    year = 2021 AND
    month = 7 AND
    day = 28 AND
    atm_location = "Leggett Street";
-- RESULTS:
-- - 9 account numbers obtained from the people who used
--   the ATM on July 28 on Leggett Street.
-- - 8 withdraws, 1 deposit.




-- QUERY 5: LOOK FOR RELATED PHONECALLS
-- Look for phone-calls made on July 28 that lasted less than a minute.
-- Get the caller and the receiver number. Also get the duration.
SELECT
    caller, receiver, duration
FROM
    phone_calls
WHERE
    year = 2021 AND
    month = 7 AND
    day = 28 AND
    duration < 60;




-- QUERY 6:
-- Now that I have got enough information, can start to match with
-- the information available of the bank and the people's name
-- using the bank account to find possible suspects of the theft.
SELECT
    people.name,
    bank_accounts.account_number,
    people.phone_number,
    people.license_plate
FROM
    people
    JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE
    account_number IN (
        SELECT
            account_number
        FROM
            atm_transactions
        WHERE
            year = 2021 AND
            month = 7 AND
            day = 28 AND
            atm_location = "Leggett Street"
    ) AND
    license_plate IN (
        SELECT
            license_plate
        FROM
            bakery_security_logs
        WHERE
            year = 2021 AND
            month = 7 AND
            day = 28 AND
            hour = 10 AND
            minute >= 5 AND
            minute <= 25
    );
-- RESULTS:
-- - 4 suspects found
-- +-------+----------------+----------------+---------------+
-- | name  | account_number |  phone_number  | license_plate |
-- +-------+----------------+----------------+---------------+
-- | Bruce | 49610011       | (367) 555-5533 | 94KL13X       |
-- | Diana | 26013199       | (770) 555-1861 | 322W7JE       |
-- | Iman  | 25506511       | (829) 555-5269 | L93JTIZ       |
-- | Luca  | 28500762       | (389) 555-5198 | 4328GD8       |
-- +-------+----------------+----------------+---------------+
--
-- > Compare with phone numbers to find the thieves.




-- QUERY 7:
-- Given the 4 suspects, this list can be narrowed down campring with
-- phone numbers gotten in QUERY 5.
SELECT
    caller, receiver
FROM
    phone_calls
WHERE
    year = 2021 AND
    month = 7 AND
    day = 28 AND
    duration < 60 AND
    caller IN (
        SELECT
            people.phone_number
        FROM
            people
            JOIN bank_accounts ON people.id = bank_accounts.person_id
        WHERE
            account_number IN (
                SELECT
                    account_number
                FROM
                    atm_transactions
                WHERE
                    year = 2021 AND
                    month = 7 AND
                    day = 28 AND
                    atm_location = "Leggett Street"
            ) AND
            license_plate IN (
                SELECT
                    license_plate
                FROM
                    bakery_security_logs
                WHERE
                    year = 2021 AND
                    month = 7 AND
                    day = 28 AND
                    hour = 10 AND
                    minute >= 15 AND
                    minute <= 25
            )
    );
-- RESULTS:
-- - We got 2 possible thieves and 2 possible accomplices.
-- +----------------+----------------+
-- |     caller     |    receiver    |
-- +----------------+----------------+
-- | (367) 555-5533 | (375) 555-8161 |
-- | (770) 555-1861 | (725) 555-3243 |
-- +----------------+----------------+




-- QUERY 8:
-- Now we just need to campare those phone numbers with the people data.
-- With this we will get the name of the 2 suspect thieves and the
-- 2 suspect accomplices.
SELECT
    name,
    phone_number,
    passport_number,
    license_plate
FROM
    people
WHERE
    phone_number IN (
        "(367) 555-5533",
        "(375) 555-8161",
        "(770) 555-1861",
        "(725) 555-3243"
    );
-- RESULT:
-- Suspect thieves' names.
-- - Diana 
-- - Bruce.
-- Suspect accomplices' names:
-- - Philip and Robin.
-- 
-- +--------+----------------+-----------------+---------------+
-- |  name  |  phone_number  | passport_number | license_plate |
-- +--------+----------------+-----------------+---------------+
-- | Diana  | (770) 555-1861 | 3592750733      | 322W7JE       |
-- | Bruce  | (367) 555-5533 | 5773159633      | 94KL13X       |
-- | Philip | (725) 555-3243 | 3391710505      | GW362R6       |
-- | Robin  | (375) 555-8161 |                 | 4V16VO0       |
-- +--------+----------------+-----------------+---------------+


-- QUERY 9:
-- We have to find the 2 suspects, the thief and the accomplice.
-- To discard the other 2, we need to find to keep looking for evidence
-- this comes from the QUERY 2, from what Raymand said, he was going
-- to buy a flight to the next day, July 29. So let's check all flights
-- planned to take off on July 29, and match this with suspects data like 
-- passport number.
-- The earliest flight should be the thief.
SELECT
    passengers.passport_number,
    origin_airport_id,
    destination_airport_id,
    flight.hour,
    flight.minute
FROM
    passengers
    JOIN flights ON passengers.flight_id = flights.id
    JOIN airports ON flights.origin_airport_id = airports.id
WHERE
    flights.year = 2021 AND
    flights.month = 7 AND
    flights.day = 29 AND
    passengers.passport_number IN (
        3592750733,
        5773159633,
        3391710505
    );
-- RESULTS:
-- After this search, 2 suspects took a flight on July 29,
-- but as our witness Raymond said in his testimony, the thief's
-- plan was to take the earliest flight, the earliest flight
-- from Fiftiville airport was at 8:20 so, based on that
-- conclussion, the thief is the user with the passport's number:
-- 5773159633
-- And the accomplice is the person who received his call just after the
-- theft.

-- QUERY 10:
-- The name of the thief is...
SELECT
    name,
    phone_number
FROM
    people
WHERE
    passport_number = 5773159633;
-- RESULTS:
-- The thief is Bruce and his phone number is (367) 555-5533



-- QUERY 11:
-- The accomplice is the person who receved the call from the
-- phone number of Bruce just after the theft. Based on Query 7
-- the accomplice has the phone number: (375) 555-8161. And his
-- name is...
SELECT
    name,
    phone_number
FROM
    people
WHERE
    phone_number = "(375) 555-8161";
-- RESULTS:
-- The accomplice name is: Robin.
-- This corresponds with a "manual search" among our last results,




-- QUERY 12:
-- Finally, based on Query 9, the suspect took a flight
-- with destination to the airport with id = 4
-- that corresponds to...
SELECT
    abbreviation,
    full_name,
    city
FROM
    airports
WHERE
    id = 4;
-- RESULTS:
-- The thief escaped to New York City.
-- 
-- LGA|LaGuardia Airport|New York City
