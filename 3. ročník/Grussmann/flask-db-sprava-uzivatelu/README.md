# Flask Správa Uživatelů - Kompletní Projekt

## 🎯 Přehled
Kompletní Flask aplikace pro správu uživatelů s produkčním nasazením pomocí Gunicorn.

### 🔧 Funkce
- **Web rozhraní** s Flask-WTF formuláři a CSRF ochranou
- **REST API** pro všechny CRUD operace
- **SQLite databáze** s Alembic migracemi
- **Export/Import dat** přes CLI příkazy
- **Produkční nasazení** s Gunicorn
- **Validace formulářů** s vlastními validátory

## 🚀 Rychlá instalace

```bash
# 1. Vytvoření virtuálního prostředí
make .venv
source .venv/bin/activate

# 2. Instalace závislostí
pip install -r requirements.txt

# 3. Inicializace databáze
flask db upgrade

# 4. Spuštění aplikace
flask run --port 5001
# NEBO produkční server:
./start_gunicorn.sh
```

## 📦 Requirements Management

### **Základní soubory:**
- `requirements.txt` - Všechny závislosti
- `requirements-organized.txt` - Organizovaná verze s komentáři  
- `requirements-dev.txt` - Development nástroje
- `requirements-prod.txt` - Produkční závislosti

### **Makefile příkazy:**
```bash
make venv          # Vytvoří virtuální prostředí
make install       # Nainstaluje základní závislosti
make install-dev   # + development nástroje
make run           # Spustí Flask server
make db-upgrade    # Aplikuje migrace
make requirements  # Aktualizuje requirements.txt
```

Více informací v [REQUIREMENTS_GUIDE.md](REQUIREMENTS_GUIDE.md)

## 🌐 Spuštění aplikace

### Vývojový server (Flask)
```bash
make run
# Aplikace běží na http://127.0.0.1:5001
```

### Produkční server (Gunicorn)
```bash
./start_gunicorn.sh
# Aplikace běží na http://127.0.0.1:8000
```

## 📱 Použití

### Web rozhraní
- **Domovská stránka**: http://127.0.0.1:5001/
- **Seznam uživatelů**: http://127.0.0.1:5001/users
- **Přidat uživatele**: http://127.0.0.1:5001/users/create

### REST API
- **GET /api** - Přehled API
- **GET /api/users** - Seznam všech uživatelů
- **POST /api/users** - Vytvoření nového uživatele
- **GET /api/users/<id>** - Detail uživatele
- **PUT /api/users/<id>** - Aktualizace uživatele
- **DELETE /api/users/<id>** - Smazání uživatele

## 🏗️ Struktura projektu
```
.
├── app.py              # Hlavní Flask aplikace
├── forms.py            # Flask-WTF formuláře
├── wsgi.py             # WSGI vstupní bod
├── gunicorn.conf.py    # Konfigurace Gunicorn
├── requirements.txt    # Python závislosti
├── Makefile           # Automatizované úlohy
├── start_gunicorn.sh  # Spuštění produkčního serveru
├── stop_gunicorn.sh   # Zastavení produkčního serveru
├── migrations/        # Alembic migrace
├── static/           # CSS styly
└── templates/        # HTML šablony

Databáze:
├── app.db            # SQLite databáze
```

## 🛠️ Databázový model

### User
- `id` - Primární klíč
- `username` - Unikátní uživatelské jméno
- `email` - Unikátní email
- `datum_narozeni` - Datum narození (volitelné)
- `created_at` - Datum vytvoření

## ⚡ Technologie
- **Flask 3.1.2** - Web framework
- **SQLAlchemy 2.0.43** - ORM
- **Alembic 1.16.5** - Databázové migrace
- **Flask-WTF 1.2.2** - Formuláře s CSRF ochranou
- **Gunicorn 23.0.0** - WSGI server pro produkci
- **SQLite** - Databáze

## 🚀 Produkční nasazení

### Gunicorn konfigurace
- **17 worker procesů** (2 × CPU jádra + 1)
- **Async worker třída** pro lepší výkon
- **Automatické restartování** při změnách kódu
- **Detailní logování**

## Dostupné Flask CLI příkazy

### Databázové migrace (Alembic)
```bash
# Aktivace virtuálního prostředí
source .venv/bin/activate

# Inicializace migrací (pouze jednou na začátku projektu)
flask db init

# Vytvoření nové migrace po změně modelů
flask db migrate -m "Popis změny"

# Aplikace migrací do databáze
flask db upgrade

# Vrácení zpět na předchozí migraci
flask db downgrade

# Zobrazení historie migrací
flask db history

# Zobrazení současného stavu databáze
flask db current
```

### Vlastní CLI příkazy
```bash
# Inicializace databáze (vytvoří všechny tabulky)
flask init-db

# Smazání všech tabulek
flask drop-db

# Reset databáze (smaže a znovu vytvoří)
flask reset-db

# Export dat
flask export-data --format json --output backup
flask export-data --format csv --output backup

# Import dat
flask import-data --file backup.json
flask import-data --file backup.json --clear  # s vymazáním existujících dat
```

### Utility skripty pro backup

