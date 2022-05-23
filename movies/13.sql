SELECT DISTINCT P.name FROM people as P, stars as S WHERE S.movie_id in
(SELECT S.movie_id FROM people as P, stars as S WHERE P.name = "Kevin Bacon" AND P.birth = 1958 AND S.person_id = P.id)
AND S.person_id NOT IN (SELECT id FROM people as P WHERE P.name = "Kevin Bacon" AND P.Birth = 1958) AND S.person_id = P.id;