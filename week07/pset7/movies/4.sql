SELECT
    COUNT(rating) AS "Top movies"
FROM
    ratings
WHERE
    rating = 10.0;