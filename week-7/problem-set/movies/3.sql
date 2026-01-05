-- 3. Titles of all movies since 2018, in alphabetical order
SELECT title FROM movies WHERE year > 2018 AND year < 2026 ORDER BY title