# Importuje třídu 'Flask' ze modulu 'flask'.
from flask import Flask

# Vytváří instanci třídy 'Flask' a přiřazuje ji proměnné 'app'.
app = Flask(__name__)

# Dekorátor '@app.route('/')' přiřazuje funkci 'hello_world' URL cestu '/'.
@app.route('/')
def hello_world():
    # Vrací text 'Hello, world!' jako odpověď na HTTP požadavek.
    return 'Hello, world!'
