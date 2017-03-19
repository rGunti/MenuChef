<?php
class DatabaseTools {
    /**
     * @return PDO
     */
    public static function getNewPdo() {
        return new PDO(
            "mysql:host=" . DbConfig::HOST .
            ";dbname=" . DbConfig::DB,
            DbConfig::USER,
            DbConfig::PASS, [
            PDO::ATTR_CASE                  => PDO::CASE_LOWER,
            PDO::ATTR_ERRMODE               => PDO::ERRMODE_EXCEPTION,
            PDO::ATTR_DEFAULT_FETCH_MODE    => PDO::FETCH_CLASS,
            PDO::ATTR_EMULATE_PREPARES      => false,
            PDO::ATTR_ORACLE_NULLS          => PDO::NULL_EMPTY_STRING,
            PDO::ATTR_AUTOCOMMIT            => false,
        ]);
    }

    /**
     * @param $sql string SQL statement
     * @param $pdo PDO|null PDO object to work with. If null, a new PDO object will be created
     * @return PDOStatement
     */
    public static function getPdoStatement($sql, $pdo = null) {
        Logger::debug("New PDO with SQL: $sql");
        if (is_null($pdo)) {
            $pdo = self::getNewPdo();
        }
        return $pdo->prepare($sql);
    }

    /**
     * @param $class
     * @param $sql string SQL statement
     * @param $pdo PDO|null PDO object to work with. If null, a new PDO object will be created
     * @return PDOStatement
     */
    public static function getPdoObjectStatement($class, $sql, $pdo = null) {
        $stmt = self::getPdoStatement($sql, $pdo);
        $stmt->setFetchMode(PDO::FETCH_CLASS | PDO::FETCH_PROPS_LATE, $class);
        return $stmt;
    }

    /**
     * Returns a new PDO object with a transaction started
     * @return PDO
     */
    public static function startNewTransaction() {
        $pdo = self::getNewPdo();
        Logger::debug("PDO Begin New Transaction");
        $pdo->beginTransaction();
        return $pdo;
    }

    /**
     * @param $pdo PDO
     */
    public static function commitTransaction($pdo) {
        Logger::debug("PDO Commit");
        $pdo->commit();
    }

    /**
     * @param $pdo PDO
     */
    public static function rollbackTransaction($pdo) {
        Logger::debug("PDO Rollback");
        $pdo->rollBack();
    }

    /**
     * Returns the class name of the object given.
     * If a string is given, the same string will be returned.
     * @param $o string|object Evaluation String / Object
     * @return string
     */
    public static function getClassName($o) {
        if (gettype($o) == 'object') {
            return get_class($o);
        } else {
            return $o;
        }
    }

    /**
     * @param $tbl string Table to select from
     * @param $classOrEmptyObj string|object Name of class or an empty instance of said class
     * @return array Returns an array of objects
     */
    public static function getAll($tbl, $classOrEmptyObj) {
        $objs = [];
        $objClass = self::getClassName($classOrEmptyObj);

        try {
            $stmt = self::getPdoObjectStatement($objClass, "SELECT * FROM $tbl");
            $stmt->execute();
            while ($obj = $stmt->fetch()) {
                array_push($objs, $obj);
            }
        } catch (PDOException $ex) {
            Logger::error("An error occured while fetching data: " . $ex->getMessage());
        }
        return $objs;
    }

    /**
     * @param $tbl string Table to select form
     * @param $classOrEmptyObj string|object Name of class or an empty instance of said class
     * @param $whereMap array Map containing the property and the value to check
     * @return array Returns an array of matching object
     */
    public static function getWhereSimple($tbl, $classOrEmptyObj, $whereMap) {
        $objs = [];
        $objClass = self::getClassName($classOrEmptyObj);

        $whereSqlArr = [];
        foreach ($whereMap as $whereCol => $whereVal) {
            array_push($whereSqlArr, "$whereCol = :$whereCol");
        }

        $whereSql = implode(" AND ", $whereSqlArr);
        $sql = "SELECT * FROM $tbl WHERE $whereSql";
        try {
            $stmt = self::getPdoObjectStatement($objClass, $sql);

            foreach ($whereMap as $whereCol => $whereVal) {
                Logger::verbose(" - Statement Parameter $whereCol = $whereVal");
                $stmt->bindValue(":$whereCol", $whereVal);
            }

            $stmt->execute();
            while ($obj = $stmt->fetch()) {
                array_push($objs, $obj);
            }
        } catch (PDOException $ex) {
            Logger::error("An error occured while fetching data: " . $ex->getMessage());
        }
        return $objs;
    }

