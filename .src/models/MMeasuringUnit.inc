<?php
require_once __DIR__ . '/ModelBaseClass.inc';

class MMeasuringUnit extends ModelBaseClass {
    const TABLE_NAME = 'MEASURING_UNITS';
    const KEY_NAME = 'NAME';

    public function getTableName() { return self::TABLE_NAME; }
    public function getPrimaryKeyName() { return self::KEY_NAME; }
    /** @return string */
    public function getPrimaryKey() { return $this->name; }
    /**
     * @param $key string Primary Key Value
     * @return MMeasuringUnit|null
     */
    public function getByKey($key) { return parent::getByKey($key); }

    /** @var string */
    public $name;
    /** @var string */
    public $symbol;
    /** @var string|null */
    public $super_unit;
    /** @var int|null */
    public $super_unit_multiplier;
    /** @var string */
    public $unit_group;

    /** @return bool */
    public function hasSuperUnit() { return !is_null($this->super_unit); }
    /** @return MMeasuringUnit|null */
    public function getSuperUnit() {
        if ($this->hasSuperUnit()) {
            return $this->getByKey($this->super_unit);
        } else {
            return null;
        }
    }

    /**
     * Returns a sorted map of Measuring Units (Key of Array: Super Unit)
     * @return MMeasuringUnit[]
     */
    public function getUnitMap() {
        /** @var MMeasuringUnit[] $units */
        $units = DatabaseTools::getAll($this->getTableName(), $this);
        $map = [];
        foreach ($units as $unit) {
            if (!array_key_exists($unit->unit_group, $map)) {
                $map[$unit->unit_group] = [];
            }
            array_push($map[$unit->unit_group], $unit);
        }
        return $map;
    }
}
