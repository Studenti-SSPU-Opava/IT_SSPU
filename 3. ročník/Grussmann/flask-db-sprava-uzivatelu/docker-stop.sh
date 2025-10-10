#!/bin/bash
# Skript pro zastavení a vyčištění Docker kontejneru

echo "🛑 Stopping Flask Docker container..."

# Zastavení kontejneru
if docker ps | grep -q flask-app-container; then
    docker stop flask-app-container
    echo "✅ Container stopped"
else
    echo "ℹ️  Container is not running"
fi

# Smazání kontejneru
if docker ps -a | grep -q flask-app-container; then
    docker rm flask-app-container
    echo "🗑️  Container removed"
else
    echo "ℹ️  Container does not exist"
fi

echo "🏁 Cleanup completed"
echo ""
echo "📊 Current Docker status:"
docker ps
