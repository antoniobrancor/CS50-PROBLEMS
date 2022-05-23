SELECT M.title FROM movies as M, stars as S, ratings as R, people as P WHERE P.name = "Chadwick Boseman" AND P.id = S.person_id AND S.movie_id = M.id  AND R.movie_id = M.id ORDER BY R.rating DESC LIMIT 5;