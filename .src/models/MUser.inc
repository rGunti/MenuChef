<?php
class MUser {
    const TABLE_NAME = 'USER';
    const VIEW_NAME = 'V_USER';
    const KEY_NAME = 'ID';

    /** Contains a list of User IDs which are protected from removal */
    const PROTECTED_USER_IDS = [ 1, 2 ];

    public $id;
    public $username;
    public $PassHash;
    public $is_blocked;
    public $is_admin;
    public $is_batch;
    public $mail;
}
