<?php
require_once '.src/.requireAll.inc';
L10N::initL10N();
require_once '.req/.requireAll.inc';
RequestProcessor::processRequest();
$request = RequestProcessor::getProcessedRequest();

$themes = [
    'default' => '/css/bootstrap.min.css',
    'defaulttheme' => '/css/bootstrap-theme.min.css',
    'darkmode' => '/css/bootswatch.min.css',
    'darkadmin' => '/css/darkadmin.min.css',
    'superhero' => '/css/superhero.min.css',
];
$usedTheme = $themes[AppUtils::getDefaultValue(@$_COOKIE['UsedTheme'], 'darkmode')];
?>
<!DOCTYPE html>
<html>
    <head>
        <title>
            <?= $request->getPageTitle() ?> &ndash;
            [ <?= (AppConfig::SHOW_INSTANCE_NAME ? ("(" . AppConfig::INSTANCE_NAME . ") ") : "") . AppConfig::APP_NAME ?> ]
        </title>
        <meta charset="UTF-8">

        <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no" />
        <meta name="HandheldFriendly" content="true" />

        <!-- STYLESHEETS -->
        <!-- Fonts -->
        <link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Open+Sans:300,300i,400,400i,600,600i,700,700i,800,800i">
        <link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Open+Sans+Condensed:300,700">

        <!-- Bootstrap -->
        <link rel="stylesheet" href="<?= PathUtils::getLink('/css/bootstrap.min.css') ?>" />

        <?php if ($usedTheme != $themes['default']) { ?>
        <!-- Bootstrap Theme -->
        <link rel="stylesheet" href="<?= PathUtils::getLink($usedTheme) ?>" />
        <?php } ?>

        <!-- jQuery UI -->
        <link rel="stylesheet" href="<?= PathUtils::getLink('/css/jquery-ui/jquery-ui.min.css') ?>" />
        <link rel="stylesheet" href="<?= PathUtils::getLink('/css/jquery-ui/jquery-ui.min.css') ?>" />
        <link rel="stylesheet" href="<?= PathUtils::getLink('/css/jquery-ui/jquery-ui.min.css') ?>" />

        <!-- jQuery DataTables -->
        <link rel="stylesheet" href="<?= PathUtils::getLink('/css/dataTables.bootstrap.min.css') ?>" />
        <?php /*
        <link rel="stylesheet" href="<?= PathUtils::getLink('/css/responsive.dataTables.min.css') ?>" />
        <link rel="stylesheet" href="<?= PathUtils::getLink('/css/bootstrap-checkbox/awesome-bootstrap-checkbox.css') ?>" />
        */?>
        <link rel="stylesheet" href="<?= PathUtils::getLink('/css/rgunti.css') ?>" />

        <!-- JAVASCRIPT -->
        <script src="<?= PathUtils::getLink('/js/jquery.min.js') ?>"></script>
        <script src="<?= PathUtils::getLink('/js/tether.min.js') ?>"></script>
        <script src="<?= PathUtils::getLink('/js/bootstrap.min.js') ?>"></script>
        <script src="<?= PathUtils::getLink('/js/parallax.min.js') ?>"></script>
        <script src="<?= PathUtils::getLink('/js/jquery-ui/jquery-ui.min.js') ?>"></script>

        <!-- jQuery DataTables (+ Addons) -->
        <script src="<?= PathUtils::getLink('/js/jquery.dataTables.min.js') ?>"></script>
        <script src="<?= PathUtils::getLink('/js/dataTables.bootstrap.min.js') ?>"></script>
        <script src="<?= PathUtils::getLink('/js/dataTables.fixedColumns.min.js') ?>"></script>
        <?php /*
        <script src="<?= PathUtils::getLink('/js/dataTables.responsive.min.js') ?>"></script>
        */?>

        <!-- Other Libraries -->
        <script src="<?= PathUtils::getLink('/js/js.cookie.js') ?>"></script>

        <!-- Custom Scripts -->
        <script src="<?= PathUtils::getLink('/js/rgunti.js') ?>"></script>
    </head>
    <body>
        <nav class="navbar navbar-default navbar-fixed-top">
            <div class="container-fluid">
                <!-- Brand and toggle get grouped for better mobile display -->
                <div class="navbar-header">
                    <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#rgunti-nav-bar" aria-expanded="false">
                        <span class="sr-only"><?= t('toggle_nav') ?></span>
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
        <?php require_once '.frm/general/notifications.inc'; ?>
        <div class="container">
            <div class="page-header">
                <h1><?= $request->getPageTitle() ?></h1>
            </div>
            <?php require_once '.frm/' . $request->getFormPath(); ?>
        </div>
        <hr>
        <footer>
            <div class="container"><?php require_once '.frm/general/footer.inc' ?></div>
        </footer>
    </body>
</html>
