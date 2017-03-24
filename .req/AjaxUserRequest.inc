<?php
class AjaxUserRequest extends BaseAjaxRequest {
    public function get($vars = []) {
        // Check Permission
        $this->checkPermissions(self::PERM_LEVEL_ADMIN);

        // Get Parameters
        $params = $this->prepareDataTableArguments($vars);
        $order = $params->getSqlOrderColumns();

        // Get Conditions
        $conditions = [];
        if ($params->hasSearchTerm()) {
            $searchText = $params->getSearchTerm();
            $conditions = [
                TableWhereObject::getLike('USERNAME', $searchText),
                TableWhereObject::getLike('MAIL', $searchText, TableWhereObject::PREFIX_OR)
            ];
        }

        // Get Data
        $users = DatabaseTools::getWhereAdv(
            MUser::VIEW_NAME,
            new MUser(),
            $conditions,
            $order,
            $params->start,
            $params->length
        );

        // Send Data
        $this->sendObjectResponse($users);
    }
}
