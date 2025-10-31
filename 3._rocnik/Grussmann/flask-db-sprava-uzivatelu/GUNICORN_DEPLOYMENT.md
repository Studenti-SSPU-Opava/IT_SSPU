# Gunicorn Deployment Guide

## 🚀 Produkční nasazení s Gunicorn

### **Rychlé spuštění**

```bash
# Development server (Flask)
make run

# Production server (Gunicorn)
make run-prod

# Background server
make start

# Zastavení serveru
make stop

# Restart serveru
make restart
```

## 📁 Vytvořené soubory

### **gunicorn.conf.py** - Konfigurace
- **Workers**: CPU cores × 2 + 1
- **Bind**: 0.0.0.0:8000
- **Timeout**: 30 sekund
- **Logging**: logs/access.log, logs/error.log
- **Max requests**: 1000 (restart workers)

### **wsgi.py** - WSGI entry point
- Standardní WSGI aplikace pro Gunicorn
- Import Flask app jako 'application'

### **Skripty**:
- **start_gunicorn.sh** - Spuštění serveru
- **stop_gunicorn.sh** - Zastavení serveru
- **flask-app.service** - Systemd service
- **nginx.conf** - Nginx reverse proxy

## ⚙️ Konfigurace

### **Gunicorn Workers**
```python
# Výpočet počtu workers
workers = multiprocessing.cpu_count() * 2 + 1

# Pro 4-core CPU = 9 workers
# Pro 2-core CPU = 5 workers  
# Pro 1-core CPU = 3 workers
```

### **Logging**
```bash
# Logy jsou uloženy v
logs/access.log     # HTTP požadavky
logs/error.log      # Chyby aplikace
logs/gunicorn.pid   # PID soubor
logs/startup.log    # Startup log
```

### **Performance nastavení**
- **preload_app**: True (rychlejší start)
- **worker_tmp_dir**: /dev/shm (RAM disk)
- **max_requests**: 1000 (memory leak protection)
- **timeout**: 30s (request timeout)

## 🔧 Production Setup

### **1. Systemd Service**
```bash
# Kopírování service souboru
sudo cp flask-app.service /etc/systemd/system/

# Úprava cest v souboru
sudo nano /etc/systemd/system/flask-app.service

# Aktivace služby
sudo systemctl daemon-reload
sudo systemctl enable flask-app
sudo systemctl start flask-app

# Kontrola stavu
sudo systemctl status flask-app
```

### **2. Nginx Reverse Proxy**
```bash
# Kopírování konfigurace
sudo cp nginx.conf /etc/nginx/sites-available/flask-app

# Aktivace site
sudo ln -s /etc/nginx/sites-available/flask-app /etc/nginx/sites-enabled/

# Test konfigurace
sudo nginx -t

# Restart Nginx
sudo systemctl restart nginx
```

### **3. Firewall**
```bash
# Povolení HTTP/HTTPS
sudo ufw allow 'Nginx Full'

# Nebo jen specifické porty
sudo ufw allow 80
sudo ufw allow 443
```

## 📊 Monitoring

### **Kontrola stavu**
```bash
# Gunicorn procesy
ps aux | grep gunicorn

# Listening porty
sudo netstat -tulpn | grep :8000

# System služba
sudo systemctl status flask-app

# Logy aplikace
tail -f logs/access.log
tail -f logs/error.log
```

### **Performance metriky**
```bash
# Memory usage
ps aux --sort=-%mem | grep gunicorn

# CPU usage  
top -p $(pgrep -d',' -f gunicorn)

# Disk usage
du -sh logs/
```

## 🔄 Hot Reload

### **Restart aplikace**
```bash
# Graceful restart (systemd)
sudo systemctl reload flask-app

# Restart workers (Gunicorn signal)
kill -HUP $(cat logs/gunicorn.pid)

# Nebo pomocí Makefile
make restart
```

### **Deploy nové verze**
```bash
# 1. Pull nový kód
git pull origin main

# 2. Aktivace prostředí
source .venv/bin/activate

# 3. Update dependencies
pip install -r requirements.txt

# 4. Migrace databáze
flask db upgrade

# 5. Restart aplikace
make restart
```

## 🛡️ Security

### **Environment Variables**
```bash
# Produkční .env soubor
cp env.example .env
nano .env

# Nastavit:
FLASK_ENV=production
FLASK_DEBUG=False
SECRET_KEY=<generate-new-secret>
```

### **File Permissions**
```bash
# Správné práva
chmod 755 start_gunicorn.sh stop_gunicorn.sh
chmod 644 gunicorn.conf.py wsgi.py
chmod 600 .env
```

### **SSL Certificate (Let's Encrypt)**
```bash
# Instalace Certbot
sudo apt install certbot python3-certbot-nginx

# Získání certifikátu
sudo certbot --nginx -d your-domain.com

# Auto-renewal test
sudo certbot renew --dry-run
```

## 🚨 Troubleshooting

### **Časté problémy**

#### **Port již používán**
```bash
# Najít proces na portu 8000
sudo lsof -i :8000

# Zabít proces
sudo kill -9 <PID>
```

#### **Permission denied**
```bash
# Zkontrolovat ownership
ls -la start_gunicorn.sh

# Opravit práva
chmod +x start_gunicorn.sh
```

#### **Workers se restartují**
```bash
# Zkontrolovat memory usage
free -h

# Zvýšit memory limit
# Nebo snížit počet workers v gunicorn.conf.py
```

#### **503 Bad Gateway (Nginx)**
```bash
# Zkontrolovat, zda Gunicorn běží
make stop && make start

# Zkontrolovat Nginx logy
sudo tail -f /var/log/nginx/error.log
```

## 📈 Performance Tuning

### **Hardware doporučení**
- **CPU**: Minimálně 2 cores pro produkci
- **RAM**: 1GB+ (závisle na počtu workers)
- **Disk**: SSD pro databázi a logy

### **Optimalizace workers**
```python
# Pro CPU-intensive aplikace
workers = cpu_count()

# Pro I/O-intensive aplikace  
workers = cpu_count() * 2 + 1

# Pro high-traffic
workers = cpu_count() * 3
```

Aplikace je nyní připravena pro produkční nasazení! 🎉
