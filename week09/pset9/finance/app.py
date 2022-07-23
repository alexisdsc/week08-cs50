import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Get history data
    rows = db.execute("SELECT symbol, SUM(shares) AS 'shares' FROM history WHERE user_id = ? GROUP BY symbol", session["user_id"])

    # Get shares data and give it a format
    shares = []
    total_price_shares = 0
    for row in rows:
        shares.append({"info": lookup(row["symbol"]), "number": row["shares"],
                    "total": row["shares"]*lookup(row["symbol"])["price"]})

    # get total price for every different share symbol
    for s in shares:
        total_price_shares += s["total"]

    # Get current user cash data
    userdata = db.execute("SELECT username, cash FROM users WHERE id=?", session["user_id"])

    return render_template("index.html", shares=shares, userdata=userdata, total_price_shares=total_price_shares)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # html variables
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Get share info
        shares_info = lookup(symbol)

        # check symbol exist
        if not shares_info:
            return apology("Symbol does not exist", 400)
        # check shares exist
        if not shares:
            return apology("Must provide a number of shares", 400)
        # check shares is numeric, integer and positive
        if  not shares.isdecimal():
            return apology("Shares must be integer", 400)

        # get current user info
        rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])

        # check if user can afford to buy the number of share at current price
        total_price = int(shares)*shares_info["price"]

        if rows[0]["cash"] < total_price:
            return apology("Not enough cash!", 403)

        # add to database num fo shares and symbol asociated to current user
        db.execute("INSERT INTO history (user_id, symbol, shares, price, transaction_time) VALUES(?, ?, ?, ?, datetime('now'))",
                session["user_id"], shares_info["symbol"], shares, shares_info["price"])

        # update cash of current user
        db.execute("UPDATE users SET cash=? WHERE id = ?", rows[0]["cash"]-total_price, session["user_id"])

        # redirect to index
        return redirect("/")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # extract info from history table
    rows = db.execute("SELECT * FROM history WHERE user_id=? ORDER BY transaction_time DESC", session["user_id"])

    return render_template("history.html", rows=rows)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

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
    """Get stock quote."""
    # when submitting shares info
    if request.method == "POST":
        # html data
        symbol = request.form.get("symbol")
        # check if symbol exist
        share_info = lookup(symbol)
        if not share_info:
            return apology("Symbol does not exist", 400)
        # render symbol and its price times shares
        return render_template("quoted.html", share_info=share_info)

    # When accessed via GET (as by clicking link or redirect)
    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # When submitting data
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # check name, password and password confirmation are not empty
        if not username:
            return apology("Must provide username", 400)
        if not password:
            return apology("Enter your password", 400)
        if not confirmation:
            return apology("Must provide password confirmation", 400)
        # check password and confirmation are equal
        if password != confirmation:
            return apology("Passwords does not match", 400)
        # check if username exist in the database
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        if len(rows) != 0:
            return apology("Username already exist", 400)

        # add username and hashed password into the database
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, generate_password_hash(password))

        # redirect to index page
        return redirect("/")

    # User reached route via GET (as by clicking a link or redirect)
    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Check value of shares
        if not shares or int(shares) < 1:
            return apology("Enter number of shares", 400)

        # Check user inputs
        history_rows = db.execute(
            "SELECT symbol, SUM(shares) AS 'symbol_shares' FROM history WHERE user_id=? AND symbol=?", session["user_id"], symbol)
        print("shares", shares, type(shares))
        print("total_shares", history_rows, type(history_rows))
        # check symbol exist
        if not history_rows[0]["symbol_shares"] and not history_rows[0]["symbol"]:
            return apology("Symbol is not correct", 400)
        # Check user have enough shares to sell
        if int(shares) > history_rows[0]["symbol_shares"]:
            return apology("Not enough shares of that symbol", 400)

        # Check user have enough money to buy the shares
        cash = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])
        # Must be a unique id per username
        if len(cash) != 1:
            return apology("Something went wrong x_x", 400)
        # check you have enough money
        share_info = lookup(symbol)
        total_share_price = int(shares)*share_info["price"]
        user_cash = cash[0]["cash"]
        # check user cash is more than shares cost
        if total_share_price > user_cash:
            return apology("Not enough cash", 400)

        # Add to history database number shares sold in negative
        db.execute("INSERT INTO history (user_id, symbol, shares, price, transaction_time) VALUES(?, ?, ?, ?, datetime('now'))",
                session["user_id"], symbol, int(shares)*(-1), share_info["price"])
        # Update user cash
        db.execute("UPDATE users SET cash=? WHERE id=?", user_cash+total_share_price, session["user_id"])

        return redirect("/")

    # Get all symbols of current user
    symbols = db.execute("SELECT symbol FROM history WHERE user_id=? GROUP BY symbol", session["user_id"])
    return render_template("sell.html", symbols=symbols)
