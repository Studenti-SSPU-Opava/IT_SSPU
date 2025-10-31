#!/bin/bash

# Aktivace virtuálního prostředí
# shellcheck source=/dev/null
source ".venv/bin/activate"

# Kontrola, zda byla předána akce
if [ $# -eq 0 ]; then
    echo "=== DATABÁZOVÝ EXPORT/IMPORT ==="
    echo "Použití:"
    echo "  $0 export-json [filename]    - Export do JSON"
    echo "  $0 export-csv [prefix]       - Export do CSV"
    echo "  $0 import [filename] [clear] - Import z JSON"
    echo "  $0 sample-data               - Vytvoření ukázkových dat"
    echo "  $0 interactive               - Interaktivní režim"
    echo ""
    echo "Flask CLI příkazy:"
    echo "  flask export-data --format json --output backup"
    echo "  flask export-data --format csv --output backup"
    echo "  flask import-data --file backup.json --clear"
    echo ""
    echo "Spouštím interaktivní režim..."
    python db_utils.py
    exit 0
fi

case $1 in
    "export-json")
        filename=${2:-"backup_$(date +%Y%m%d_%H%M%S).json"}
        echo "📤 Exportuji data do JSON: $filename"
        flask export-data --format json --output "${filename%.*}"
        ;;
    "export-csv")
        prefix=${2:-"backup_$(date +%Y%m%d_%H%M%S)"}
        echo "📤 Exportuji data do CSV s prefixem: $prefix"
        flask export-data --format csv --output "$prefix"
        ;;
    "import")
        if [ -z "$2" ]; then
            echo "❌ Musíte zadat cestu k souboru pro import!"
            echo "Použití: $0 import soubor.json [clear]"
            exit 1
        fi
        
        if [ "$3" = "clear" ]; then
            echo "📥 Importuji data z $2 (s vymazáním existujících dat)"
            flask import-data --file "$2" --clear
        else
            echo "📥 Importuji data z $2"
            flask import-data --file "$2"
        fi
        ;;
    "sample-data")
        echo "🎯 Vytvářím ukázková data..."
        python -c "
from db_utils import create_sample_data
create_sample_data()
"
        ;;
    "interactive")
        echo "🖥️  Spouštím interaktivní režim..."
        python db_utils.py
        ;;
    *)
        echo "❌ Neznámá akce: $1"
        echo "Spusťte bez parametrů pro nápovědu."
        exit 1
        ;;
esac
