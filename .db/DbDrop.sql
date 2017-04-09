-- DRIVER LOG DATABASE
-- Database Destruction Script
-- Used to drop the Database for DriverLog
-- NOTE: This script does not drop or select a schema!
-- NOTE: This script is optimized for MySQL databases!

-- Stop Execution to prevent accidental execution
EXIT;

-- Drop Everything
DROP VIEW v_meal_list;
DROP VIEW v_meal_ingredient;
DROP TABLE meal_ingredient;
DROP TABLE meal;
DROP TABLE ingredient;
DROP TABLE measuring_units;

-- User
TRUNCATE user;
DROP VIEW v_user;
DROP TABLE user;
