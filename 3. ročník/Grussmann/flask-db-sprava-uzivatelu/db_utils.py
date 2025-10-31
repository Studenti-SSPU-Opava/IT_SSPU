#!/usr/bin/env python3
"""
Utility skript pro export a import dat z Flask aplikace.
Může být spuštěn nezávisle na Flask CLI.
"""

import json
import csv
import os
import sys
from datetime import datetime

# Přidání aktuálního adresáře do Python path
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from app import app, db, User, Post

def export_to_json(filename='export.json'):
    """Exportuje všechna data do JSON souboru."""
    with app.app_context():
        try:
            # Export uživatelů
            users = User.query.all()
            users_data = [user.to_dict() for user in users]
            
            # Export příspěvků
            posts = Post.query.all()
            posts_data = [post.to_dict() for post in posts]
            
            # Vytvoření struktury dat
            data = {
                'users': users_data,
                'posts': posts_data,
                'exported_at': datetime.utcnow().isoformat(),
                'version': '1.0',
                'description': 'Export dat z Flask aplikace'
            }
            
            # Zápis do souboru
            with open(filename, 'w', encoding='utf-8') as f:
                json.dump(data, f, ensure_ascii=False, indent=2)
            
            print(f"✅ Data byla exportována do souboru: {filename}")
            print(f"📊 Exportováno: {len(users_data)} uživatelů, {len(posts_data)} příspěvků")
            return True
            
        except Exception as e:
            print(f"❌ Chyba při exportu: {e}")
            return False

def export_to_csv(prefix='export'):
    """Exportuje data do CSV souborů."""
    with app.app_context():
        try:
            # Export uživatelů
            users = User.query.all()
            users_data = [user.to_dict() for user in users]
            
            users_filename = f"{prefix}_users.csv"
            with open(users_filename, 'w', newline='', encoding='utf-8') as f:
                if users_data:
                    writer = csv.DictWriter(f, fieldnames=users_data[0].keys())
                    writer.writeheader()
                    writer.writerows(users_data)
            
            # Export příspěvků
            posts = Post.query.all()
            posts_data = [post.to_dict() for post in posts]
            
            posts_filename = f"{prefix}_posts.csv"
            with open(posts_filename, 'w', newline='', encoding='utf-8') as f:
                if posts_data:
                    writer = csv.DictWriter(f, fieldnames=posts_data[0].keys())
                    writer.writeheader()
                    writer.writerows(posts_data)
            
            print(f"✅ Data byla exportována do CSV souborů:")
            print(f"📄 Uživatelé: {users_filename} ({len(users_data)} záznamů)")
            print(f"📄 Příspěvky: {posts_filename} ({len(posts_data)} záznamů)")
            return True
            
        except Exception as e:
            print(f"❌ Chyba při exportu: {e}")
            return False

def import_from_json(filename, clear_data=False):
    """Importuje data z JSON souboru."""
    with app.app_context():
        try:
            if not os.path.exists(filename):
                print(f"❌ Soubor {filename} neexistuje!")
                return False
            
            if clear_data:
                print("🗑️  Mazání existujících dat...")
                Post.query.delete()
                User.query.delete()
                db.session.commit()
                print("✅ Existující data byla smazána.")
            
            # Načtení dat
            with open(filename, 'r', encoding='utf-8') as f:
                data = json.load(f)
            
            users_imported = 0
            posts_imported = 0
            users_skipped = 0
            posts_skipped = 0
            
            # Import uživatelů
            if 'users' in data:
                print("👥 Importuji uživatele...")
                for user_data in data['users']:
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
                        users_skipped += 1
                        print(f"⚠️  Uživatel {user_data['username']} již existuje, přeskakuji...")
            
            # Commit uživatelů
            db.session.commit()
            
            # Import příspěvků
            if 'posts' in data:
                print("📝 Importuji příspěvky...")
                for post_data in data['posts']:
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
                        posts_skipped += 1
                        print(f"⚠️  Autor '{post_data['author']}' nebyl nalezen pro příspěvek '{post_data['title']}'")
            
            db.session.commit()
            
            print(f"✅ Import dokončen!")
            print(f"📊 Výsledky:")
            print(f"   👥 Uživatelé: {users_imported} importováno, {users_skipped} přeskočeno")
            print(f"   📝 Příspěvky: {posts_imported} importováno, {posts_skipped} přeskočeno")
            return True
            
        except Exception as e:
            db.session.rollback()
            print(f"❌ Chyba při importu: {e}")
            return False

