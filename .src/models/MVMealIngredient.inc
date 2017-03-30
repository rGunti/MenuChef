<?php
class MVMealIngredient extends ModelBaseClass {
    const TABLE_NAME = 'V_MEAL_INGREDIENT';
    const KEY_NAME = 'REF_ID';

    /** Returns the Name of the Database Table of this object
     * @return string
     */
    public function getTableName() { return self::TABLE_NAME; }

    /** Returns the Name of the Database Table's Primary Key
     * @return string
     */
    public function getPrimaryKeyName() { return self::KEY_NAME; }

    /** Returns the rows Primary Key
     * @return mixed
     */
    public function getPrimaryKey() { return $this->ref_id; }

    public $ref_id;
    public $meal_id;
    public $meal_name;
    public $ingredient_id;
    public $ingredient_name;
    public $amount;
    public $amount_unit;
    public $amount_text;
}
