#!/bin/bash
# stop_gunicorn.sh - Script to stop Gunicorn server

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${YELLOW}🛑 Stopping Gunicorn server...${NC}"

# Check if PID file exists
if [ -f "logs/gunicorn.pid" ]; then
    PID=$(cat logs/gunicorn.pid)
    echo -e "${BLUE}📋 Found PID: $PID${NC}"
    
    if kill -0 $PID 2>/dev/null; then
        echo -e "${YELLOW}Stopping Gunicorn process...${NC}"
        kill -TERM $PID
        
        # Wait for graceful shutdown
        for i in {1..10}; do
            if ! kill -0 $PID 2>/dev/null; then
                echo -e "${GREEN}✅ Gunicorn stopped successfully${NC}"
                rm -f logs/gunicorn.pid
                exit 0
            fi
            echo -e "${YELLOW}Waiting for graceful shutdown... ($i/10)${NC}"
            sleep 1
        done
        
        # Force kill if still running
        echo -e "${RED}⚠️ Forcing shutdown...${NC}"
        kill -KILL $PID 2>/dev/null
        rm -f logs/gunicorn.pid
        echo -e "${GREEN}✅ Gunicorn stopped (forced)${NC}"
    else
        echo -e "${YELLOW}⚠️ Process not running, removing stale PID file${NC}"
        rm -f logs/gunicorn.pid
    fi
else
    echo -e "${YELLOW}⚠️ No PID file found${NC}"
    
    # Try to find and kill gunicorn processes
    PIDS=$(pgrep -f "gunicorn.*wsgi:application")
    if [ -n "$PIDS" ]; then
        echo -e "${YELLOW}Found running Gunicorn processes: $PIDS${NC}"
        echo "$PIDS" | xargs kill -TERM
        echo -e "${GREEN}✅ Killed running processes${NC}"
    else
        echo -e "${GREEN}✅ No running Gunicorn processes found${NC}"
    fi
fi
