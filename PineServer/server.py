from flask import Flask
app = Flask(__name__)

@app.route("/")
def start():
    return "PineServer"

@app.route("/highscores")
def highscores():
    return "Highscores!"

if(__name__ == "__main__"):
    app.run()