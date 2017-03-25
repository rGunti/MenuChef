<?php
class RequestProcessor {
    const REQ_PROCESS_FILE = "/.cfg/pathconfig.inc";

    private static $processedRequest;
    /**
     * Gets processed request
     * @return BaseRequest Processed Request
     */
    public static function getProcessedRequest() { return self::$processedRequest; }

    /**
     * @return mixed
     */
    private static function getRequestProcessConfig() {
        return (require __DIR__ . '/../' . self::REQ_PROCESS_FILE);
    }

    /**
     * Returns new request which is used to process a 404 error
     * @return PageNotFoundRequest
     */
    private static function getPageNotFoundRequest() { return new PageNotFoundRequest(); }

    /** Processes the request for the current path */
    public static function processRequest() {
        $mapping = self::getRequestProcessConfig();
        $current_path = PathUtils::getCurrentPath();
        foreach ($mapping as $path => $request) {
            //echo "<pre>$path</pre>";
            if (PathUtils::currentPathMatches($path)) {
                self::$processedRequest = $request;
                $request->process($current_path, @$_GET, @$_POST);
                //echo "<pre>Path processed, ended</pre>";
                return;
            }
        }
        //echo "<pre>Path unknown, 404ing...</pre>";
        $pageNotFoundRequest = self::getPageNotFoundRequest();
        self::$processedRequest = $pageNotFoundRequest;
        $pageNotFoundRequest->process($current_path, @$_GET, @$_POST);
    }
}

abstract class BaseRequest {
    protected $storage_values = [];

    /**
     * Gets a value from the requests value storage
     * @param $key string
     * @return mixed
     */
    public function getStorageValue($key) { return $this->storage_values[$key]; }

    /**
     * Puts a value to the request value storage
     * @param $key string
     * @param $value mixed
     */
    public function setStorageValue($key, $value) { $this->storage_values[$key] = $value; }

    /**
     * Gets the page title
     * @return string
     */
    public function getPageTitle() { return "Unknown Page"; }

    /**
     * Gets the name of the Page Form file
     * @return string
     */
    public abstract function getFormPath();

    /**
     * Method called then request gets processed
     * @param string $path Current Navigation Path
     * @param array $get
     * @param array $post
     * @return mixed
     */
    public abstract function process($path, $get = [], $post = []);
}

abstract class BaseMultiRequest extends BaseRequest {
    public function process($path, $get = [], $post = []) {
        switch (RequestUtils::getRequestMethod()) {
            case RequestUtils::REQ_GET: $this->get($get); break;
            case RequestUtils::REQ_POST: $this->post($post); break;
            case RequestUtils::REQ_PUT:
                parse_str(file_get_contents('php://input'), $put_vars);
                $this->put($put_vars);
                break;
            case RequestUtils::REQ_DELETE: $this->delete($_GET); break;
        }
    }

    public function get($vars = []) {
        Logger::warn("Request Method GET has not been implemented by Request " . get_class($this));
    }
    public function post($vars = []) {
        Logger::warn("Request Method POST has not been implemented by Request " . get_class($this));
    }
    public function put($vars = []) {
        Logger::warn("Request Method PUT has not been implemented by Request " . get_class($this));
    }
    public function delete($vars = []) {
        Logger::warn("Request Method DELETE has not been implemented by Request " . get_class($this));
    }
}

abstract class BaseAjaxRequest extends BaseMultiRequest {
    // HTTP 100
    const HTTP_CODE_CONTINUE = 100;
    const HTTP_CODE_PROCESSING = 102;

    // HTTP 200
    const HTTP_CODE_OK = 200;
    const HTTP_CODE_CREATED = 201;
    const HTTP_CODE_ACCEPTED = 202;
    const HTTP_CODE_NON_AUTHORITATIVE_INFO = 203;
    const HTTP_CODE_NO_CONTENT = 204;
    const HTTP_CODE_RESET_CONTENT = 205;
    const HTTP_CODE_PARTIAL_CONTENT = 206;

    // HTTP 300
    const HTTP_CODE_MULTIPLE_CHOICES = 300;
    const HTTP_CODE_MOVED_PERM = 301;
    const HTTP_CODE_MOVED_TEMP = 302;
    const HTTP_CODE_SEE_OTHER = 303;
    const HTTP_CODE_NOT_MODIFIED = 304;
    const HTTP_CODE_REDIRECT_TEMP = 307;
    const HTTP_CODE_REDIRECT_PERM = 308;

    // HTTP 400
    const HTTP_CODE_BAD_REQUEST = 400;
    const HTTP_CODE_UNAUTHORIZED = 401;
    const HTTP_CODE_FORBIDDEN = 403;
    const HTTP_CODE_NOT_FOUND = 404;
    const HTTP_CODE_METHOD_NOT_ALLOWED = 405;
    const HTTP_CODE_NOT_ACCEPTABLE = 406;
    const HTTP_CODE_REQ_TIMEOUT = 408;
    const HTTP_CODE_GONE = 410;
    const HTTP_CODE_TEAPOT = 418;
    const HTTP_CODE_LOCKED = 423;
    const HTTP_CODE_TOO_MANY_REQUESTS = 429;
    const HTTP_CODE_UNAVAILABLE_LEGAL = 451;

    // HTTP 500
    const HTTP_CODE_INTERNAL_ERROR = 500;
    const HTTP_CODE_NOT_IMPLEMENTED = 501;
    const HTTP_CODE_SERVICE_UNAVAILABLE = 503;
    const HTTP_CODE_VER_NOT_SUPPORTED = 505;
    const HTTP_CODE_INSUFFICIENT_STORAGE = 507;
    const HTTP_CODE_LOOP_DETECTED = 508;
    const HTTP_CODE_NETWORK_AUTH_REQUIRED = 511;

