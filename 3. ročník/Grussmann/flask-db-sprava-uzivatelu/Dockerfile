# Použití oficiálního Python 3.11 slim image
FROM python:3.11-slim

# Nastavení pracovního adresáře
WORKDIR /app

# Kopírování requirements.txt pro efektivní cache layery
COPY requirements.txt .

# Instalace Python závislostí
RUN pip install --no-cache-dir -r requirements.txt

# Kopírování aplikačních souborů
COPY . .

# Vytvoření non-root uživatele pro bezpečnost
RUN adduser --disabled-password --gecos '' appuser && \
    chown -R appuser:appuser /app
USER appuser

# Exponování portu
EXPOSE 8000

# Nastavení proměnných prostředí
ENV FLASK_APP=app.py
ENV FLASK_ENV=production
ENV PYTHONPATH=/app

# Vytvoření databáze při prvním spuštění
RUN flask db upgrade || echo "Database upgrade failed, will retry at runtime"

# Spuštění Gunicorn s konfigurací pro 2 CPU jádra
# 2 CPU × 2 + 1 = 5 worker procesů
CMD ["gunicorn", "--bind", "0.0.0.0:8000", "--workers", "5", "--worker-class", "sync", "--timeout", "120", "--max-requests", "1000", "--max-requests-jitter", "100", "--log-level", "info", "--access-logfile", "-", "--error-logfile", "-", "wsgi:app"]
