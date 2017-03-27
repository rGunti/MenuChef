<?php

/**
 * A base class for Database Model Objects
 * Contains different utility and QoL functions to shorten code
 */
abstract class ModelBaseClass {
    /** Returns the Name of the Database Table of this object
     * @return string
     */
    public abstract function getTableName();

    /** Returns the Name of the Database Table's Primary Key
     * @return string
     */
    public abstract function getPrimaryKeyName();

    /** Returns the rows Primary Key
     * @return mixed
     */
    public abstract function getPrimaryKey();

    /**
     * Returns a new object with the data for the given primary key.
     * If the object could not be found, NULL will be returned.
     * @param $key mixed Primary Key Value
     * @return ModelBaseClass|null
     */
    public function getByKey($key) {
        $items = DatabaseTools::getWhereSimple(
            $this->getTableName(),
            $this,
            [ $this->getPrimaryKeyName() => $key ]
        );
        if (count($items) == 1) {
            return $items[0];
        } else {
            return null;
        }
    }
}