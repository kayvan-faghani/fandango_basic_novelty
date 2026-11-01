CREATE TABLE users (
    id INTEGER PRIMARY KEY,
    name TEXT,
    age INTEGER
);

INSERT INTO users (name, age)
VALUES ('Alice', 25), ('Bob', 30), ('Charlie', 19);

SELECT name, age
FROM users
WHERE age >= 25
ORDER BY age DESC;
