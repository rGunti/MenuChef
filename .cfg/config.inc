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
}

class DbConfig {
    const HOST = "192.168.1.200";
    const USER = "menuchef";
    const PASS = "menuchef";
    const DB = "dev-menuchef";
}
