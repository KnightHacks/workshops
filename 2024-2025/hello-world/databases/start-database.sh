#!/bin/bash

# Variables for database name, username, and password
DB_NAME="knighthacks"
DB_USER="dylan"
DB_PASSWORD="password123"

# Install PostgreSQL if not already installed
echo "Checking if PostgreSQL is installed..."
if ! command -v psql &> /dev/null
then
    echo "PostgreSQL not found. Installing..."
    sudo apt update
    sudo apt install -y postgresql postgresql-contrib
else
    echo "PostgreSQL is already installed."
fi

# Start PostgreSQL service
echo "Starting PostgreSQL service..."
sudo service postgresql start

# Run all commands as the postgres user
echo "Creating database and user as the postgres user..."
sudo -u postgres psql << EOF
-- Create the user and database
CREATE USER $DB_USER WITH ENCRYPTED PASSWORD '$DB_PASSWORD';
CREATE DATABASE $DB_NAME OWNER $DB_USER;

-- Set the new user as the owner of the public schema
ALTER SCHEMA public OWNER TO $DB_USER;

-- Grant all privileges on the public schema
GRANT ALL ON SCHEMA public TO $DB_USER;

-- Set default privileges for future tables created in the public schema
ALTER DEFAULT PRIVILEGES IN SCHEMA public GRANT ALL ON TABLES TO $DB_USER;
EOF

echo "Database '$DB_NAME' and user '$DB_USER' created successfully with full ownership and permissions."

# Connect to the PostgreSQL client as the new user
echo "Connecting to PostgreSQL client as $DB_USER..."
PGPASSWORD=$DB_PASSWORD psql -h localhost -U $DB_USER -d $DB_NAME

