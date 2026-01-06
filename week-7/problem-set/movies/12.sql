-- 12. Titles of all of movies in which both Jennifer Lawrence and Bradley Cooper starred
SELECT title
FROM people
    JOIN stars ON people.id = stars.person_id
    JOIN movies ON stars.movie_id = movies.id
WHERE name = 'Jennifer Lawrence'
    OR name = 'Bradley Cooper'