<?php
require_once __DIR__ . '/ModelBaseClass.inc';

class MUser extends ModelBaseClass {
    const TABLE_NAME = 'USER';
    const VIEW_NAME = 'V_USER';
    const KEY_NAME = 'ID';

    /** Contains a list of User IDs which are protected from removal */
    const PROTECTED_USER_IDS = [ 1, 2 ];

    /** @var int */
    public $id;
    public $username;
    public $PassHash;
    public $is_blocked;
    public $is_admin;
    public $is_batch;
    public $mail;

    /** Returns the Name of the Database Table of this object
     * @return string
     */
    public function getTableName() { return self::TABLE_NAME; }

    /** Returns the Name of the Database Table's Primary Key
     * @return string
     */
    public function getPrimaryKeyName() { return self::KEY_NAME; }

    /** Returns the rows Primary Key
     * @return int
     */
    public function getPrimaryKey() { return $this->id; }

    /**
     * Returns a new object with the data for the given primary key.
     * If the object could not be found, NULL will be returned.
     * @param $key mixed Primary Key Value
     * @return MUser|null
     */
    public function getByKey($key) { return parent::getByKey($key); }
}
