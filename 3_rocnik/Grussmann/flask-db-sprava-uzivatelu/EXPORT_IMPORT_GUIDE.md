# Přehled Export/Import nástrojů

## 📁 Soubory

### Hlavní aplikace
- **app.py** - Flask aplikace s integrovanými CLI příkazy
- **db_utils.py** - Samostatný Python utility skript  
- **db_backup.sh** - Bash wrapper skript

### Vytvořené export soubory
- **test_backup.json** - JSON export se všemi daty
- **test_backup_users.csv** - CSV export uživatelů
- **test_backup_posts.csv** - CSV export příspěvků
- **final_backup.json** - Finální JSON backup

## 🛠️ Způsoby použití

### 1. Flask CLI příkazy (doporučeno)
```bash
# Aktivace prostředí
source .venv/bin/activate

# Export
flask export-data --format json --output backup_$(date +%Y%m%d)
flask export-data --format csv --output backup_$(date +%Y%m%d)

# Import
flask import-data --file backup.json
flask import-data --file backup.json --clear
```

### 2. Bash skript (nejjednodušší)
```bash
# Export s automatickým časovým razítkem
./db_backup.sh export-json
./db_backup.sh export-csv

# Export s vlastním názvem
./db_backup.sh export-json muj_backup
./db_backup.sh export-csv muj_backup

# Import
./db_backup.sh import backup.json
./db_backup.sh import backup.json clear

# Ukázková data
./db_backup.sh sample-data

# Interaktivní menu
./db_backup.sh interactive
```

### 3. Python skript (pokročilé)
```bash
# Interaktivní režim s menu
python db_utils.py

# Nebo přímé volání funkcí
python -c "from db_utils import export_to_json; export_to_json('backup.json')"
python -c "from db_utils import import_from_json; import_from_json('backup.json')"
```

## 🔧 Funkce

### Export
- ✅ **JSON formát** - kompletní backup s metadaty
- ✅ **CSV formát** - separátní soubory pro analýzu  
- ✅ **Časové razítko** - automatické pojmenování souborů
- ✅ **Metadata** - verze, datum exportu, popis

### Import  
- ✅ **Bezpečný import** - kontrola duplicit
- ✅ **Transakční** - při chybě rollback
- ✅ **Volitelné vymazání** - čistý import
- ✅ **Podrobné logy** - informace o průběhu

### Ukázková data
- ✅ **3 testovací uživatelé** - s různými daty narození
- ✅ **3 testovací příspěvky** - propojené s autory
- ✅ **Realistická data** - pro testování aplikace

## 🚀 Rychlý start

```bash
# 1. Vytvoření ukázkových dat
./db_backup.sh sample-data

# 2. Export do JSON
./db_backup.sh export-json

# 3. Smazání dat a import zpět
flask reset-db
./db_backup.sh import backup_*.json

# 4. Kontrola dat
flask run
# Otevřete http://localhost:5000/users
```
