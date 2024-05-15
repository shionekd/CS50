-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Check the crime details for the Problem
SELECT * FROM crime_scene_reports WHERE year = 2023 AND month = 7 AND day = 28 AND street = 'Humphrey Street';


-- CHeck the witnesses report From interviews table
SELECT * FROM interviews WHERE transcript LIKE '%bakery%' AND year = 2023 AND month = 7 AND day = 28;
/*
each of their interview transcripts mentions the bakery
id:161, 162, 163
*/

/*
Details from id: 161
Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
Check the security logs
*/
SELECT name FROM people JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25;
-- SELECT name FROM bakery_security_logs JOIN people ON bakery_security_logs.license_plate = people.license_plate WHERE year = 2023 AND month = 7 AND day = 28 AND activity = 'exit' AND hour = 10 AND minute BETWEEN 15 AND 25;
/*
+---------+
|  name   |
+---------+
| Vanessa |
| Bruce   |
| Barry   |
| Luca    |
| Sofia   |
| Iman    |
| Diana   |
| Kelsey  |
+---------+
*/

/*
Details from id: 162, 163
- I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
- As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

*/
SELECT name FROM people WHERE id IN
(SELECT person_id FROM bank_accounts JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
JOIN phone_calls ON people.phone_number = phone_calls.caller
JOIN passengers ON people.passport_number = passengers.passport_number
WHERE passengers.flight_id = 36 AND phone_calls.duration < 60 AND atm_transactions.year = 2023 AND atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_transactions.atm_location = 'Leggett Street' AND atm_transactions.transaction_type = 'withdraw' AND bakery_security_logs.hour = 10 AND bakery_security_logs.minute BETWEEN 15 AND 25);
/*
+-------+
| name  |
+-------+
| Diana |
| Bruce |
+-------+
*/


-- Check the accomplice
SELECT name FROM people WHERE phone_number =
(SELECT receiver FROM phone_calls WHERE caller =
(SELECT phone_number FROM people WHERE name = 'Bruce') AND year = 2023 AND month = 7 AND day = 28 AND duration < 60);
/*
+-------+
| name  |
+-------+
| Robin |
+-------+
*/


-- Check the earliest flight and the destination
SELECT * FROM flights WHERE year = 2023 AND month = 7 AND day = 29 ORDER BY hour, minute ASC LIMIT 1;
SELECT * FROM airports WHERE id = 4;
/*
+----+--------------+-------------------+---------------+
| id | abbreviation |     full_name     |     city      |
+----+--------------+-------------------+---------------+
| 4  | LGA          | LaGuardia Airport | New York City |
+----+--------------+-------------------+---------------+
*/

