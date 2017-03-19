-- DRIVER LOG DATABASE
-- Database Initialisation Script
-- Used to create the initial Database for DriverLog
-- NOTE: This script does not create a schema!
-- NOTE: This script is optimized for MySQL databases!

-- User Table
CREATE TABLE user (
  ID int(11) NOT NULL AUTO_INCREMENT,
  USERNAME varchar(45) NOT NULL,
  PASSHASH varchar(64) NOT NULL DEFAULT '0',
  IS_BLOCKED tinyint(1) DEFAULT '0',
  IS_ADMIN tinyint(1) DEFAULT '0',
  IS_BATCH tinyint(1) DEFAULT '0',
  MAIL varchar(255) DEFAULT NULL,
  PRIMARY KEY (`ID`),
  UNIQUE KEY USERNAME_UNIQUE (USERNAME)
) ENGINE=InnoDB AUTO_INCREMENT=10000 DEFAULT CHARSET=utf8;

-- Insert Test Data
--    Initial Login Data:
--      admin : admin
--      batch : <is not allowed to log in>
--    Added users start with ID 10000.
--    Do not use IDs below 10000 as it represents the "reserved space" for User IDs
--    Do not change the fixed User IDs!
START TRANSACTION;
INSERT INTO user
      (ID ,USERNAME  , PASSHASH                                                          , IS_BLOCKED, IS_ADMIN, IS_BATCH, MAIL)
    VALUES
      (1  , 'admin'  , 'b85c4821cc44c42ac26d9b1bb87a55c57399c8cdae6fa63028c33ed52b68da75',          0,        1,        0, 'admin@example.com'),
      (2  , 'batch'  , '----------------------------------------------------------------',          0,        0,        1, 'batch@example.com')
;
COMMIT;
