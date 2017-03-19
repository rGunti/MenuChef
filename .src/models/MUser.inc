<?php
class MUser {
    const TABLE_NAME = 'USER';
    const KEY_NAME = 'ID';

    public $id;
    public $username;
    public $PassHash;
    public $is_blocked;
    public $is_admin;
    public $is_batch;
    public $mail;
}
