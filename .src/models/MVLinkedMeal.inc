<?php
class MVLinkedMeal extends ModelBaseClass {
    const TABLE_NAME = 'V_LINKED_MEAL';
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

    /** @var int */
    public $ref_id;
    /** @var int */
    public $meal_id;
    /** @var string */
    public $meal_name;
    /** @var int */
    public $linked_meal_id;
    /** @var string */
    public $linked_meal_name;
}
