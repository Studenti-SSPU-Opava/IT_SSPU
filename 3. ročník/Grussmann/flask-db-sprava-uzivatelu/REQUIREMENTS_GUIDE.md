# Requirements Management

## 📁 Soubory dependencies

### **requirements.txt** (základní)
Automaticky generovaný seznam všech nainstalovaných balíčků pomocí `pip freeze`

### **requirements-organized.txt** (doporučený)
Organizovaný seznam s komentáři a skupinami:
- Flask Core Framework  
- Database & Migrations
- Forms & Validation
- Template Engine
- Development Dependencies

### **requirements-dev.txt**
Dodatečné balíčky pro development:
- Testing (pytest, coverage)
- Code Quality (flake8, black, pylint)
- Documentation (Sphinx)
- Performance Testing (locust)

### **requirements-prod.txt**
Produkční závislosti:
- WSGI server (gunicorn)
- Database drivers (PostgreSQL, MySQL)
- Monitoring (sentry, prometheus)
- Security (bcrypt, JWT)
- Caching (Redis)
- Rate limiting

## 🚀 Instalace

### **Development prostředí**
```bash
# Základní závislosti
pip install -r requirements.txt

# Nebo organizovaná verze
pip install -r requirements-organized.txt

# + Development nástroje
pip install -r requirements-dev.txt
```

### **Production prostředí**  
```bash
# Produkční závislosti (zahrnuje základní)
pip install -r requirements-prod.txt
```

### **Vytvoření nového virtuálního prostředí**
```bash
# Vytvoření prostředí
python -m venv .venv

# Aktivace
source .venv/bin/activate  # Linux/Mac
# nebo
.venv\Scripts\activate     # Windows

# Instalace dependencies
pip install -r requirements.txt
```

## 🔄 Aktualizace dependencies

### **Přidání nového balíčku**
```bash
# Instalace
pip install novy-balicek

# Aktualizace requirements
pip freeze > requirements.txt
```

### **Upgrade všech balíčků**
```bash
# Zobrazení zastaralých
pip list --outdated

# Upgrade konkrétního balíčku
pip install --upgrade flask

# Nebo použijte pip-tools pro správu
pip install pip-tools
pip-compile --upgrade requirements.in
```

## 📋 Kontrola závislostí

### **Bezpečnostní audit**
```bash
# Instalace nástroje
pip install safety

# Kontrola známých vulnerabilities
safety check

# Nebo pomocí pip-audit
pip install pip-audit
pip-audit
```

### **Analýza velikosti**
```bash
# Zobrazení velikosti balíčků
pip install pipdeptree
pipdeptree --packages flask

# Nebo
pip show flask
```

## 🎯 Současné dependencies (v projektu)

### **Core Flask Stack:**
- **Flask 3.1.2** - Mikroframework
- **SQLAlchemy 2.0.43** - ORM
- **Alembic 1.16.5** - Databázové migrace
- **Flask-WTF 1.2.2** - Formuláře a validace

### **Klíčové funkce:**
- ✅ **CSRF ochrana** - Flask-WTF
- ✅ **Databázové migrace** - Alembic  
- ✅ **Validace formulářů** - WTForms
- ✅ **SQLite databáze** - SQLAlchemy
- ✅ **Template engine** - Jinja2

### **Velikost instalace:**
```
Celková velikost: ~15-20 MB
Počet balíčků: 17
Python verze: 3.10+
```

## 🔒 Pinning verzí

Všechny verze jsou "pinnuté" (==) pro:
- ✅ **Reprodukovatelnost** - stejné verze všude
- ✅ **Stabilita** - žádné nečekané změny  
- ✅ **Bezpečnost** - kontrola nad updates

Pro flexibilnější verze můžete použít:
```
Flask>=3.1.0,<4.0.0  # Kompatibilní verze
Flask~=3.1.0         # Patch updates OK
```
