<?php
session_start();

class Session {
    /**
     * @return bool True, if user is logged in
     */
    public static function isLoggedIn() { return !empty(self::getUserInfo()); }

    /**
     * Checks if the user is logged in.
     * If not the application will redirect the user to a given internal URL (if no URL is given, the Home Page is used)
     * @param $redirect_url string Direct URL which will be used if the user is not logged in (default: '/')
     * @param $add_redirect_url bool If true, a GET parameter ('to') will be added to the URL indicating where the last
     * request went to
     */
    public static function enforceLoggedIn($redirect_url = "/Login", $add_redirect_url = true) {
        if (!self::isLoggedIn()) {
            Logger::error("Session enforcement failed at " . PathUtils::getCurrentPath() . ", falling back to $redirect_url");
            Session::addNotification(new SessionNotification(
                'error_navigation_login_needed', [],
                'error_navigation_login_needed_content', [],
                SessionNotification::LEVEL_WARN
            ));
            $url = ($add_redirect_url) ? "$redirect_url?to=" . urlencode(PathUtils::getCurrentPath()) : $redirect_url;
            PathUtils::internalRedirect($url);
            exit(0);
        }
    }

    private static $loggedInUser;

    /**
     * @return MUser|null Info about logged in user, NULL is not logged in
     */
    public static function getUserInfo() {
        if (empty(@$_SESSION['session_user'])) { return null; }
        else if (empty(self::$loggedInUser)) {
            $user = new MUser();
            $user->id = $_SESSION['session_user']['id'];
            $user->username = $_SESSION['session_user']['name'];
            $user->is_admin = $_SESSION['session_user']['is_admin'];
            $user->is_batch = $_SESSION['session_user']['is_batch'];
            $user->mail = $_SESSION['session_user']['mail'];
            self::$loggedInUser = $user;
        }
        return self::$loggedInUser;
    }

    /**
     * Logs in the given user
     * @param $user MUser
     * @param $onlyUpdate bool If true, the session-stored user info will only be updated.
     */
    public static function login($user, $onlyUpdate = false) {
        $_SESSION['session_user']['id'] = $user->id;
        $_SESSION['session_user']['name'] = $user->username;
        $_SESSION['session_user']['is_admin'] = $user->is_admin;
        $_SESSION['session_user']['is_batch'] = $user->is_batch;
        $_SESSION['session_user']['mail'] = $user->mail;
        if (!$onlyUpdate) {
            $_SESSION['session_user']['login_at'] = date('U');
        }
        self::$loggedInUser = $user;
    }

    /** Destroys the current session and therefor logs the user out */
    public static function logout() {
        $_SESSION['session_user'] = null;
        //session_destroy();
        //session_unset();
        //session_start();
    }

    /**
     * @param $key string
     * @return mixed
     */
    public static function getSessionInfo($key) {
        return $_SESSION['session_user'][$key];
    }

    /**
     * @param $key string Session Info Key
     * @param $value mixed
     */
    public static function setSessionInfo($key, $value) {
        $_SESSION['session_user'][$key] = $value;
    }

    public static function getAllSessionInfo() {
        return $_SESSION['session_user'];
    }

    /**
     * Gets all Session-stored Notifications as Objects. Returns an empty array if none are present.
     * @return SessionNotification[]
     */
    public static function getAllNotifications() {
        $notifications = @$_SESSION['notifications'];
        if (is_array($notifications) && count($notifications) >= 1) {
            $objs = [];
            foreach ($notifications as $notification) {
                array_push($objs, unserialize($notification));
            }
            return $objs;
        } else {
            return [];
        }
    }

    /**
     * @param $notifications SessionNotification[]
     */
    public static function setAllNotifications($notifications) {
        $serNotifications = [];
        foreach ($notifications as $notification) {
            array_push($serNotifications, serialize($notification));
        }
        $_SESSION['notifications'] = $serNotifications;
    }

    /**
     * Clears all Session-stored notifications
     */
    public static function clearAllNotifications() {
        $_SESSION['notifications'] = [];
    }

    /**
     * @param $notification SessionNotification
     */
    public static function addNotification($notification) {
        if (!isset($_SESSION['notifications'])) {
            $notifications = [];
        } else {
            $notifications = $_SESSION['notifications'];
        }
        array_push($notifications, serialize($notification));
        $_SESSION['notifications'] = $notifications;
    }
}

class SessionNotification {
    const LEVEL_SUCCESS = "alert-success";
    const LEVEL_INFO = "alert-info";
    const LEVEL_WARN = "alert-warning";
    const LEVEL_ERROR = "alert-danger";

    public $notificationLevel;
    public $messageCode;
    public $messageArgs;
    public $titleCode;
    public $titleArgs;

    public function __construct($titleCode = "", $titleArgs = [], $messageCode = "", $messageArgs = [], $level = self::LEVEL_INFO) {
        $this->titleCode = $titleCode;
        $this->titleArgs = $titleArgs;
        $this->messageCode = $messageCode;
        $this->messageArgs = $messageArgs;
        $this->notificationLevel = $level;
    }

    public function render() {
        echo "<div class=\"alert " . $this->notificationLevel . " alert-dismissible\" role=\"alert\">";
        echo "<button type=\"button\" class=\"close\" "/*data-dismiss=\"alert\"*/ . " aria-label=\"Close\">";
        echo "<span aria-hidden=\"true\">&times;</span></button>";
        // Write Title only if filled
        if (!empty($this->titleCode)) {
            echo "<strong>";
            echo t($this->titleCode, $this->titleArgs);
            echo "</strong>";
        }

        if (!empty($this->titleCode) && !empty($this->messageCode)) {
            echo ":&nbsp;";
        }

        // Write Message only if filled
        if (!empty($this->messageCode)) {

            echo t($this->messageCode, $this->messageArgs);
        }
        echo "</div>";
    }

    public static function handleNotificationsAfterRender() {
        if (!@$_SESSION['preventNotificationClear']) {
            Session::clearAllNotifications();
        } else {
            self::preventNotificationClear(false);
        }
    }

    public static function preventNotificationClear($enabled = true) {
        if ($enabled) {
            $_SESSION['preventNotificationClear'] = 1;
        } else {
            unset($_SESSION['preventNotificationClear']);
        }
    }
}
