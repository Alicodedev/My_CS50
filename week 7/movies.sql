SELECT title, year FROM movies WHERE year='2008';--*Q1

SELECT birth FROM people WHERE name='Emma Stone';--*Q2

SELECT title FROM movies WHERE year=2018 ORDER BY title DESC;--*Q3

SELECT rating FROM ratings WHERE rating=10;--*Q4

SELECT title , year FROM movies WHERE (SELECT name FROM people)='Harry Potter';--*Q5

SELECT AVG(rating) FROM ratings WHERE (SELECT year FROM movies WHERE year=2012);--*Q6

SELECT title, rating FROM movies
    JOIN ratings ON movies.id = ratings.movie_id
    WHERE year = 2010 ORDER BY rating DESC, title ASC;--*Q7

 SELECT name FROM people--*Q8
    JOIN stars ON stars.person_id = people.id
    JOIN movies on movie_id = movies.id
    WHERE movies.title='Toy Story';

SELECT DISTINCT name FROM people--*Q9
    JOIN stars on stars.person_id = people.id
    JOIN movies ON stars.movie_id = movies.id
    WHERE movies.year=2004;


SELECT DISTINCT name FROM people--*Q10
    JOIN directors on directors.person_id = people.id
    JOIN movies ON directors.movie_id = movies.id
    JOIN ratings ON ratings.movie_id = movies.id
    WHERE movies.rating >= 9.0;

SELECT name, title FROM people--*Q11
    JOIN stars on stars.person_id = people.id
    JOIN movies ON stars.movie_id = movies.id
    JOIN ratings on ratings.movie_id = movies.id    
    WHERE people.name='Chadwick Boseman' ORDER BY ratings.rating DESC LIMIT 5;

SELECT title FROM movies--*Q12
    JOIN stars ON stars.movie_id = movies.id
    JOIN people ON stars.person_id = people.id
    WHERE people.name='Johnny Depp'
    AND title IN (SELECT title FROM movies
    JOIN stars ON stars.movie_id = movies.id
    JOIN people ON stars.person_id = people.id
    WHERE people.name='Helena Bonham Carter');

SELECT DISTINCT name FROM people--*Q13
    JOIN stars ON stars.person_id = people.id
    JOIN movies ON stars.movie_id = movies.id
    WHERE movies.id IN (SELECT movies.id FROM movies

    JOIN stars ON stars.movie_id = movies.id
    JOIN people ON people.id = stars.person_id  
WHERE people.name = 'Kevin Bacon' AND people.birth = '1958' AND people.name != 'Kevin Bacon'
);
