SELECT name From songs; --*Q1

SELECT name,tempo FROM songs ORDER BY tempo ASC;;--*Q2

SELECT name,duration_ms FROM SONGS ORDER BY duration_ms DESC;--*Q3

SELECT name FROM songs
WHERE danceability > 0.75 AND energy > 0.75 AND valence > 0.75--*Q4

SELECT AVG(energy) FROM songs;--*Q5

SELECT name FROM songs
WHERE artist_id= (SELECT id FROM artists WHERE name="Post Malone");--*Q6

SELECT AVG(energy) FROM songs
WHERE artist_id = (SELECT id FROM artists WHERE name = 'Drake');--*Q7

SELECT name FROM songs WHERE name LIKE '%feat.%';--*8