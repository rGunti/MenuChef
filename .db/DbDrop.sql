-- DRIVER LOG DATABASE
-- Database Destruction Script
-- Used to drop the Database for DriverLog
-- NOTE: This script does not drop or select a schema!
-- NOTE: This script is optimized for MySQL databases!

-- Stop Execution to prevent accidental execution
EXIT;

-- User
TRUNCATE user;
DROP TABLE user;
