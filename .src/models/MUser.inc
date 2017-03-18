<?php
class MUser {
    const TABLE_NAME = 'USER';

    public $id;
    public $username;
    public $PassHash;
    public $Is_Blocked;
    public $is_admin;
    public $is_batch;
    public $mail;
}
