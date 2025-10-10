# Flask Project Makefile

.PHONY: install install-dev install-prod venv clean test lint format requirements help run run-prod start stop restart

# Default virtual environment name
VENV_NAME = .venv
PYTHON = $(VENV_NAME)/bin/python
PIP = $(VENV_NAME)/bin/pip
FLASK = $(VENV_NAME)/bin/flask

# Help command
help:
	@echo "Available commands:"
	@echo "  install      - Install basic dependencies"
	@echo "  install-dev  - Install development dependencies"  
	@echo "  install-prod - Install production dependencies"
	@echo "  venv         - Create virtual environment"
	@echo "  clean        - Remove virtual environment"
	@echo "  test         - Run tests"
	@echo "  lint         - Run code linting"
	@echo "  format       - Format code with black"
	@echo "  requirements - Update requirements.txt"
	@echo "  run          - Run Flask development server"
	@echo "  run-prod     - Run with Gunicorn (production)"
	@echo "  start        - Start Gunicorn in background"
	@echo "  stop         - Stop Gunicorn server"
	@echo "  restart      - Restart Gunicorn server"
	@echo "  shell        - Open Flask shell"
	@echo "  db-init      - Initialize database"
	@echo "  db-migrate   - Create migration"
	@echo "  db-upgrade   - Apply migrations"

# Create virtual environment
venv:
	python3 -m venv $(VENV_NAME)
	$(PIP) install --upgrade pip
	@echo "Virtual environment created. Activate with: source $(VENV_NAME)/bin/activate"

# Install basic dependencies
install: venv
	$(PIP) install -r requirements.txt
	@echo "Basic dependencies installed"

# Install development dependencies
install-dev: install
	$(PIP) install -r requirements-dev.txt
	@echo "Development dependencies installed"

# Install production dependencies  
install-prod: venv
	$(PIP) install -r requirements-prod.txt
	@echo "Production dependencies installed"

# Clean virtual environment
clean:
	rm -rf $(VENV_NAME)
	@echo "Virtual environment removed"

# Update requirements.txt
requirements:
	$(PIP) freeze > requirements.txt
	@echo "Requirements updated"

# Run Flask development server
run:
	$(FLASK) run --debug --port 5001

# Run with Gunicorn (production)
run-prod:
	./start_gunicorn.sh

# Start Gunicorn in background
start:
	@echo "Starting Gunicorn server in background..."
	@nohup ./start_gunicorn.sh > logs/startup.log 2>&1 &
	@echo "Server starting... Check logs/startup.log for details"

# Stop Gunicorn server
stop:
	./stop_gunicorn.sh

# Restart Gunicorn server
restart: stop start

# Open Flask shell
shell:
	$(FLASK) shell

# Database commands
db-init:
	$(FLASK) db init

db-migrate:
	$(FLASK) db migrate -m "Migration"

db-upgrade:
	$(FLASK) db upgrade

# Development tools (requires dev dependencies)
test:
	$(PYTHON) -m pytest tests/ -v

lint:
	$(PYTHON) -m flake8 app.py forms.py
	$(PYTHON) -m pylint app.py forms.py

format:
	$(PYTHON) -m black app.py forms.py

# Security check
security:
	$(PYTHON) -m safety check

# Install everything for development
setup-dev: install-dev db-upgrade
	@echo "Development environment ready!"
	@echo "Run 'make run' to start the server"
