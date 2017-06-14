<?php
$nav_left = new TopNavigationBarCollection();
$nav_left->setSide(TopNavigationBarCollection::SIDE_LEFT);

if (Session::isLoggedIn()) {
    $nav_left->addItem(new NavigationBarElement("/Meal", t('meal_pl')));
    $nav_left->addItem(new NavigationBarElement(
        "/PlanCreator",
        t('plan_creator'),
        false,
        false,
        '/PlanCreator/Step/*'
    ));
}

$nav_right = new TopNavigationBarCollection();
$nav_right->setSide(TopNavigationBarCollection::SIDE_RIGHT);

$nav_right->addItem(new NavigationBarElement("/Debug", t('debug_title')));
if (Session::isLoggedIn()) {
    if (Session::isAdmin()) {
        $nav_admin = new TopNavigationBarMenu();
        $nav_admin->setTitle(t('admin_tools'));
        $nav_admin->setLink('/AdminTools');
        $nav_admin->addItem(new NavigationBarElement("/AdminTools/Users", "<span class='glyphicon glyphicon-briefcase'></span> " . t('admin_tools_users')));
        $nav_admin->addItem(new NavigationBarSeparatorElement());
        $nav_admin->addItem(new NavigationBarElement("/AdminTools/Ingredient", "<span class='glyphicon glyphicon-list'></span> " . t('ingredient_pl')));
        $nav_admin->addItem(new NavigationBarElement("/AdminTools/Units", "<span class='glyphicon glyphicon-wrench'></span> " . t('measuring_unit_pl')));

        $nav_right->addItem($nav_admin);
    }

    $nav_user = new TopNavigationBarMenu();
    $nav_user->setTitle(Session::getUserInfo()->username);
    $nav_user->addItem(new NavigationBarElement("/MySettings", "<span class='glyphicon glyphicon-user'></span> " . t('user_settings_title')));
    $nav_user->addItem(new NavigationBarSeparatorElement());
    $nav_user->addItem(new NavigationBarElement("/Logout", "<span class='glyphicon glyphicon-log-out'></span> " . t('logout')));

    $nav_right->addItem($nav_user);
} else {
    $nav_right->addItem(new NavigationBarElement("/Login", "<span class='glyphicon glyphicon-log-in'></span> " . t('login')));
}

// Build Language Menu
$nav_lang = new TopNavigationBarCollection();
$nav_lang->setSide(TopNavigationBarCollection::SIDE_RIGHT);
$nav_lang_dropdown = new TopNavigationBarMenu();
$nav_lang_dropdown->setTitle('<img src="' . PathUtils::getLink(t(L10N::L10N_LANG_INFO_FLAG)) . '">');
$nav_lang_dropdown->addItem(new NavigationBarElement('#', t('languages'), false, true));
foreach (L10N::getLanguageList() as $lang_code => $lang_info) {
    $title = "<img src=\"" . PathUtils::getLink($lang_info['flag']) . "\"> $lang_info[name]";
    $i = new NavigationBarElement(PathUtils::getCurrentPath() . "?lang=$lang_code", $title);
    if (L10N::getLanguageCookie() == $lang_code) {
        //$i->setTitle("<b>$title</b>");
        $i->setIsActive(true);
    }
    $nav_lang_dropdown->addItem($i);
}
$nav_lang->addItem($nav_lang_dropdown);

$nav_els = [
    $nav_left,
    $nav_lang,
    $nav_right,
];
NavigationBarManager::setNavEls($nav_els);
