<?php
class UnitsRequest extends BaseMultiRequest {
    /**
     * Gets the name of the Page Form file
     * @return string
     */
    public function getFormPath() { return "units.inc"; }
    public function getPageTitle() { return t('measuring_unit_pl'); }

    public function get($vars = []) {
        // Check Permission
        Session::enforceAdmin();
    }
}
