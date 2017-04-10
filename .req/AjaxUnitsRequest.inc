<?php
class AjaxUnitsRequest extends BaseAjaxRequest {
    public function get($vars = []) {
        // Check Permission
        $this->checkPermissions(self::PERM_LEVEL_LOGGED_IN);

        // Get Parameters
        $params = $this->prepareDataTableArguments($vars);
        $order = $params->getSqlOrderColumns();

        // Get Conditions
        $conditions = [];
        /*
        if ($params->hasSearchTerm()) {
            $searchText = $params->getSearchTerm();
            $conditions = [
                TableWhereObject::getLike('NAME', $searchText)
            ];
        }
        */

        // Get Data
        $units = DatabaseTools::getWhereAdv(
            MMeasuringUnit::TABLE_NAME,
            new MMeasuringUnit(),
            $conditions,
            $order,
            $params->start,
            $params->length
        );

        for ($i = 0; $i < $units->recordsTotal; $i++) {
            /** @var MMeasuringUnit $unit */
            $unit = $units->data[$i];
            $unit->t_name = t($unit->name);
            $unit->t_unit_group = t($unit->unit_group);
            $unit->t_super_unit = (empty($unit->super_unit) ? null : t($unit->super_unit));
        }

        // Send Data
        $this->sendObjectResponse($units);
    }
}
