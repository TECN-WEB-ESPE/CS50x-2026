-- 8. Names of people who starred in Toy Story
SELECT people.name
FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE movies.title = 'Toy Story';