#### Bash skript (db_backup.sh)
```bash
# Rychlý export s časovým razítkem
./db_backup.sh export-json
./db_backup.sh export-csv

# Import dat
./db_backup.sh import backup.json
./db_backup.sh import backup.json clear  # s vymazáním

# Vytvoření ukázkových dat
./db_backup.sh sample-data

# Interaktivní režim
./db_backup.sh interactive
```

#### Python utility (db_utils.py)
```bash
# Interaktivní režim s menu
python db_utils.py
```

### Spuštění aplikace
```bash
# Spuštění vývojového serveru
flask run

# Nebo
python app.py
```

## Workflow pro práci s migracemi

1. **Inicializace projektu** (pouze jednou):
   ```bash
   flask db init
   flask db migrate -m "Initial migration"
   flask db upgrade
   ```

2. **Po změně modelů**:
   ```bash
   flask db migrate -m "Popis změny"
   flask db upgrade
   ```

3. **Kontrola stavu**:
   ```bash
   flask db current
   flask db history
   ```

## Struktura projektu
```
├── app.py              # Hlavní Flask aplikace
├── app.db              # SQLite databáze
├── migrations/         # Alembic migrace
│   ├── versions/       # Soubory migrací
│   ├── alembic.ini     # Konfigurace
│   ├── env.py          # Prostředí migrací
│   └── script.py.mako  # Šablona pro migrace
└── .venv/              # Virtuální prostředí
```

## Modely databáze

## 🧪 Testování

### Test API
```bash
# Získání seznamu uživatelů
curl http://127.0.0.1:8000/api/users

# Vytvoření nového uživatele
curl -X POST http://127.0.0.1:8000/api/users \
  -H "Content-Type: application/json" \
  -d '{"username": "novak", "email": "novak@example.com", "datum_narozeni": "1990-01-01"}'
```

### Ovládání produkčního serveru
```bash
./start_gunicorn.sh    # Spuštění
./stop_gunicorn.sh     # Zastavení
```

## ✅ Stav projektu
**KOMPLETNÍ** - Plně funkční Flask aplikace s produkčním nasazením

### Ověřené funkce:
- ✅ Virtuální prostředí (.venv)
- ✅ Flask aplikace s web rozhraním
- ✅ SQLite databáze s Alembic migracemi
- ✅ User model s polem datum_narozeni
- ✅ Flask-WTF formuláře s validací
- ✅ REST API pro všechny CRUD operace
- ✅ Export/Import funkcionalita
- ✅ Gunicorn produkční server
- ✅ Kompletní dokumentace a konfigurační soubory

### Poslední test (2025-10-07 11:50):
- **Gunicorn server**: ✅ Běží na portu 8000 se 17 worker procesy
- **API endpoint**: ✅ Funkční (GET /api/users, POST /api/users)
- **Web rozhraní**: ✅ Dostupné na hlavní URL
- **Databáze**: ✅ Funkční s 4 testovacími uživateli

**Projekt je připraven k produkčnímu použití.**

### Uživatelé
- **GET /api/users** - Seznam všech uživatelů
- **POST /api/users** - Vytvoření nového uživatele
  ```json
  {
    "username": "jmeno_uzivatele",
    "email": "email@example.com",
    "datum_narozeni": "1990-05-15"  // volitelné, formát YYYY-MM-DD
  }
  ```
- **GET /api/users/<id>** - Detail uživatele
- **PUT /api/users/<id>** - Aktualizace uživatele

### Webové rozhraní
- **/** - Domovská stránka
- **/users** - Seznam uživatelů
- **/users/create** - Formulář pro vytvoření uživatele
- **/users/<id>/edit** - Formulář pro editaci uživatele

## Historie migrací
1. `f5b21d661486` - Initial migration (User, Post tabulky)
2. `f0efb12d829a` - Přidání pole datum_narozeni do tabulky user

## Export/Import dat

### Podporované formáty

#### JSON Export
- **Soubor**: `backup.json`
- **Struktura**: Obsahuje uživatele, příspěvky, metadata
- **Výhody**: Zachovává vztahy, obsahuje metadata
- **Použití**: Kompletní backup systému

#### CSV Export  
- **Soubory**: `backup_users.csv`, `backup_posts.csv`
- **Struktura**: Samostatné soubory pro každou tabulku
- **Výhody**: Snadné otevření v Excel/LibreOffice
- **Použití**: Analýza dat, ruční editace

### Ukázková struktura JSON exportu
```json
{
  "users": [
    {
      "id": 1,
      "username": "admin",
      "email": "admin@example.com",
      "datum_narozeni": "1985-03-15",
      "created_at": "2025-10-07T10:30:00"
    }
  ],
  "posts": [
    {
      "id": 1,
      "title": "Vítejte!",
      "content": "První příspěvek...",
      "created_at": "2025-10-07T10:35:00",
      "author": "admin"
    }
  ],
  "exported_at": "2025-10-07T13:20:00",
  "version": "1.0"
}
```

### Bezpečnostní funkce
- ✅ **Kontrola existujících dat** - duplicity se přeskakují
- ✅ **Transakční import** - při chybě se vše vrátí zpět  
- ✅ **Volitelné vymazání** - `--clear` flag pro čistý import
- ✅ **Validace dat** - kontrola formátů datumů
- ✅ **Podrobné logy** - informace o průběhu operace
