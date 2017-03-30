<?php
require_once __DIR__ . '/ModelBaseClass.inc';

class MMeal extends ModelBaseClass {
    const TABLE_NAME = 'MEAL';
    const KEY_NAME = 'ID';

    public function getTableName() { return self::TABLE_NAME; }
    public function getPrimaryKeyName() { return self::KEY_NAME; }
    /** @return int */
    public function getPrimaryKey() { return $this->id; }
    /**
     * @param $key int Primary Key Value
     * @return MMeal|null
     */
    public function getByKey($key) { return parent::getByKey($key); }

    /** @var int */
    public $id;
    /** @var string */
    public $name;
    /** @var int */
    public $base_portion_size;
}
