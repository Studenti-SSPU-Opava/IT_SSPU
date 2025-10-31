#!/usr/bin/env python3
"""
WSGI entry point for Gunicorn deployment
"""

import os
import sys

# Add the current directory to Python path
sys.path.insert(0, os.path.dirname(__file__))

from app import app

# Gunicorn will look for 'application' callable
application = app

if __name__ == "__main__":
    # This won't be called when using Gunicorn, but useful for testing
    app.run(debug=False, host='0.0.0.0', port=8000)
