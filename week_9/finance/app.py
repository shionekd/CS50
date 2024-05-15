import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


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
    user_id = session["user_id"]
    user_rows = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    cash = round(user_rows[0]['cash'], 2)

    rows = db.execute(
        "SELECT symbol, SUM(shares) AS shares_sum, price, SUM(shares) * price AS shares_price FROM transactions WHERE user_id = ? GROUP by symbol", user_id
    )

    shares_sum = 0
    for row in rows:
        shares_sum += row['shares_price']

    return render_template("index.html", rows = rows, cash = cash, shares_sum = shares_sum)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        user_id = session["user_id"]

        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        if not symbol:
            return apology("Must Provide Symbol ", 400)
        elif not shares:
            return apology("Must Provide Number ", 400)
        elif int(shares) < 0:
            return apology("Must Provide Correct Number ", 400)

        # Check the price of symbol
        stock = lookup(symbol)
        if stock == None:
            return apology("Symbol Does Not Exist", 400)
        else:
            price = stock['price']

        # Check how much the user have in cash
        user = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        cash_value = user[0]["cash"]

        total = price * float(shares)
        if total > cash_value:
            return apology("You need more money to buy the symbol", 400)
        else:
            # Update users cash price
            update_value = cash_value - total
            db.execute("UPDATE users SET cash = ? WHERE id = ?", update_value, user_id)

            # Save the transaction data
            # 1:Buy, 2:Sell, 3:Add Cash
            db.execute("INSERT INTO transactions (user_id, symbol, shares, price, action, date) VALUES (?, ?, ?, ?, 1, CURRENT_TIMESTAMP)",user_id, symbol, shares, price)

            flash('Bought!')
            return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    if request.method == "GET":
        user_id = session["user_id"]
        rows = db.execute("SELECT * FROM transactions WHERE user_id = ?", user_id)
        if len(rows) == 0:
            message = "No history"
            return render_template("history.html", message = message)
        else:
            return render_template("history.html", rows = rows)


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
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
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
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Must Provide Symbol", 400)
        else:
            stock = lookup(symbol)
            if stock == None:
                return apology("Symbol Does Not Exist", 400)
            else:
                return render_template("quoted.html", stock = stock)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        name_check = db.execute("SELECT COUNT(*) FROM users WHERE username = ?", username)

        if not username:
            return apology("Must Provide Username", 400)
        elif not password:
            return apology("Must Provide Password", 400)
        elif not confirmation:
            return apology("Must Provide Comform Password", 400)
        elif password != confirmation:
            return apology("Passwords Do Not Match", 400)
        elif name_check[0]['COUNT(*)'] != 0:
            return apology("Username Alrady Exitst", 400)
        else:
            db.execute(
                "INSERT INTO users (username, hash, cash) VALUES (?, ?, ?)", username, generate_password_hash(password), 10000
            )

            rows = db.execute("SELECT * FROM users WHERE username = ?", username)
            session["user_id"] = rows[0]["id"]

            return redirect("/quote")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]
    if request.method == "GET":
        rows = db.execute(
            "SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol", user_id
        )
        return render_template("sell.html", rows = rows)
    else:
        symbol = request.form.get("sell")
        shares = request.form.get("shares")
        if not symbol:
            return apology("Must Select symbol", 400)
        elif not shares:
            return apology("Must provide shares", 400)

        # Check current symbol
        rows = db.execute(
            "SELECT SUM(shares) AS sum_shares, * FROM transactions WHERE user_id = ? AND symbol = ? GROUP BY symbol", user_id, symbol
        )
        if int(shares) > rows[0]['sum_shares']:
            return apology("Plese input less shares", 400)
        else:
            stock = lookup(symbol)
            if stock == None:
                return apology("Symbol Does Not Exist", 400)
            else:
                price = stock['price']
                shares = int(shares)
                minus_shares = -shares
                db.execute(
                    "INSERT INTO transactions (user_id, symbol, shares, price, action, date) VALUES (?, ?, ?, ?, 2, CURRENT_TIMESTAMP)", user_id, symbol, minus_shares, price
                )

                total_price = price * shares
                flash("Sold!")
                return redirect("/")


@app.route("/add_cash", methods=["GET", "POST"])
@login_required
def add_cash():
    """Add Cash."""
    if request.method == "POST":
        cash = float(request.form.get("cash"))

        if not cash:
            return apology("Must Provide Price", 400)
        else:
            user_id = session["user_id"]
            user = db.execute("SELECT cash FROM users WHERE id = ?", user_id)

            cash_value = user[0]["cash"]
            new_value = round(cash_value + cash, 2)
            db.execute(
                "UPDATE users SET cash = ? WHERE id = ?", new_value, user_id
            )
            db.execute(
                "INSERT INTO transactions (user_id, symbol, shares, price, action, date) VALUES (?, 'cash', 'cash', ?, 3, CURRENT_TIMESTAMP)", user_id, cash
            )

            flash("Added Cash!")
            return redirect("/")
    else:
        return render_template("add_cash.html")


@app.route("/change_pwd", methods=["GET", "POST"])
@login_required
def change_pwd():
    """Change Password."""
    if request.method == "POST":
        crt_psw = request.form.get("crt_psw")
        cfm_pwd = request.form.get("cfm_pwd")
        new_psw = request.form.get("new_psw")

        if not crt_psw:
            return apology("Must Provide Current Password", 400)
        elif not cfm_pwd:
            return apology("Must Provide Conform Password", 400)
        elif not new_psw:
            return apology("Must Provide New Password", 400)
        else:
            # Query database for username
            user_id =session["user_id"]
            rows = db.execute(
                "SELECT * FROM users WHERE id = ?", user_id
            )

            # Ensure password is correct
            if not check_password_hash(
                rows[0]["hash"], request.form.get("crt_psw")
            ):
                return apology("Current Password Is Not Correct", 400)
            elif crt_psw != cfm_pwd:
                return apology("Conform Password", 400)
            else:
                db.execute(
                    "UPDATE users SET hash = ? WHERE id = ?", generate_password_hash(new_psw), user_id
                )

                flash("Password Changed")
                return redirect("/")
    else:
        return render_template("change_pwd.html")
