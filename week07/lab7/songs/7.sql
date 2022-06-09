SELECT
    AVG(songs.energy) AS "average energy"
FROM
    songs
    JOIN artists ON songs.artist_id = artists.id
WHERE
    artists.name = "Drake";