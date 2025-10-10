#!/bin/bash
# start_gunicorn.sh - Script to start Gunicorn server

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}🚀 Starting Flask app with Gunicorn...${NC}"

# Check if virtual environment exists
if [ ! -d ".venv" ]; then
    echo -e "${RED}❌ Virtual environment not found!${NC}"
    echo -e "${YELLOW}Run: python -m venv .venv && source .venv/bin/activate && pip install -r requirements.txt${NC}"
    exit 1
fi

# Activate virtual environment
# shellcheck source=/dev/null
source ".venv/bin/activate"

# Check if gunicorn is installed
if ! command -v gunicorn &> /dev/null; then
    echo -e "${RED}❌ Gunicorn not installed!${NC}"
    echo -e "${YELLOW}Installing Gunicorn...${NC}"
    pip install gunicorn
fi

# Create logs directory if it doesn't exist
mkdir -p logs

# Set environment variables
export FLASK_ENV=production
export FLASK_DEBUG=False

# Start Gunicorn
echo -e "${GREEN}✅ Starting Gunicorn on http://0.0.0.0:8000${NC}"
echo -e "${BLUE}📋 Configuration:${NC}"
echo -e "  • Workers: $(python -c 'import multiprocessing; print(multiprocessing.cpu_count() * 2 + 1)')"
echo -e "  • Bind: 0.0.0.0:8000"
echo -e "  • Config: gunicorn.conf.py"
echo -e "  • Logs: logs/"

# Start Gunicorn with config file
exec gunicorn --config gunicorn.conf.py wsgi:application
