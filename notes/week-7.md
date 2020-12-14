## Sorting with Python

```
import csv

counts = {}

with open("shows.csv", "r") as file:
    reader = csv.DictReader(file)

    for row in reader:
        title = row("title").lower()

        if title in counts:
            counts[title] += 1
        else:
            counts[title] = 1

# Passing in anonymous sorting function and reverse parameter
for title, count in sorted(counts.items(), key=lambda item: item[1], reverse=True):
    print(title, count, sep=" | ")
```

## SQLite

### Importing

```
sqlite3 filename.db
.mode csv
.import "filename.csv"
.schema
```

### Data Types (in SQLite)

- BLOB (binary large object)
- INTEGER
    - smallint
    - integer
    - bigint
- NUMERIC
    - boolean
    - date
    - datetime
    - numeric (scale, precision)
    - time
    - timestamp
- REAL
    - real
    - double precision
- TEXT
    - char(n) - fixed length string
    - varchar(n)
    - text

### Other Data Types

- ENUM (string object with a value chosen from a list of permitted values)

## SQL Queries

### INSERT

```
INSERT INTO <table> (<columns>) VALUES (<values>);
```

### SELECT

```
SELECT <columns> FROM <table> WHERE <predicate> ORDER BY <column>;
```

### SELECT (JOIN)

```
SELECT <columns> FROM <table1> JOIN <table2> ON <predicate>;

SELECT users.fullname, moms.mother FROM users JOIN moms ON users.username = moms.username;
```

### UPDATE

```
UPDATE <table> SET <column> = <value> WHERE <predicate>;
```

### DELETE

```
DELETE FROM <table> WHERE <predicate>;
```

## Examples

### Connection and DB Creation/Insertion

```
import cs50
import csv

# Create new empty file - open file in write mode and close it right away
open("shows.db", "w").close()

# Open file for SQLite
db = cs50.SQL("sqlite:///shows.db")

# Execute SQL (create shows table)
db.execute("CREATE TABLE shows (tconst TEXT, primaryTitle TEXT, startYear NUMERIC, genres TEXT)")

# Open .tsv
with open("title.basics.tsv", "r") as titles:
    # Create DictReader
    reader = csv.DictReader(titles, delimiter="\t")
    for row in reader:
        if row["titleType"] == "tvSeries" and row["isAdult"] == "0":
            if row["startYear"] != "\\N":
                startYear = int(row["startYear"])
                if startYear >= 1970:
                    tconst = row["tconst"]
                    primaryTitle = row["primaryTitle"]
                    genres = row["genres"]

                    # Insert a show row (? is a placeholder for a value)
                    db.execute("INSERT INTO shows (tconst, primaryTitle, startYear, genres) VALUES(?, ?, ?, ?)",
                        tconst, primaryTitle, startYear, genres)
```

### Creating a genres table:

```
db.execute("CREATE TABLE shows (id INT, title TEXT, year NUMERIC, PRIMARY KEY(id))")
db.execute("CREATE TABLE genres (show_id INT, genre TEXT, FOREIGN KEY(show_id) REFERENCES shows(id)")
```

### Querying for all shows in a genre:

```
SELECT COUNT(*) FROM shows WHERE id IN (SELECT show_id FROM genres WHERE genre == "Comedy") AND year = 2019;
```

### Select and Group:

```
SELECT title, COUNT(title) AS n FROM favorites GROUP BY title ORDER BY n DESC LIMIT 10;
```

### Joining:

```
SELECT * FROM shows JOIN genres ON shows.id = genres.show_id WHERE title = "The Office" AND year = 2005;
```

### Nested Query:

```
SELECT * FROM shows WHERE id IN (SELECT show_id FROM stars WHERE person_id = (SELECT * FROM people WHERE name = "Ellen DeGeneres"));
```

### Explicit Join:

```
SELECT title FROM
people JOIN stars ON people.id = stars.person_id JOIN
shows ON stars.show_id = shows.id
WHERE name = "Ellen DeGeneres"
```

### Creating Indexes:

```
CREATE INDEX person_index ON stars(person_id);
CREATE INDEX show_index ON stars(show_id);
CREATE INDEX name_index ON people(name);
```

This will speed up the Explicit Join query above.

To avoid race conditions your can use SQL Transactions.

Libraries such as CS50 sanitize user inputs and helps avoid SQL injection, caused, for example, by using raw strings.