    // Permission Level
    const PERM_LEVEL_NOT_LOGGED_IN = -1;
    const PERM_LEVEL_NONE = 0;
    const PERM_LEVEL_LOGGED_IN = 1;
    const PERM_LEVEL_ADMIN = 100;

    public function getFormPath() { return null; }
    public function getPageTitle() { return 'AJAX Request'; }

    /**
     * Parses the input (e.g. from $_GET) into a AjaxDataTableParameter object
     * @param array $vars
     * @return AjaxDataTableParameter
     */
    protected function prepareDataTableArguments($vars = []) {
        return new AjaxDataTableParameter(
            AppUtils::getKeyDefault($vars, 'start'),
            AppUtils::getKeyDefault($vars, 'length'),
            AppUtils::getKeyDefault($vars, 'search' , []),
            AppUtils::getKeyDefault($vars, 'columns', []),
            AppUtils::getKeyDefault($vars, 'order'  , [])
        );
    }

    /**
     * @param mixed $data Data to send with
     * @param int $errorCode Error Code (BaseAjaxRequest contains Constants for these)
     */
    protected function sendErrorResponse($data, $errorCode = self::HTTP_CODE_INTERNAL_ERROR) {
        AppUtils::clearRenderedContent(false);
        header('Content-Type: application/json');
        http_response_code($errorCode);
        die(json_encode([
            'HasError' => 1,
            'ErrorInfo' => $data
        ]));
    }

    /**
     * Gets the current Permission Level for AJAX requests
     * @return int
     */
    protected function getCurrentPermissionLevel() {
        if (Session::isLoggedIn()) {
            if (Session::isAdmin()) {
                return self::PERM_LEVEL_ADMIN;
            } else {
                return self::PERM_LEVEL_LOGGED_IN;
            }
        } else {
            return self::PERM_LEVEL_NONE;
        }
    }

    /**
     * Checks the current users permission level. If the required permission level
     * does not meet the permission level the user has, a response will be sent containing
     * error detail about the failed permission check and the request will be dropped.
     * @param int $neededPermission Permission Level (BaseAjaxRequest provides constants)
     */
    protected function checkPermissions($neededPermission = 0) {
        if ($neededPermission == self::PERM_LEVEL_NOT_LOGGED_IN) {
            if (Session::isLoggedIn()) {
                $this->sendErrorResponse(
                    new AjaxPermissionErrorObject(
                        self::PERM_LEVEL_NOT_LOGGED_IN,
                        self::PERM_LEVEL_LOGGED_IN,
                        'You have to be logged out in order to use this.'
                    )
                );
            }
        } else {
            $currentPermission = $this->getCurrentPermissionLevel();
            if ($currentPermission < $neededPermission) {
                $this->sendErrorResponse(
                    new AjaxPermissionErrorObject(
                        $neededPermission,
                        $currentPermission,
                        'Your permission level was too low to access this resource.'
                    ),
                    self::HTTP_CODE_FORBIDDEN
                );
            }
        }
    }

    /**
     * Converts the given Object to JSON and prints it.
     * All previous output will be removed from the Buffer.
     * Execution will then be terminated!
     * @param $data mixed Data to send
     * @param $httpCode int|null HTTP Response Code to use
     */
    protected function sendObjectResponse($data, $httpCode = null) {
        AppUtils::clearRenderedContent(false);
        header('Content-Type: application/json');
        if (!empty($httpCode)) { http_response_code($httpCode); }
        die(json_encode($data));
    }

    public function get($vars = []) {
        $this->sendErrorResponse('GET', self::HTTP_CODE_METHOD_NOT_ALLOWED);
    }

    public function post($vars = []) {
        $this->sendErrorResponse('POST', self::HTTP_CODE_METHOD_NOT_ALLOWED);
    }

    public function put($vars = []) {
        $this->sendErrorResponse('PUT', self::HTTP_CODE_METHOD_NOT_ALLOWED);
    }

    public function delete($vars = []) {
        $this->sendErrorResponse('DELETE', self::HTTP_CODE_METHOD_NOT_ALLOWED);
    }
}

class AjaxPermissionErrorObject {
    public function __construct($requiredPermission, $currentPermission, $message) {
        $this->requiredPermission = $requiredPermission;
        $this->currentPermission = $currentPermission;
        $this->message = $message;
    }

    public $requiredPermission;
    public $currentPermission;
    public $message;
}

class AjaxDataTableParameter {
    public function __construct($start, $length, $search, $cols, $order) {
        $this->start = $start;
        $this->length = $length;
        $this->search = $search;
        $this->cols = $cols;
        $this->order = $order;
    }

    /** @var int */
    public $start;
    /** @var int */
    public $length;
    /** @var array */
    public $search;
    /** @var array */
    public $cols;
    /** @var array */
    public $order;

    /** @return bool */
    public function hasOrderColumns() { return !empty($this->order); }
    /** @return bool */
    public function hasSearchTerm() { return !empty($this->search['value']); }

    /** @return string */
    public function getSearchTerm() { return $this->search['value']; }

    /** @return array */
    public function getSqlOrderColumns() {
        $order = [];
        if ($this->hasOrderColumns()) {
            foreach ($this->order as $param) {
                array_push($order, $this->cols[$param['column']]['data'] . ' ' . $param['dir']);
            }
        }
        return $order;
    }
}
