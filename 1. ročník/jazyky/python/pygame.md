# změna adresáře:
cd /tmp\
# vytvoření pracovního adresáře
mkdir prace
# přepnutí do pracovního adresáře
cd prace
# vytvoření virtuálního python prostředí do složky .venv
python -m venv .venv
# zapnutí virtuálního python prostředí
. .venv/bin/activate
# v příkazovém řádku se musí objevit (.venv)
# instalace balíčku do virtálního python prostředí
pip install pygame
# pokud v adresáři existuje soubor requirement.txt můžete použít
pip install -r requirements.txt
# pokud chcete zmrazit vaše knihovny a poslat stav knihoven na github použijte
pip freeze > requirements.txt
