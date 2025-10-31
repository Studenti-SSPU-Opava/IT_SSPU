from flask import Flask, request, jsonify, render_template, redirect, url_for, flash
from flask_sqlalchemy import SQLAlchemy
from flask_migrate import Migrate
from datetime import datetime, date
import os
import json
import csv
import click
from forms import CreateUserForm, EditUserForm, PostForm, DeleteForm

# Vytvoření Flask aplikace
app = Flask(__name__)

# Konfigurace SQLite databáze
basedir = os.path.abspath(os.path.dirname(__file__))
app.config['SQLALCHEMY_DATABASE_URI'] = f'sqlite:///{os.path.join(basedir, "app.db")}'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
app.config['SECRET_KEY'] = 'your-secret-key-change-this-in-production'

# Inicializace databáze a migrací
db = SQLAlchemy(app)
migrate = Migrate(app, db)

# Model pro uživatele
class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(80), unique=True, nullable=False)
    email = db.Column(db.String(120), unique=True, nullable=False)
    datum_narozeni = db.Column(db.Date, nullable=True)
    created_at = db.Column(db.DateTime, default=datetime.utcnow)
    posts = db.relationship('Post', backref='author', lazy=True)

    def to_dict(self):
        return {
            'id': self.id,
            'username': self.username,
            'email': self.email,
            'datum_narozeni': self.datum_narozeni.isoformat() if self.datum_narozeni else None,
            'created_at': self.created_at.isoformat()
        }

