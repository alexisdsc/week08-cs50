SELECT
    movies.title
FROM
    movies
    JOIN stars ON movies.id = stars.movie_id
    JOIN people ON people.id = stars.person_id
    JOIN ratings ON stars.movie_id = ratings.movie_id
WHERE
    people.name LIKE "%Chadwick Boseman%"
ORDER BY
    ratings.rating DESC
LIMIT 5;