# Docker Deployment Guide

## 🐳 Docker Konfigurace

### Specifikace
- **Base Image**: Python 3.11 slim
- **Gunicorn Workers**: 5 (2 CPU × 2 + 1)
- **Port**: 8000
- **User**: non-root (appuser) pro bezpečnost
- **Database**: SQLite s volume mount pro perzistenci

### Optimalizace pro 2 CPU jádra
- **Worker procesy**: 5 (optimálně pro 2 CPU jádra)
- **Worker třída**: sync
- **Timeout**: 120s
- **Max requests**: 1000 s jitter 100

## 🚀 Spuštění

### Metoda 1: Docker Run
```bash
# Build image
docker build -t flask-app .

# Spuštění kontejneru
docker run -d \
  --name flask-app-container \
  -p 8000:8000 \
  -v $(pwd)/app.db:/app/app.db \
  flask-app
```

### Metoda 2: Docker Compose
```bash
docker-compose up -d
```

### Metoda 3: Convenience skripty
```bash
./docker-run.sh    # Build a spuštění
./docker-stop.sh   # Zastavení a cleanup
```

## 🔧 Správa kontejneru

### Základní příkazy
```bash
# Zobrazit běžící kontejnery
docker ps

# Zobrazit logy
docker logs flask-app-container

# Zobrazit real-time logy
docker logs -f flask-app-container

# Zastavit kontejner
docker stop flask-app-container

# Smazat kontejner
docker rm flask-app-container

# Smazat image
docker rmi flask-app
```

### Debugging
```bash
# Připojit se do běžícího kontejneru
docker exec -it flask-app-container /bin/bash

# Zkontrolovat procesy v kontejneru
docker exec flask-app-container ps aux

# Zkontrolovat využití zdrojů
docker stats flask-app-container
```

## 📊 Monitorování

### Health Check
```bash
# API health check
curl http://localhost:8000/api

# Detailed health check
curl -f http://localhost:8000/api/users
```

### Performance Metrics
```bash
# Container stats
docker stats flask-app-container

# Memory usage
docker exec flask-app-container cat /proc/meminfo

# CPU usage
docker exec flask-app-container top
```

## 🔒 Bezpečnost

### Implementované bezpečnostní opatření:
- ✅ **Non-root user**: Aplikace běží pod uživatelem `appuser`
- ✅ **Minimal base image**: Python 3.11 slim pro menší attack surface
- ✅ **No cache pip install**: Menší image size
- ✅ **dockerignore**: Vyloučení citlivých souborů
- ✅ **Volume mount**: Databáze mimo kontejner

### Doporučení pro produkci:
```bash
# Použití secrets pro citlivé údaje
docker run -d \
  --name flask-app-container \
  -p 8000:8000 \
  -v $(pwd)/app.db:/app/app.db \
  -e FLASK_SECRET_KEY=$(openssl rand -hex 32) \
  flask-app
```

## 🌐 Nginx Reverse Proxy

### Nginx konfigurace pro Docker
```nginx
upstream flask_app {
    server 127.0.0.1:8000;
}

server {
    listen 80;
    server_name yourdomain.com;

    location / {
        proxy_pass http://flask_app;
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_set_header X-Forwarded-Proto $scheme;
    }
}
```

## 📈 Scaling

### Docker Compose pro multiple instances
```yaml
version: '3.8'
services:
  flask-app:
    build: .
    ports:
      - "8000-8002:8000"
    deploy:
      replicas: 3
    volumes:
      - ./app.db:/app/app.db
```

### Load balancer setup
```bash
# Nginx pro load balancing
upstream flask_cluster {
    server 127.0.0.1:8000;
    server 127.0.0.1:8001;
    server 127.0.0.1:8002;
}
```

## ✅ Testováno

### Funkční testy:
- ✅ **Docker build**: Úspěšný build image
- ✅ **Container startup**: 5 Gunicorn worker procesů
- ✅ **API endpoints**: Všechny REST endpointy funkční
- ✅ **Database**: SQLite databáze přístupná s daty
- ✅ **Performance**: Optimalizováno pro 2 CPU jádra
- ✅ **Logging**: Gunicorn logy dostupné přes `docker logs`

### Poslední test (2025-10-07 11:58):
```
Container: flask-app-container ✅ RUNNING
Port: 8000 ✅ ACCESSIBLE  
Workers: 5 ✅ ACTIVE
API: /api/users ✅ RESPONDING
Database: 4 users ✅ ACCESSIBLE
```

**Docker deployment je připraven k produkčnímu použití! 🚀**
