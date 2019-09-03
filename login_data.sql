CREATE DATABASE occ_veteran_club;

USE occ_veteran_club;

CREATE TABLE IF NOT EXISTS members(
	id VARCHAR(8) PRIMARY KEY NOT NULL,
    name VARCHAR(50) NOT NULL,
    branch VARCHAR(15) NOT NULL
    );
    
CREATE TABLE IF NOT EXISTS logins(
	id VARCHAR(8) NOT NULL,
    name VARCHAR(50) NOT NULL,
    date_time DATETIME NOT NULL
    );
    
CREATE TABLE IF NOT EXISTS admin(
	id VARCHAR(15) NOT NULL,
	name VARCHAR(5)
	);

REPLACE INTO admin
SET id = 'Got your 6',
name = 'ADMIN';
