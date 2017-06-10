<?php
class AppConfig {
    const APP_NAME = "MenuChef";
    const APP_VERSION = "0.1";
    const INSTANCE_NAME = "dev";
    const SHOW_INSTANCE_NAME = true;

    const LOG_ENABLED = true;
    const LOG_MIN_LEVEL = 0;
    const LOG_DATE_PATTERN = 'Y-m-d H:i:s P';
    const LOG_DYN_REQUIRES = false;
    const LOG_REQUESTS = true;
    const LOG_PATH = "C:/temp/menuchef.%date%.log";

    const FEEDBACK_MAIL = "feedback@rgunti.ch";
    const FEEDBACK_SUBJECT = "feedback_subject";
}

class DbConfig {
    const HOST = "192.168.1.250";
    const USER = "dev-menuchef";
    const PASS = "dev-menuchef";
    const DB = "dev-menuchef";
    const CHAR_SET = "utf8";
}