    /**
     * Performs a more complex Select Where statement and returns its results
     * @param $tbl string Table to select from
     * @param $classOrEmptyObj string|object Name of class or an empty instance of said class
     * @param $whereArray TableWhereObject[] Array of TableWhereObjects to determine the where statement
     * @param $order string[] Columns to sort by
     * @param int $skip Items to skip
     * @param int $take Items to take
     * @return PagedResultObject
     */
    public static function getWhereAdv($tbl, $classOrEmptyObj, $whereArray, $order = [], $skip = 0, $take = -1) {
        $objs = [];
        $objsTotal = 0;
        $objsFilter = 0;
        $objClass = self::getClassName($classOrEmptyObj);

        $orderSql = self::renderOrderBySql($order);
        $limitSql = "LIMIT $skip, $take";

        $whereSqlArr = [];
        $binds = [];
        $paramCounter = 0;
        foreach ($whereArray as $whereCond) {
            array_push($whereSqlArr, $whereCond->getRenderSql($paramCounter));
            if ($whereCond->hasValue()) {
                $binds[":param$paramCounter"] = $whereCond->getValue();
            }
            $paramCounter++;
        }

        $whereSql = implode(" ", $whereSqlArr);
        $sql = "SELECT * FROM $tbl" . (empty($whereSql) ? " WHERE $whereSql" : "") . " $orderSql $limitSql";
        $totalCountSql = "SELECT COUNT(0) AS 'count' FROM $tbl";
        $filterCountSql = "$totalCountSql" . (empty($whereSql) ? " WHERE $whereSql" : "");

        try {
            // Count Total Rows
            $stmt = self::getPdoStatement($totalCountSql);
            $stmt->execute($binds);
            while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
                $objsTotal = $row['count'];
            }

            // Count Filtered Rows
            $stmt = self::getPdoStatement($filterCountSql);
            $stmt->execute($binds);
            while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
                $objsFilter = $row['count'];
            }

            // Get Data
            $stmt = self::getPdoObjectStatement($objClass, $sql);
            $stmt->execute($binds);
            while ($obj = $stmt->fetch()) {
                array_push($objs, $obj);
            }
        } catch (PDOException $ex) {
            // TODO: Add Error Handling
        }

        // Return Data
        return new PagedResultObject($objs, $objsTotal, $objsFilter);
    }

    /**
     * Returns a rendered SQL part-statement for ORDER BY
     * @param $cols string[] Columns to sort by
     * @return string
     */
    public static function renderOrderBySql($cols) {
        if (empty($cols) || count($cols) == 0) { return ""; }
        $sql = "ORDER BY " . implode(',', $cols);
        return $sql;
    }

    /**
     * Returns a password as a hashed and salted string
     * @param $password string Password
     * @return string Hashed and salted string
     */
    public static function hashNSaltPassword($password) {
        return hash('sha256', 'DRIVER/LOG-' . strrev($password));
    }

    /**
     * @param $table string Table to update
     * @param $key_col string The column containing the primary key
     * @param $key_value mixed The value of the primary key
     * @param $key_value_map array A map of properties and their values to update
     * @return int Rows effected
     */
    public static function update($table, $key_col, $key_value, $key_value_map) {
        // Pre-build SQL
        $params = [];
        foreach ($key_value_map as $col => $val) {
            array_push($params, "$col = :$col");
        }
        $params_sql = implode(",", $params);
        $sql = "UPDATE $table SET $params_sql WHERE $key_col = :PRIMARY_KEY";

        // Open PDO
        $pdo = self::startNewTransaction();
        try {
            // Bind SQL Params
            $stmt = self::getPdoStatement($sql, $pdo);
            foreach ($key_value_map as $col => $val) {
                if (is_array($val)) {
                    Logger::verbose(" - Statement Parameter $col = $val[0]");
                    $stmt->bindValue(":$col", $val[0], $val[1]);
                } else {
                    Logger::verbose(" - Statement Parameter $col = $val");
                    $stmt->bindValue(":$col", $val);
                }
            }
            Logger::verbose(" - Statement Parameter PRIMARY_KEY ($key_col) = $key_value");
            $stmt->bindValue(":PRIMARY_KEY", $key_value);
            $stmt->execute();

            Logger::verbose("Updated values in Table $table, rows affected: " . $stmt->rowCount());
            self::commitTransaction($pdo);
            return $stmt->rowCount();
        } catch (PDOException $ex) {
            Logger::fatal("An exception occurred while updating data: " . $ex->getMessage());
            self::rollbackTransaction($pdo);
            return 0;
        }
    }
}

