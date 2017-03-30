<?php
require_once __DIR__ . '/ModelBaseClass.inc';

class MMealIngredient extends ModelBaseClass {
    const TABLE_NAME = 'MEAL_INGREDIENT';
    const KEY_NAME = 'REF_ID';

    public function getTableName() { return self::TABLE_NAME; }
    public function getPrimaryKeyName() { return self::KEY_NAME; }
    /** @return int */
    public function getPrimaryKey() { return $this->ref_id; }
    /**
     * @param $key int Primary Key Value
     * @return MIngredient|null
     */
    public function getByKey($key) { return parent::getByKey($key); }

    /** @var int */
    public $ref_id;
    /** @var int */
    public $meal_id;
    /** @var int */
    public $ingredient_id;
    /** @var float */
    public $amount;
    /** @var string */
    public $amount_unit;

    /** @var MMeal */
    private $meal;
    /** @return MMeal|null */
    public function getMeal() {
        if (empty($this->meal)) {
            $m = new MMeal();
            $this->meal = $m->getByKey($this->meal_id);
        }
        return $this->meal;
    }

    /** @var MIngredient */
    private $ingredient;
    /** @return MIngredient|null */
    public function getIngredient() {
        if (empty($this->ingredient)) {
            $i = new MIngredient();
            $this->ingredient = $i->getByKey($this->ingredient_id);
        }
        return $this->ingredient;
    }

    /** @var MMeasuringUnit */
    private $unit;
    /** @return MMeasuringUnit|null */
    public function getAmountUnit() {
        if (empty($this->unit)) {
            $u = new MMeasuringUnit();
            $this->unit = $u->getByKey($this->amount_unit);
        }
        return $this->unit;
    }
}
