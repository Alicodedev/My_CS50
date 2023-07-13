from flask import Flask, render_template, request

app = Flask(__name__)

color_values = [
    "red",
    "blue"
]

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        color = request.form.get("color")# stores the form color value
        if color in color_values:
            return render_template("color.html",color_id=color)# renders only colors from color value list

        else:
            return "Invaild color value"

    return render_template("index.html")
