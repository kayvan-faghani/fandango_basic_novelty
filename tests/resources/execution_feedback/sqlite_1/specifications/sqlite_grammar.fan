# ==============================
# Defining a subset of available SQLite commands to Fuzz `sqlite3.c`
# ==============================

<start> ::= <create_table> "\n" <payload>

<create_table> ::= "CREATE TABLE users (id INTEGER PRIMARY KEY, name TEXT, age INTEGER);"

<payload> ::= <insert> | <insert> "\n" <payload>

<insert>  ::= "INSERT INTO users (name, age) VALUES " <rows> ";"

<rows>    ::= <row> | <row> ", " <rows>
<row>     ::= "(" <name> ", " <age> ")"

<name>    ::= "'" <word> "'"
<word>    ::= r'[a-z]+'
<age>     ::= r'[0-9]+'

maximizing DynamicAnalysis(str(<start>)).NovelBlocks()
