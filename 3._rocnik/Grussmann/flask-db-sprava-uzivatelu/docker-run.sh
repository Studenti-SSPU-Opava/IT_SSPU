#!/bin/bash
# Skript pro build a spuštění Docker kontejneru

echo "🐳 Building Docker image..."
docker build -t flask-app .

echo "🚀 Starting Flask application with Docker..."
docker run -d \
  --name flask-app-container \
  -p 8000:8000 \
  -v "$(pwd)"/app.db:/app/app.db \
  flask-app

echo "✅ Application is running on http://localhost:8000"
echo "📊 Container status:"
docker ps | grep flask-app

echo ""
echo "🔧 Useful commands:"
echo "  docker logs flask-app-container     - Zobrazit logy"
echo "  docker stop flask-app-container     - Zastavit kontejner"
echo "  docker rm flask-app-container       - Smazat kontejner"
