-- Keep a log of any SQL queries you execute as you solve the mystery.
-- to start gathering informations with the witnesses interviews
   SELECT * FROM interviews WHERE day = 28 AND month = 7 AND year = 2021;
--| 161 | Ruth    | 2021 | 7     | 28  | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
--| 162 | Eugene  | 2021 | 7     | 28  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
--| 163 | Raymond | 2021 | 7     | 28  | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |
--| 193 | Emma    | 2021 | 7     | 28  | I'm the bakery owner, and someone came in, suspiciously whispering into a phone for about half an hour. They never bought anything.

--following information checking the parking lot
SELECT name FROM people
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25
AND activity = "exit";
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

--transactions made matching the interview report
SELECT name FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE year = 2021 AND day = 28 AND month = 7 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";
+---------+
|  name   |
+---------+
| Bruce   |
| Diana   |
| Brooke  |
| Kenny   |
| Iman    |
| Luca    |
| Taylor  |
| Benista |
+---------+

suspects Bruce, Diana, Iman, Luca

--people in the flight
SELECT name FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
WHERE passengers.flight_id = (
SELECT id FROM flights
WHERE year = 2021 AND month = 7 AND day = 29 AND origin_airport_id = (
SELECT id FROM airports WHERE city = "Fiftyville")
ORDER BY hour,minute
LIMIT 1);

+--------+
|  name  |
+--------+
| Doris  |
| Sofia  |
| Bruce  |
| Edward |
| Kelsey |
| Taylor |
| Kenny  |
| Luca   |
+--------+

Suspects Bruce and Luca

--people that made a call
SELECT name FROM people
JOIN phone_calls ON phone_calls.caller = people.phone_number
WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60;

+---------+
|  name   |
+---------+
| Sofia   |
| Kelsey  |
| Bruce   |
| Kelsey  |
| Taylor  |
| Diana   |
| Carina  |
| Kenny   |
| Benista |
+---------+

Suspects Bruce


-- flight destination
SELECT city FROM airports
WHERE id = (SELECT destination_airport_id FROM flights
WHERE year = 2021 AND day = 29 AND month = 7 AND origin_airport_id = (
SELECT id FROM airports WHERE city = "Fiftyville")
ORDER BY hour,minute
LIMIT 1);

NEW YORK CITY

--ACCOMPLICE
SELECT phone_number FROM people WHERE name = "Bruce";
(367) 555-5533

SELECT name FROM people WHERE phone_number = (
SELECT receiver FROM phone_calls
WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60 AND caller = "(367) 555-5533"
);

Robin