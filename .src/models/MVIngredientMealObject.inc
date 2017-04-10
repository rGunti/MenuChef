<?php
class MVIngredientMealObject extends ModelBaseClass {
    const TABLE_NAME = 'V_INGREDIENT_MEAL_LIST';
    const KEY_NAME = 'ID';

    public function getTableName() { return self::TABLE_NAME; }
    public function getPrimaryKeyName() { return self::KEY_NAME; }
    /** @return int */
    public function getPrimaryKey() { return $this->id; }
    /**
     * @param $key int Primary Key Value
     * @return MVMeal|null
     */
    public function getByKey($key) { return parent::getByKey($key); }

    /** @var int */
    public $id;
    /** @var string */
    public $name;
    /** @var int */
    public $meal_count;
}
