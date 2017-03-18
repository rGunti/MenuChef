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
