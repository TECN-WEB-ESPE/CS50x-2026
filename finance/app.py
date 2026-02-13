import os
from datetime import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

app.jinja_env.filters["usd"] = usd

app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

db = SQL("sqlite:///finance.db")


# -------------------------
# CREATE TRANSACTIONS TABLE
# -------------------------
db.execute("""
CREATE TABLE IF NOT EXISTS transactions (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER NOT NULL,
    symbol TEXT NOT NULL,
    shares INTEGER NOT NULL,
    price NUMERIC NOT NULL,
    transacted DATETIME DEFAULT CURRENT_TIMESTAMP
)
""")


@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# =========================
# INDEX
# =========================
@app.route("/")
@login_required
def index():

    user_id = session["user_id"]

    # Cash
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

    # Holdings
    rows = db.execute("""
        SELECT symbol, SUM(shares) as shares
        FROM transactions
        WHERE user_id = ?
        GROUP BY symbol
        HAVING SUM(shares) > 0
    """, user_id)

    portfolio = []
    total_stocks = 0

    for row in rows:
        quote = lookup(row["symbol"])
        price = quote["price"]
        total = price * row["shares"]
        total_stocks += total

        portfolio.append({
            "symbol": row["symbol"],
            "shares": row["shares"],
            "price": price,
            "total": total
        })

    grand_total = total_stocks + cash

    return render_template("index.html",
                           portfolio=portfolio,
                           cash=cash,
                           grand_total=grand_total)


# =========================
# BUY
# =========================
@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():

    if request.method == "GET":
        return render_template("buy.html")

    symbol = request.form.get("symbol")
    shares = request.form.get("shares")

    if not symbol:
        return apology("must provide symbol")

    quote = lookup(symbol)
    if quote is None:
        return apology("invalid symbol")

    try:
        shares = int(shares)
        if shares <= 0:
            return apology("shares must be positive")
    except:
        return apology("shares must be integer")

    price = quote["price"]
    cost = price * shares

    user_id = session["user_id"]
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

    if cost > cash:
        return apology("not enough cash")

    db.execute("""
        INSERT INTO transactions (user_id, symbol, shares, price)
        VALUES (?, ?, ?, ?)
    """, user_id, quote["symbol"], shares, price)

    db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", cost, user_id)

    flash("Purchased!")
    return redirect("/")


# =========================
# SELL
# =========================
@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():

    user_id = session["user_id"]

    stocks = db.execute("""
        SELECT symbol, SUM(shares) as shares
        FROM transactions
        WHERE user_id = ?
        GROUP BY symbol
        HAVING SUM(shares) > 0
    """, user_id)

    if request.method == "GET":
        return render_template("sell.html", stocks=stocks)

    symbol = request.form.get("symbol")
    shares = request.form.get("shares")

    if not symbol:
        return apology("must choose stock")

    try:
        shares = int(shares)
        if shares <= 0:
            return apology("shares must be positive")
    except:
        return apology("shares must be integer")

    owned = db.execute("""
        SELECT SUM(shares) as shares
        FROM transactions
        WHERE user_id = ? AND symbol = ?
    """, user_id, symbol)[0]["shares"]

    if shares > owned:
        return apology("too many shares")

    quote = lookup(symbol)
    price = quote["price"]
    value = price * shares

    db.execute("""
        INSERT INTO transactions (user_id, symbol, shares, price)
        VALUES (?, ?, ?, ?)
    """, user_id, symbol, -shares, price)

    db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", value, user_id)

    flash("Sold!")
    return redirect("/")


# =========================
# QUOTE
# =========================
@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():

    if request.method == "GET":
        return render_template("quote.html")

    symbol = request.form.get("symbol")
    if not symbol:
        return apology("must provide symbol")

    quote = lookup(symbol)
    if quote is None:
        return apology("invalid symbol")

    return render_template("quoted.html", quote=quote)


# =========================
# HISTORY
# =========================
@app.route("/history")
@login_required
def history():

    user_id = session["user_id"]

    rows = db.execute("""
        SELECT symbol, shares, price, transacted
        FROM transactions
        WHERE user_id = ?
        ORDER BY transacted DESC
    """, user_id)

    return render_template("history.html", rows=rows)


# =========================
# REGISTER
# =========================
@app.route("/register", methods=["GET", "POST"])
def register():

    if request.method == "GET":
        return render_template("register.html")

    username = request.form.get("username")
    password = request.form.get("password")
    confirmation = request.form.get("confirmation")

    if not username:
        return apology("must provide username")
    if not password:
        return apology("must provide password")
    if password != confirmation:
        return apology("passwords must match")

    hash_pw = generate_password_hash(password)

    try:
        user_id = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)",
                             username, hash_pw)
    except:
        return apology("username exists")

    session["user_id"] = user_id
    return redirect("/")


@app.route("/logout")
def logout():
    session.clear()
    return redirect("/")
