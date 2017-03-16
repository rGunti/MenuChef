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
            if (PathUtils::currentPathMatches($path)) {
                self::$processedRequest = $request;
                $request->process($current_path, @$_GET, @$_POST);
                return;
            }
        }
        $pageNotFoundRequest = self::getPageNotFoundRequest();
        self::$processedRequest = $pageNotFoundRequest;
        $pageNotFoundRequest->process($current_path, @$_GET, @$_POST);
    }
}

abstract class BaseRequest {
    public function getPageTitle() { return "Unknown Page"; }

    public abstract function getFormPath();
    public abstract function process($path, $get = [], $post = []);
}
