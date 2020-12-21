import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    return render_template("index.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide a symbol", 400)
        if not request.form.get("shares"):
            return apology("must provide number of shares", 400)
        if int(request.form.get("shares")) < 1:
            return apology("must enter valid number of shares", 400)

        # Lookup the stock
        result = lookup(request.form.get("symbol"))

        # If non-existant stock, render apology
        if not result:
            return apology("invalid symbol", 400)

        # Check user cash to see if they can afford current shares of stock
        cash_val = db.execute("SELECT cash FROM users WHERE id = :user_id",
                              user_id=session["user_id"])

        if cash_val[0]["cash"] < result["price"] * int(request.form.get("shares")):
            return apology("can't afford", 400)

        # Update users table cash column
        update_cash = db.execute("UPDATE users SET cash = :new_cash_val WHERE id = :user_id",
                                 new_cash_val=cash_val[0]["cash"] - result["price"] * int(request.form.get("shares")),
                                 user_id=session["user_id"])

        # Update transactions table with user information
        insert_transaction = db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (:user_id, :symbol, :shares, :price)",
                                        user_id=session["user_id"],
                                        symbol=request.form.get("symbol"),
                                        shares=int(request.form.get("shares")),
                                        price=result["price"])

        if not update_cash or not insert_transaction:
            return apology("couldn't purchase", 400)

        flash(f"Bought {request.form.get('shares')} shares of {result['name']} for ${result['price']}")
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)

        # Lookup the stock
        result = lookup(request.form.get("symbol"))

        # If non-existant stock, render apology
        if not result:
            return apology("invalid symbol", 400)

        return render_template("quoted.html", quote=result)

    # Render Quote page ("GET")
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        if not request.form.get("username"):
            return apology("must provide username", 400)
        if not request.form.get("password"):
            return apology("must provide password", 400)
        if not request.form.get("confirmation"):
            return apology("must provide password confirmation", 400)
        if not request.form.get("password") == request.form.get("confirmation"):
            return apology("password and confirmation must match", 400)

        # Check if user already exists with this username
        user = db.execute("SELECT username FROM users WHERE username = :username",
                          username=request.form.get("username"))

        if user:
            return apology("this user already exists", 400)

        # Insert a new user with hashed password into DB
        new_user = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)",
                              username=request.form.get("username"),
                              hash=generate_password_hash(request.form.get("password")))

        # Login the user and redirect to home page
        if new_user:
           session["user_id"] = new_user
           return redirect("/")

    # Render Register page ("GET")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
