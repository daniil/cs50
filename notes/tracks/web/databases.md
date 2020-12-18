## Adding sessions

<pre>
from flask import Flask, redirect, render_template, request, <b>session</b>
<b>from flask_session import Session</b>

app = Flask(__name__)

<b># Session setup
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)</b>

@app.route("/")
def tasks():
  <b>if "todos" not in session:
    session["todos"] = []</b>
  return render_template("tasks.html", todos=<b>session["todos"]</b>)

@app.route("/add", methods=["GET", "POST"])
def add():
  if request.method == "GET":
    return render_template("add.html")
  else:
    # Get data from the form
    todo = request.form.get("task")
    <b>session["todos"]</b>.append(todo)
    return redirect("/")
</pre>

## Using DB for storing the data

### Creating DB:

```
sqlite3 lecture.db

CREATE TABLE 'registrants' (
  'id' INTEGER PRIMARY KEY,
  'name' VARCHAR(255),
  'email' VARCHAR(255)
);

INSERT INTO registrants (name, email) VALUES ('Alice', 'alice@example.com');

SELECT * FROM registrants;
```

### Creating Application

```
# application.py
from cs50 import SQL
from flask import Flask, redirect, render_template, request

app = Flask(__name__)

db = SQL("sqlite:///lecture.db")

@app.route("/")
def index():
  rows = db.execute("SELECT * FROM registrants")
  return render_template("index.html", rows=rows)

@app.route("/register", methods=["GET", "POST"])
def register():
  if request.method == "GET":
    return render_template("register.html")
  else:
    name = request.form.get("name")
    if not name:
      return render_template("apology.html", message="You must provide a name.")
    email = request.form.get("email")
    if not email:
      return render_template("apology.html", message="You must provide an email.")
    db.execute("INSERT INTO registrants (name, email) VALUES (:name, :email)", name=name, email=email)
    return redirect("/")


# /templates/index.html
...
<body>
  <h1>Registrants</h1>
  <ul>
    {% for row in rows %}
      <li>{{ row["name"] }} ({{ row["email"] }}</li>
    {% endfor %}
  </ul>
</body>
...


# /templates/register.html
...
<body>
  <h1>Register</h1>
  <form action="/register" method="post">
    <input type="text" name="name" placeholder="Name">
    <input type="text" name="submit" placeholder="Email Address">
    <input type="submit">
  </form>
</body>
...


# /templates/apology.html
...
<body>
  <h1>Sorry!</h1>
  <div>{{ message }}</div>
</body>
...
```