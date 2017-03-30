<?php
class MIngredient {
    const TABLE_NAME = 'INGREDIENT';
    const KEY_NAME = 'ID';

    public function getTableName() { return self::TABLE_NAME; }
    public function getPrimaryKeyName() { return self::KEY_NAME; }
    /** @return int */
    public function getPrimaryKey() { return $this->id; }
    /**
     * @param $key int Primary Key Value
     * @return MIngredient|null
     */
    public function getByKey($key) { return parent::getByKey($key); }

    /** @var int */
    public $id;
    /** @var string */
    public $name;
}
