# ==============================
# Defining a subset of available SQLite commands to Fuzz `sqlite3.c`
# ==============================

<start> ::= <create_table> "\n" <payload>

<create_table> ::= "CREATE TABLE users (id INTEGER PRIMARY KEY, name TEXT, age INTEGER);"

<payload> ::= <insert> | <query> | <payload> "\n" <payload>

<query> ::= "SELECT * FROM users WHERE " <condition> | "SELECT DISTINCT name FROM users" | "SELECT * FROM users ORDER BY age " <direction> | "SELECT name, COUNT(*), AVG(age) FROM users GROUP BY name"


<condition> ::= "age " <comparison> " " <age> | "(" <condition> ") AND (" <condition> ")" | "(" <condition> ") OR (" <condition> ")"

<comparison> ::= "=" | "<" | ">" | "<=" | ">=" | "!="
<direction> ::= "ASC" | "DESC"

<insert>  ::= "INSERT INTO users (name, age) VALUES " <rows> ";"

<rows>    ::= <row> | <row> ", " <rows>
<row>     ::= "(" <name> ", " <age> ")"

<name>    ::= "'" <word> "'"
<word>    ::= r'[a-z]+'
<age>     ::= r'[0-9]+'

maximizing DynamicAnalysis(str(<start>)).Novelty()