class TableWhereObject {
    const COND_EQUALS = '=';
    const COND_LESS = '<';
    const COND_LESS_EQ = '<=';
    const COND_MORE = '>';
    const COND_MORE_EQ = '>=';
    const COND_LIKE = 'LIKE';
    const COND_NULL = 'IS NULL';
    const COND_NOT_NULL = 'NOT NULL';

    const PREFIX_AND = 'AND';
    const PREFIX_OR = 'OR';
    const PREFIX_BR_START = '(';
    const PREFIX_BR_END = ')';

    private $condition;
    private $column;
    private $value;
    private $prefix;
    private $suffix;

    /**
     * Creates a new TableWhereObject.
     * @param $column string Column name
     * @param $condition string Condition
     * @param $value object Value
     * @param null|string $prefix
     * @param null|string $suffix
     */
    public function __construct($column, $condition, $value, $prefix = null, $suffix = null) {
        $this->column = $column;
        $this->condition = $condition;

        $this->value = $value;

        $this->prefix = $prefix;
        $this->suffix = $suffix;
    }

    //public function getCondition() { return $this->condition; }
    //public function getColumn() { return $this->column; }

    public function hasValue() { return $this->value !== null; }
    public function getValue() { return $this->value; }

    public function hasPrefix() { return !empty($this->prefix); }
    public function getPrefix() { return $this->prefix; }

    public function hasSuffix() { return !empty($this->suffix); }
    public function getSuffix() { return $this->suffix; }

    public function getRenderSql($paramNum = 0) {
        $sql = "";
        if ($this->hasPrefix()) { $sql .= "$this->prefix "; }

        $sql .= "$this->column $this->condition";
        if ($this->hasValue()) { $sql .= " :param$paramNum"; }

        if ($this->hasSuffix()) { $sql .= " $this->suffix"; }
        return $sql;
    }

    /**
     * Returns a new TableWhereObject for an equals statement
     * @param $column string
     * @param $value object
     * @param null|string $prefix
     * @param null|string $suffix
     * @return TableWhereObject
     */
    public static function getEq($column, $value, $prefix = null, $suffix = null) {
        return new TableWhereObject($column, self::COND_EQUALS, $value, $prefix, $suffix);
    }
}

class PagedResultObject {
    /** @var int Total number of objects in table */
    public $objectsTotal;
    /** @var int Total number of objects in table when filter is applied */
    public $objectsFiltered;
    /** @var object[] Objects selected */
    public $objects;

    /**
     * Creates a new PagedResultObject.
     * @param array $objects Objects selected
     * @param int $c_total Total number of objects in table
     * @param int $c_filtered Total number of objects in table when filter is applied
     */
    public function __construct($objects = [], $c_total = 0, $c_filtered = 0) {
        $this->objects = $objects;
        $this->objectsTotal = $c_total;
        $this->objectsFiltered = $c_filtered;
    }
}
