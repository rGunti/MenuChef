<?php
require_once '.src/.requireAll.inc';
require_once '.req/.requireAll.inc';

RequestProcessor::processRequest();
$request = RequestProcessor::getProcessedRequest();
?>
<html>
    <head>
        <title><?= $request->getPageTitle() ?></title>
        <meta charset="UTF-8">

        <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no" />
        <meta name="HandheldFriendly" content="true" />

        <link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Open+Sans:300,300i,400,400i,600,600i,700,700i,800,800i">
        <link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Open+Sans+Condensed:300,700">
        <link rel="stylesheet" href="css/bootstrap.min.css" />
        <link rel="stylesheet" href="https://cdn.datatables.net/1.10.13/css/dataTables.bootstrap.min.css" />
        <link rel="stylesheet" href="https://cdn.datatables.net/responsive/2.1.1/css/responsive.dataTables.min.css" />
        <link rel="stylesheet" href="css/rgunti.css" />

        <link rel="stylesheet" href="css/bootstrap-checkbox/awesome-bootstrap-checkbox.css" />

        <script src="js/jquery.min.js"></script>
        <script src="js/tether.min.js"></script>
        <script src="js/bootstrap.min.js"></script>
        <script src="js/parallax.min.js"></script>

        <script src="https://cdn.datatables.net/1.10.13/js/jquery.dataTables.min.js"></script>
        <script src="https://cdn.datatables.net/1.10.13/js/dataTables.bootstrap.min.js"></script>
        <script src="https://cdn.datatables.net/fixedcolumns/3.2.2/js/dataTables.fixedColumns.min.js"></script>
        <script src="https://cdn.datatables.net/responsive/2.1.1/js/dataTables.responsive.min.js"></script>

        <script src="js/rgunti.js"></script>
    </head>
    <body>
        <?php require_once '.frm/' . $request->getFormPath(); ?>
    </body>
</html>
