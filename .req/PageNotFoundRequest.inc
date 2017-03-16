<?php

class PageNotFoundRequest extends BaseRequest {
    public function getFormPath() { return "404.inc"; }

    public function process($path, $get = [], $post = []) {
        // TODO: Implement process() method.
    }
}
