-- DRIVER LOG DATABASE
-- Database Reset Script
-- Used to reset the login credentials for the super admin
-- NOTE: This script does not create a schema!
-- NOTE: This script is optimized for MySQL databases!

-- Default Login Credentials are:
--    admin : admin
START TRANSACTION;
UPDATE user
SET
  USERNAME = 'admin',
  PASSHASH = 'b85c4821cc44c42ac26d9b1bb87a55c57399c8cdae6fa63028c33ed52b68da75'
WHERE
  ID = 1
;
COMMIT;
