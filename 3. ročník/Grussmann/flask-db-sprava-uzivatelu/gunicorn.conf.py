# Gunicorn Configuration File
# gunicorn.conf.py

import multiprocessing
import os

# Server socket
bind = "0.0.0.0:8000"
backlog = 2048

# Worker processes
workers = multiprocessing.cpu_count() * 2 + 1
worker_class = "sync"
worker_connections = 1000
timeout = 30
keepalive = 2
max_requests = 1000
max_requests_jitter = 50
preload_app = True

# Restart workers after this many requests, to help prevent memory leaks
max_requests = 1000
max_requests_jitter = 100

# Logging
loglevel = "info"
accesslog = "logs/access.log"
errorlog = "logs/error.log"
access_log_format = '%(h)s %(l)s %(u)s %(t)s "%(r)s" %(s)s %(b)s "%(f)s" "%(a)s" %(D)s'

# Process naming
proc_name = 'flask_app'

# Server mechanics
daemon = False
pidfile = 'logs/gunicorn.pid'
user = None
group = None
tmp_upload_dir = None

# SSL (uncomment for HTTPS)
# keyfile = "/path/to/keyfile"
# certfile = "/path/to/certfile"

# Environment variables
raw_env = [
    'FLASK_ENV=production',
    'FLASK_DEBUG=False',
]

# Preload application for better performance
preload_app = True

# Worker temporary directory
worker_tmp_dir = "/dev/shm"

# Maximum size of HTTP request line in bytes
limit_request_line = 4094

# Maximum number of HTTP request header fields
limit_request_fields = 100

# Maximum size of HTTP request header field
limit_request_field_size = 8190
