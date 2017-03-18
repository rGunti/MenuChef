<?php
require_once '.src/.requireAll.inc';
require_once '.req/.requireAll.inc';

RequestProcessor::processRequest();
$request = RequestProcessor::getProcessedRequest();
?>
<html>
    <head>
        <title>
            <?= $request->getPageTitle() ?> &ndash;
            [ <?= (AppConfig::SHOW_INSTANCE_NAME ? ("(" . AppConfig::INSTANCE_NAME . ") ") : "") . AppConfig::APP_NAME ?> ]
        </title>
        <meta charset="UTF-8">

        <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no" />
        <meta name="HandheldFriendly" content="true" />

        <link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Open+Sans:300,300i,400,400i,600,600i,700,700i,800,800i">
        <link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Open+Sans+Condensed:300,700">
        <link rel="stylesheet" href="css/bootstrap.min.css" />
        <!--
        <link rel="stylesheet" href="https://cdn.datatables.net/1.10.13/css/dataTables.bootstrap.min.css" />
        <link rel="stylesheet" href="https://cdn.datatables.net/responsive/2.1.1/css/responsive.dataTables.min.css" />
        -->
        <link rel="stylesheet" href="css/bootstrap-checkbox/awesome-bootstrap-checkbox.css" />
        <link rel="stylesheet" href="css/superhero.min.css" />
        <link rel="stylesheet" href="css/rgunti.css" />

        <script src="js/jquery.min.js"></script>
        <script src="js/tether.min.js"></script>
        <script src="js/bootstrap.min.js"></script>
        <!--
        <script src="js/parallax.min.js"></script>
        -->

        <!--
        <script src="https://cdn.datatables.net/1.10.13/js/jquery.dataTables.min.js"></script>
        <script src="https://cdn.datatables.net/1.10.13/js/dataTables.bootstrap.min.js"></script>
        <script src="https://cdn.datatables.net/fixedcolumns/3.2.2/js/dataTables.fixedColumns.min.js"></script>
        <script src="https://cdn.datatables.net/responsive/2.1.1/js/dataTables.responsive.min.js"></script>
        -->

        <script src="js/rgunti.js"></script>
    </head>
    <body>
        <nav class="navbar navbar-default navbar-fixed-top">
            <div class="container-fluid">
                <!-- Brand and toggle get grouped for better mobile display -->
                <div class="navbar-header">
                    <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#rgunti-nav-bar" aria-expanded="false">
                        <span class="sr-only">Toggle navigation</span>
                        <span class="icon-bar"></span>
                        <span class="icon-bar"></span>
                        <span class="icon-bar"></span>
                    </button>
                    <a class="navbar-brand" href="<?= PathUtils::getLink("/") ?>">
                        <?= AppConfig::APP_NAME ?>
                        <?php if (AppConfig::SHOW_INSTANCE_NAME) { ?>
                            <span class="label label-default"><?= AppConfig::INSTANCE_NAME ?></span>
                        <?php } ?>
                    </a>
                </div>

                <!-- Collect the nav links, forms, and other content for toggling -->
                <div class="collapse navbar-collapse" id="rgunti-nav-bar">
                    <?php NavigationBarManager::render() ?>
                </div>
            </div>
        </nav>
        <div class="container-spacer"></div>
        <div class="container">
            <div class="page-header">
                <h1><?= $request->getPageTitle() ?></h1>
            </div>
            <?php require_once '.frm/' . $request->getFormPath(); ?>
        </div>
    </body>
</html>