# Model pro příspěvky
class Post(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    title = db.Column(db.String(100), nullable=False)
    content = db.Column(db.Text, nullable=False)
    created_at = db.Column(db.DateTime, default=datetime.utcnow)
    user_id = db.Column(db.Integer, db.ForeignKey('user.id'), nullable=False)

    def to_dict(self):
        return {
            'id': self.id,
            'title': self.title,
            'content': self.content,
            'created_at': self.created_at.isoformat(),
            'author': self.author.username
        }

# Základní routy - HTML stránky
@app.route('/')
def index():
    return render_template('index.html')

@app.route('/users')
def list_users():
    users = User.query.all()
    delete_form = DeleteForm()
    return render_template('users.html', users=users, delete_form=delete_form)

@app.route('/users/create', methods=['GET', 'POST'])
def create_user_form():
    form = CreateUserForm()
    
    if form.validate_on_submit():
        user = User(
            username=form.username.data,
            email=form.email.data,
            datum_narozeni=form.datum_narozeni.data
        )
        db.session.add(user)
        db.session.commit()
        
        flash(f'Uživatel {form.username.data} byl úspěšně vytvořen', 'success')
        return redirect(url_for('list_users'))
    
    return render_template('create_user.html', form=form)

@app.route('/users/<int:user_id>/edit', methods=['GET', 'POST'])
def edit_user_form(user_id):
    user = User.query.get_or_404(user_id)
    form = EditUserForm(user_id=user.id, obj=user)
    
    if form.validate_on_submit():
        form.populate_obj(user)
        db.session.commit()
        
        flash(f'Uživatel {user.username} byl úspěšně aktualizován', 'success')
        return redirect(url_for('list_users'))
    
    return render_template('edit_user.html', form=form, user=user)

@app.route('/users/<int:user_id>/delete', methods=['POST'])
def delete_user(user_id):
    form = DeleteForm()
    
    if form.validate_on_submit():
        user = User.query.get_or_404(user_id)
        username = user.username
        
        # Nejdříve smažeme všechny příspěvky uživatele
        Post.query.filter_by(user_id=user_id).delete()
        
        db.session.delete(user)
        db.session.commit()
        
        flash(f'Uživatel {username} byl úspěšně smazán', 'success')
    else:
        flash('Chyba při mazání uživatele', 'error')
    
    return redirect(url_for('list_users'))

# API routy - REST API
@app.route('/api')
def api_info():
    return jsonify({
        'message': 'REST API pro správu uživatelů',
        'endpoints': {
            'users': '/api/users',
            'posts': '/api/posts',
            'create_user': 'POST /api/users',
            'create_post': 'POST /api/posts',
            'update_user': 'PUT /api/users/<id>',
            'delete_user': 'DELETE /api/users/<id>'
        }
    })

# API pro uživatele
@app.route('/api/users', methods=['GET'])
def get_users():
    users = User.query.all()
    return jsonify([user.to_dict() for user in users])

@app.route('/api/users', methods=['POST'])
def create_user():
    data = request.get_json()
    
    if not data or 'username' not in data or 'email' not in data:
        return jsonify({'error': 'Username a email jsou povinné'}), 400
    
    # Kontrola, zda uživatel již neexistuje
    if User.query.filter_by(username=data['username']).first():
        return jsonify({'error': 'Uživatel s tímto jménem již existuje'}), 400
    
    if User.query.filter_by(email=data['email']).first():
        return jsonify({'error': 'Uživatel s tímto emailem již existuje'}), 400
    
    # Parsování data narození, pokud je zadáno
    datum_narozeni = None
    if 'datum_narozeni' in data and data['datum_narozeni']:
        try:
            datum_narozeni = datetime.strptime(data['datum_narozeni'], '%Y-%m-%d').date()
        except ValueError:
            return jsonify({'error': 'Datum narození musí být ve formátu YYYY-MM-DD'}), 400
    
    user = User(
        username=data['username'], 
        email=data['email'],
        datum_narozeni=datum_narozeni
    )
    db.session.add(user)
    db.session.commit()
    
    return jsonify(user.to_dict()), 201

@app.route('/api/users/<int:user_id>', methods=['GET'])
def get_user(user_id):
    user = User.query.get_or_404(user_id)
    return jsonify(user.to_dict())

@app.route('/api/users/<int:user_id>', methods=['PUT'])
def update_user(user_id):
    user = User.query.get_or_404(user_id)
    data = request.get_json()
    
    if not data:
        return jsonify({'error': 'Žádná data nebyla posána'}), 400
    
    if 'username' in data:
        # Kontrola, zda uživatelské jméno není použito jiným uživatelem
        existing_user = User.query.filter_by(username=data['username']).first()
        if existing_user and existing_user.id != user.id:
            return jsonify({'error': 'Uživatel s tímto jménem již existuje'}), 400
        user.username = data['username']
    
    if 'email' in data:
        # Kontrola, zda email není použit jiným uživatelem
        existing_user = User.query.filter_by(email=data['email']).first()
        if existing_user and existing_user.id != user.id:
            return jsonify({'error': 'Uživatel s tímto emailem již existuje'}), 400
        user.email = data['email']
    
    db.session.commit()
    return jsonify(user.to_dict())

@app.route('/api/users/<int:user_id>', methods=['DELETE'])
def delete_user_api(user_id):
    user = User.query.get_or_404(user_id)
    
    # Nejdříve smažeme všechny příspěvky uživatele
    Post.query.filter_by(user_id=user_id).delete()
    
    db.session.delete(user)
    db.session.commit()
    
    return jsonify({'message': f'Uživatel {user.username} byl úspěšně smazán'})

# API pro příspěvky
@app.route('/api/posts', methods=['GET'])
def get_posts():
    posts = Post.query.all()
    return jsonify([post.to_dict() for post in posts])

@app.route('/api/posts', methods=['POST'])
def create_post():
    data = request.get_json()
    
    if not data or 'title' not in data or 'content' not in data or 'user_id' not in data:
        return jsonify({'error': 'Title, content a user_id jsou povinné'}), 400
    
    # Kontrola, zda uživatel existuje
    user = User.query.get(data['user_id'])
    if not user:
        return jsonify({'error': 'Uživatel neexistuje'}), 404
    
    post = Post(
        title=data['title'],
        content=data['content'],
        user_id=data['user_id']
    )
    db.session.add(post)
    db.session.commit()
    
    return jsonify(post.to_dict()), 201

@app.route('/api/posts/<int:post_id>', methods=['GET'])
def get_post(post_id):
    post = Post.query.get_or_404(post_id)
    return jsonify(post.to_dict())

# CLI příkazy pro databázové migrace
@app.cli.command()
def init_db():
    """Inicializace databáze - vytvoří všechny tabulky."""
    db.create_all()
    print("Databáze byla inicializována!")

@app.cli.command()
def drop_db():
    """Smaže všechny tabulky v databázi."""
    db.drop_all()
    print("Databáze byla smazána!")

@app.cli.command()
def reset_db():
    """Resetuje databázi - smaže a znovu vytvoří všechny tabulky."""
    db.drop_all()
    db.create_all()
    print("Databáze byla resetována!")

@app.cli.command()
@click.option('--format', default='json', help='Formát exportu: json nebo csv')
@click.option('--output', default='export', help='Název výstupního souboru (bez přípony)')
def export_data(format, output):
    """Exportuje všechna data z databáze do JSON nebo CSV souboru."""
    try:
        # Export uživatelů
        users = User.query.all()
        users_data = [user.to_dict() for user in users]
        
        # Export příspěvků
        posts = Post.query.all()
        posts_data = [post.to_dict() for post in posts]
        
        if format.lower() == 'json':
            # Export do JSON
            data = {
                'users': users_data,
                'posts': posts_data,
                'exported_at': datetime.utcnow().isoformat(),
                'version': '1.0'
            }
            
            filename = f"{output}.json"
            with open(filename, 'w', encoding='utf-8') as f:
                json.dump(data, f, ensure_ascii=False, indent=2)
            
            print(f"Data byla exportována do souboru: {filename}")
            print(f"Exportováno: {len(users_data)} uživatelů, {len(posts_data)} příspěvků")
            
        elif format.lower() == 'csv':
            # Export uživatelů do CSV
            users_filename = f"{output}_users.csv"
            with open(users_filename, 'w', newline='', encoding='utf-8') as f:
                if users_data:
                    writer = csv.DictWriter(f, fieldnames=users_data[0].keys())
                    writer.writeheader()
                    writer.writerows(users_data)
            
            # Export příspěvků do CSV
            posts_filename = f"{output}_posts.csv"
            with open(posts_filename, 'w', newline='', encoding='utf-8') as f:
                if posts_data:
                    writer = csv.DictWriter(f, fieldnames=posts_data[0].keys())
                    writer.writeheader()
                    writer.writerows(posts_data)
            
            print(f"Data byla exportována do souborů:")
            print(f"  - Uživatelé: {users_filename} ({len(users_data)} záznamů)")
            print(f"  - Příspěvky: {posts_filename} ({len(posts_data)} záznamů)")
        else:
            print("Nepodporovaný formát! Použijte 'json' nebo 'csv'")
            
    except Exception as e:
        print(f"Chyba při exportu dat: {e}")

@app.cli.command()
@click.option('--file', required=True, help='Cesta k souboru pro import')
@click.option('--clear', is_flag=True, help='Vymazat existující data před importem')
def import_data(file, clear):
    """Importuje data z JSON souboru do databáze."""
    try:
        if not os.path.exists(file):
            print(f"Soubor {file} neexistuje!")
            return
        
        if clear:
            print("Mazání existujících dat...")
            Post.query.delete()
            User.query.delete()
            db.session.commit()
            print("Existující data byla smazána.")
        
        # Načtení dat ze souboru
        with open(file, 'r', encoding='utf-8') as f:
            data = json.load(f)
        
        users_imported = 0
        posts_imported = 0
        
        # Import uživatelů
        if 'users' in data:
            for user_data in data['users']:
                # Kontrola, zda uživatel již neexistuje
                existing_user = User.query.filter_by(username=user_data['username']).first()
                if not existing_user:
                    # Parsování data narození
                    datum_narozeni = None
                    if user_data.get('datum_narozeni'):
                        datum_narozeni = datetime.fromisoformat(user_data['datum_narozeni']).date()
                    
                    # Parsování created_at
                    created_at = datetime.fromisoformat(user_data['created_at'])
                    
                    user = User(
                        username=user_data['username'],
                        email=user_data['email'],
                        datum_narozeni=datum_narozeni,
                        created_at=created_at
                    )
                    db.session.add(user)
                    users_imported += 1
                else:
                    print(f"Uživatel {user_data['username']} již existuje, přeskakuji...")
        
        # Commit uživatelů před importem příspěvků
        db.session.commit()
        
        # Import příspěvků
        if 'posts' in data:
            for post_data in data['posts']:
                # Najít uživatele podle jména autora
                author = User.query.filter_by(username=post_data['author']).first()
                if author:
                    created_at = datetime.fromisoformat(post_data['created_at'])
                    post = Post(
                        title=post_data['title'],
                        content=post_data['content'],
                        created_at=created_at,
                        user_id=author.id
                    )
                    db.session.add(post)
                    posts_imported += 1
                else:
                    print(f"Autor '{post_data['author']}' nebyl nalezen pro příspěvek '{post_data['title']}'")
        
        db.session.commit()
        
        print(f"Import dokončen!")
        print(f"Importováno: {users_imported} uživatelů, {posts_imported} příspěvků")
        
    except Exception as e:
        db.session.rollback()
        print(f"Chyba při importu dat: {e}")

if __name__ == '__main__':
    app.run(debug=True)
