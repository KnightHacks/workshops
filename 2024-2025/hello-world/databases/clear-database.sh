#!/bin/bash

# Variables for database name, username, and password
DB_NAME="knighthacks"
DB_USER="dylan"
DB_PASSWORD="password123"

# Prompt for confirmation
read -p "Are you sure you want to completely reset the database '$DB_NAME' and user '$DB_USER'? This action cannot be undone. (y/n): " confirm
if [[ $confirm != "y" ]]; then
  echo "Operation canceled."
  exit 0
fi

# Start PostgreSQL service if it isn't running
echo "Ensuring PostgreSQL service is running..."
sudo service postgresql start

# Terminate all active connections to the database
echo "Terminating active connections to database '$DB_NAME'..."
sudo -u postgres psql << EOF
SELECT pg_terminate_backend(pg_stat_activity.pid)
FROM pg_stat_activity
WHERE pg_stat_activity.datname = '$DB_NAME'
  AND pid <> pg_backend_pid();
EOF

# Revoke all privileges and remove any grants related to the user
echo "Revoking all privileges and removing grants for user '$DB_USER'..."
sudo -u postgres psql << EOF
REVOKE ALL PRIVILEGES ON DATABASE $DB_NAME FROM $DB_USER;
REASSIGN OWNED BY $DB_USER TO postgres;
DROP OWNED BY $DB_USER;
EOF

# Drop the database and user as the postgres superuser
echo "Dropping existing database and user..."
sudo -u postgres psql << EOF
DROP DATABASE IF EXISTS $DB_NAME;
DROP USER IF EXISTS $DB_USER;
EOF

echo "Database '$DB_NAME' and user '$DB_USER' have been reset successfully with permissions."

