SELECT
    people.name
FROM
    movies,
    people,
    stars
WHERE
    people.id = stars.person_id AND
    stars.movie_id = movies.id AND
    movies.title = "Toy Story";
