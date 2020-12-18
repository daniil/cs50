## Flask is a Python web server framework

```
# application.py

# Import Flash and HTML rendering
from flask import Flask, render_template

# Serve application from this file
app = Flask(__name__)

# Routes
@app.route("/")
def index():
  # Can return HTML
  return "<h1>Hello, world!</h1>"

  # We can separate it into template file "/templates/index.html"
  return render_template("index.html")

@app.route("/goodbye")
def bye():
  return "Goodbye!"
```

To run: `flask run`.

### Generating Dynamic content:

```
# application.py
@app.route("/")
def index():
  # Pass a value to a template
  return render_template("index.html", name="Emma")


# index.html
<body>
  <!-- Use the passed value -->
  Hello, {{ name }}
</body>
```

### Coin Flip:

```
import random

@app.route("/")
def index():
  number = random.randint(0, 1)
  return render_template("index.html", number=number)


<body>
  {% if number == 1 %}
    Your coin flip is HEADS.
  {% else %}
    Your coin flip is TAILS.
  {% endif %}
</body>
```

### Forms

```
<!-- Default form method is GET -->
<form action="/hello">
  <input type="text" name="name">
  <input type="submit">
</form>


from flask import Flask, render_template, request

app = Flash(__name__)

@app.route("/hello")
def hello():
  name = request.args.get("name")
  if not name:
    return render_template("failure.html")
  return render_template("hello.html", name=name)
```

### Factoring out HTML

```
# /templates/layout.html
...
<head>
  <style>
    {% block style %}
    {% endblock %}
  </style>
</head>
<body>
  {% block body %}
  {% endblock %}
</body>
...

# /templates/index.html
{% extends "layout.html" %}

{% block style %}
  body { color: red; }
{% endblock %}

{% block body %}
  Hello, World!
{% endblock %}
```

### Sending data to server

```
# /templates/add.html
<form action="/add" method="post">
  <input id="task" type="text" name="task" placeholder="Task name">
  <input id="submit" type="submit" disabled>
</form>
<script>
  document.querySelector('#task').onkeyup = function() {
    if (document.querySelector('#task').value === '') {
      document.querySelector('#submit').disabled = true;
    } else {
      document.querySelector('#submit').disabled = false;
    }
  }
</script>

# /templates/tasks.html
...
<ul>
  {% for todo in todos %}
    <li>{{ todo }}</li>
  {% endfor %}
</ul>
...


# application.py
from flask import Flash, redirect, render_template, request

app = Flask(__name__)

todos = []

@app.route("/")
def index():
  return render_template("tasks.html", todos=todos)

@app.route("/add", methods=["GET", "POST"])
def add():
  if request.method == "GET":
    return render_template("add.html)
  else:
    # Get data from the form
    todo = request.form.get("task")
    todos.append(todo)
    return redirect("/")
```