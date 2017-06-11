-- DRIVER LOG DATABASE
-- Database Initialisation Script
-- Used to create the initial Database for DriverLog
-- NOTE: This script does not create a schema!
-- NOTE: This script is optimized for MySQL databases!

-- User Table (and views)
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
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE VIEW v_user AS
  SELECT
    ID, USERNAME, IS_BLOCKED, IS_ADMIN, IS_BATCH, MAIL
  FROM
    user
;

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
ALTER TABLE user AUTO_INCREMENT=10000;
COMMIT;

-- Meal Table
CREATE TABLE meal (
  ID int(11) NOT NULL AUTO_INCREMENT,
  NAME varchar(100) NOT NULL,
  BASE_PORTION_SIZE int(5) DEFAULT 1,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE measuring_units (
  NAME varchar(50) NOT NULL,
  SYMBOL varchar(10) DEFAULT NULL,
  SUPER_UNIT varchar(50) DEFAULT NULL,
  SUPER_UNIT_MULTIPLIER int(5) DEFAULT NULL,
  UNIT_GROUP varchar(50) DEFAULT 'unit_group_none',
  PRIMARY KEY (`NAME`),
  INDEX (`SUPER_UNIT`),
  FOREIGN KEY (`SUPER_UNIT`)
    REFERENCES measuring_units(`NAME`)
    ON DELETE RESTRICT,
  CONSTRAINT CHECK (
    (`SUPER_UNIT` IS NULL AND `SUPER_UNIT_MULTIPLIER` IS NULL) OR
    (`SUPER_UNIT` IS NOT NULL AND `SUPER_UNIT_MULTIPLIER` IS NOT NULL)
  ),
  UNIQUE KEY UNIT_SYMBOL_UNIQUE (SYMBOL)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE ingredient (
  ID int(11) NOT NULL AUTO_INCREMENT,
  NAME varchar(100) NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE meal_ingredient (
  REF_ID int(11) NOT NULL AUTO_INCREMENT,
  MEAL_ID int(11) NOT NULL,
  INGREDIENT_ID int(11) NOT NULL,
  AMOUNT decimal(10,3) NOT NULL,
  AMOUNT_UNIT varchar(50) NOT NULL,
  PRIMARY KEY (`REF_ID`),
  FOREIGN KEY (`MEAL_ID`)
    REFERENCES meal(`ID`)
    ON DELETE RESTRICT,
  FOREIGN KEY (`INGREDIENT_ID`)
    REFERENCES ingredient(`ID`)
    ON DELETE RESTRICT,
  FOREIGN KEY (`AMOUNT_UNIT`)
    REFERENCES measuring_units(`NAME`)
    ON DELETE RESTRICT
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- Create Views
CREATE VIEW v_meal_ingredient AS
  SELECT
    REF_ID,
    MEAL_ID,
    m.NAME AS MEAL_NAME,
    INGREDIENT_ID,
    i.NAME AS INGREDIENT_NAME,
    AMOUNT,
    AMOUNT_UNIT,
    TRIM(CONCAT(floor(AMOUNT), ' ', u.SYMBOL)) AS AMOUNT_TEXT
  FROM
    meal_ingredient mi
    LEFT JOIN ingredient i ON mi.INGREDIENT_ID = i.ID
    LEFT JOIN measuring_units u ON mi.AMOUNT_UNIT = u.NAME
    LEFT JOIN meal m ON mi.MEAL_ID = m.ID
;

-- Insert Default Data
INSERT INTO measuring_units
      (UNIT_GROUP, NAME, SYMBOL, SUPER_UNIT, SUPER_UNIT_MULTIPLIER)
    VALUES
      -- Leer
      ('unit_group_null', 'unit_none', '', null, null),
      -- Gewicht
      ('unit_group_weight', 'unit_mg', 'mg', null, null),
      ('unit_group_weight', 'unit_g', 'g', 'unit_mg', 1000),
      ('unit_group_weight', 'unit_kg', 'kg', 'unit_g', 1000),
      -- Flüssigmasse
      ('unit_group_fluid', 'unit_ml', 'ml', null, null),
      ('unit_group_fluid', 'unit_cl', 'cl', 'unit_ml', 10),
      ('unit_group_fluid', 'unit_dl', 'dl', 'unit_cl', 10),
      ('unit_group_fluid', 'unit_l', 'l', 'unit_dl', 10),
      -- Weitere
      ('unit_group_other', 'unit_pack', 'Päck.', null, null),
      ('unit_group_other', 'unit_tl', 'TL', null, null),
      ('unit_group_other', 'unit_el', 'EL', null, null),
      ('unit_group_other', 'unit_tr', 'Tr', null, null),
      ('unit_group_other', 'unit_sp', 'Sp', null, null),
      ('unit_group_other', 'unit_pr', 'Pr', null, null),
      ('unit_group_other', 'unit_tas', 'Tas', null, null),
      ('unit_group_other', 'unit_bd', 'Bd', null, null),
      ('unit_group_other', 'unit_sc', 'Sc', null, null)
;

-- Set Auto Increments
ALTER TABLE meal AUTO_INCREMENT=10000;
ALTER TABLE ingredient AUTO_INCREMENT=10000;
ALTER TABLE meal_ingredient AUTO_INCREMENT=10000;

-- Add View for Meal List
CREATE VIEW v_meal_list AS
  SELECT
    m.ID as ID,
    m.NAME as NAME,
    (SELECT COUNT(mi.REF_ID) FROM meal_ingredient mi WHERE mi.MEAL_ID = m.ID) AS INGR_COUNT
  FROM
    meal m
;

CREATE VIEW v_ingredient_meal_list AS
  SELECT
    i.ID as ID,
    i.NAME as NAME,
    (SELECT COUNT(mi.REF_ID) FROM meal_ingredient mi WHERE mi.INGREDIENT_ID = i.ID) as MEAL_COUNT
  FROM
    ingredient i
;

-- Add Notes to Meal
ALTER TABLE meal ADD COLUMN NOTES LONGTEXT NULL AFTER BASE_PORTION_SIZE;

-- Add Support for decimal units
DROP VIEW v_meal_ingredient;
CREATE VIEW v_meal_ingredient AS
  SELECT
    REF_ID,
    MEAL_ID,
    m.NAME AS MEAL_NAME,
    INGREDIENT_ID,
    i.NAME AS INGREDIENT_NAME,
    AMOUNT,
    AMOUNT_UNIT,
    u.SYMBOL AS UNIT_SYMBOL
  FROM
    meal_ingredient mi
    LEFT JOIN ingredient i ON mi.INGREDIENT_ID = i.ID
    LEFT JOIN measuring_units u ON mi.AMOUNT_UNIT = u.NAME
    LEFT JOIN meal m ON mi.MEAL_ID = m.ID
;

-- Add Linked Meals
CREATE TABLE linked_meal (
  REF_ID int(11) NOT NULL AUTO_INCREMENT,
  MEAL_ID int(11) NOT NULL,
  LINKED_MEAL_ID int(11) NOT NULL,
  PRIMARY KEY (REF_ID),
  FOREIGN KEY (MEAL_ID)
    REFERENCES meal(ID)
    ON DELETE RESTRICT,
  FOREIGN KEY (LINKED_MEAL_ID)
    REFERENCES meal(ID)
    ON DELETE RESTRICT
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
ALTER TABLE linked_meal AUTO_INCREMENT=10000;

CREATE VIEW v_linked_meal AS
  SELECT
    REF_ID,
    MEAL_ID,
    bm.NAME AS MEAL_NAME,
    LINKED_MEAL_ID,
    m.NAME AS LINKED_MEAL_NAME
  FROM
    linked_meal lmt
    LEFT JOIN meal bm ON lmt.MEAL_ID = bm.ID
    LEFT JOIN meal m ON lmt.LINKED_MEAL_ID = m.ID
;