def create_sample_data():
    """Vytvoří ukázková data pro testování."""
    with app.app_context():
        try:
            # Vymazání existujících dat
            Post.query.delete()
            User.query.delete()
            
            # Vytvoření ukázkových uživatelů
            users_data = [
                {
                    'username': 'admin',
                    'email': 'admin@example.com',
                    'datum_narozeni': datetime(1985, 3, 15).date()
                },
                {
                    'username': 'jana_novakova',
                    'email': 'jana@example.com',
                    'datum_narozeni': datetime(1992, 7, 22).date()
                },
                {
                    'username': 'petr_svoboda',
                    'email': 'petr@example.com',
                    'datum_narozeni': None
                }
            ]
            
            users = []
            for user_data in users_data:
                user = User(**user_data)
                db.session.add(user)
                users.append(user)
            
            db.session.commit()
            
            # Vytvoření ukázkových příspěvků
            posts_data = [
                {
                    'title': 'Vítejte v našem blogu!',
                    'content': 'Toto je první příspěvek na našem novém blogu. Těšíme se na vaše příspěvky!',
                    'user_id': users[0].id
                },
                {
                    'title': 'Jak používat Flask',
                    'content': 'Flask je skvělý mikroframework pro Python. V tomto příspěvku si ukážeme základy...',
                    'user_id': users[1].id
                },
                {
                    'title': 'Databázové migrace s Alembic',
                    'content': 'Alembic nám umožňuje elegantně spravovat změny v databázovém schématu...',
                    'user_id': users[2].id
                }
            ]
            
            for post_data in posts_data:
                post = Post(**post_data)
                db.session.add(post)
            
            db.session.commit()
            
            print(f"✅ Ukázková data byla vytvořena!")
            print(f"👥 Vytvořeno: {len(users)} uživatelů")
            print(f"📝 Vytvořeno: {len(posts_data)} příspěvků")
            return True
            
        except Exception as e:
            db.session.rollback()
            print(f"❌ Chyba při vytváření ukázkových dat: {e}")
            return False

def main():
    """Hlavní funkce s interaktivním menu."""
    print("=" * 50)
    print("🗄️  DATABÁZOVÝ EXPORT/IMPORT UTILITY")
    print("=" * 50)
    
    while True:
        print("\nVyberte akci:")
        print("1. 📤 Exportovat data do JSON")
        print("2. 📤 Exportovat data do CSV")
        print("3. 📥 Importovat data z JSON")
        print("4. 🎯 Vytvořit ukázková data")
        print("5. 🚪 Ukončit")
        
        choice = input("\nVaše volba (1-5): ").strip()
        
        if choice == '1':
            filename = input("Název souboru (enter = export.json): ").strip()
            if not filename:
                filename = 'export.json'
            export_to_json(filename)
            
        elif choice == '2':
            prefix = input("Prefix souborů (enter = export): ").strip()
            if not prefix:
                prefix = 'export'
            export_to_csv(prefix)
            
        elif choice == '3':
            filename = input("Cesta k JSON souboru: ").strip()
            if filename:
                clear = input("Vymazat existující data? (y/N): ").strip().lower()
                import_from_json(filename, clear_data=clear == 'y')
            else:
                print("❌ Musíte zadat cestu k souboru!")
                
        elif choice == '4':
            confirm = input("Toto vymaže všechna existující data! Pokračovat? (y/N): ").strip().lower()
            if confirm == 'y':
                create_sample_data()
            else:
                print("❌ Akce zrušena.")
                
        elif choice == '5':
            print("👋 Nashledanou!")
            break
            
        else:
            print("❌ Neplatná volba!")

if __name__ == '__main__':
    main()
