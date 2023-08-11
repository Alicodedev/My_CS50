import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, jsonify
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
import datetime

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

    user_id = session["user_id"]

    transactions_db = db.execute("SELECT symbol, SUM(shares) AS shares, price, SUM(shares * price) AS share_total FROM transactions WHERE user_id = ? GROUP BY symbol ", user_id) # querying user info based on session
    cash_db = db.execute("SELECT cash FROM users WHERE id = ? ", user_id)
    cash = cash_db[0]["cash"]
    total_db = db.execute("SELECT u.id AS user_id, u.username, u.cash + COALESCE(SUM(t.price * t.shares),0) AS total_balance FROM users u LEFT JOIN transactions t ON u.id = t.user_id WHERE user_id = ? GROUP BY u.id ", user_id)
    user_total = total_db[0]["total_balance"] # accessing the key for total balance of the user

    """Show portfolio of stocks"""
    return render_template("index.html", database = transactions_db, cash = cash, total=user_total, usd_func=usd) # accessing transaction query data by using placeholders


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():

    if request.method == "POST": # essentially checking if data is being sent to the website

         symbol = request.form.get('symbol') #getting form field values of each users information ( ticker symbol)
         shares = int(request.form.get('shares')) #the amount of shares provided in the form field

         if not symbol: # ticker symbol is not recognized
             return apology("Enter the stocks ticker symbol")

         stock = lookup(symbol.upper()) # using lookup to call for stock price
         if not stock: # stock is not recognized
             return apology("Enter a valid ticker symbol")

         if shares <= 0:
             return apology("Enter valid share amount") # input is not a positive integer

         transaction_value = shares * stock["price"] # the value for the price of the stock to share ratio

         user_id = session["user_id"] # holding session value of users
         user_cash_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id) # selects the total cash of the specific user in the current session
         user_cash = user_cash_db[0]["cash"] # accessing cash tables row with 0th index (only one row in the table)

         if user_cash < transaction_value: # user can not purchase below transaction value
             return apology("Not Enough Money")

         uptd_cash = user_cash - transaction_value # updating the users total cash

         db.execute("UPDATE users SET cash = ? WHERE id = ?", uptd_cash , user_id) # updating total cash value for the specific user and transcation

         date = datetime.datetime.now() # holds current time
         db.execute("INSERT INTO transactions (user_id, symbol, shares, price, date ) VALUES (? , ? , ? , ? , ?)", user_id , stock["symbol"] , shares, stock["price"] , date)

         flash("Bought")
         return redirect("/")


    else:
        return render_template('buy.html')



@app.route("/history")
@login_required
def history():
    user_id = session["user_id"]

    transactions_db = db.execute("SELECT symbol, shares, price, date FROM transactions WHERE user_id = ?", user_id) # querying user info based on session
    return render_template("history.html", database = transactions_db, usd_func=usd) # database holds transaction of user data. it will be iterated over with jinja code for accessing each row of transactions.db



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

    if(request.method == "POST"):# checking for POST REQUEST
        symbol = request.form.get('symbol') #getting form field values of each users information

        if not symbol:
            return apology("Enter the stocks ticker symbol")

        item = lookup(symbol.upper()) # using lookup to call yahoo finance api for stock information

        if not item:
            return apology("Enter a valid ticker symbol")

        return render_template("quoted.html", item=item, usd_func=usd) # rendering the stocks information in a new template with usd_func as currency string format

    else:
        return render_template("quote.html")



@app.route("/register", methods=["GET", "POST"])
def register():

    if (request.method == "POST"): # checking for POST REQUEST

        username = request.form.get('username') # getting form field values of each users information
        password = request.form.get('password')
        confirmation = request.form.get('confirmation')

        if not username: # error handeling of form fields of they're blank
            return apology("Username is required", 403)
        elif not password:
            return apology("Password is required", 403)
        elif not confirmation:
            return apology("Please confirm the password",403)

        if password != confirmation: # both password and confirm password form fields do not match
            return apology('Password do not match')

        hash = generate_password_hash(password)

        try:
            db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hash)
            return redirect('/') # if users registered return to root page
        except:
            return apology("Username is already registered")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():

    user_id = session["user_id"]

    if request.method == "POST": # checking for POST REQUEST
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        user_shares = db.execute("SELECT SUM(shares) AS total_shares FROM transactions WHERE user_id = ? AND symbol = ? GROUP BY symbol", user_id, symbol)[0]["total_shares"]# querying the current shares of the stock of a speific user(based on session)
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"] # querying the current cash balance of the user
        stock_price = lookup(symbol)["price"]
        sale = user_shares * stock_price

        if not symbol:
            return apology("invalid stock selection")

        elif shares <= 0:
            return apology("Enter a valid number of shares")

        elif user_shares < shares:
            return apology("Not enough shares owned")

        # UPDATE THE USERS CASH WHEN SELL TRANSCTION IS COMPLETE
        db.execute("UPDATE users SET cash = ? WHERE id = ? ", (user_cash + sale) , user_id) #upadting the users table of coloum cahs(balance) from selling the shares( )

        db.execute("INSERT INTO transactions (user_id, shares, symbol, price) VALUES (?, ?, ?, ?)", user_id, -shares, symbol, stock_price ) # tracking sale of the shares for in transactions table by adding new row
        return redirect('/')

    else:
        symbols = db.execute("SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol", user_id) # accessing stocks for select menu
        return render_template("sell.html",symbols=symbols)
