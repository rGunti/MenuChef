<?php
//$nav_left = new TopNavigationBarCollection();
//$nav_left->setSide(TopNavigationBarCollection::SIDE_LEFT);

$nav_right = new TopNavigationBarCollection();
$nav_right->setSide(TopNavigationBarCollection::SIDE_RIGHT);

$nav_right->addItem(new NavigationBarElement("/Debug", t('debug_title')));
if (Session::isLoggedIn()) {
    $nav_user = new TopNavigationBarMenu();
    $nav_user->setTitle(Session::getUserInfo()->username);
    $nav_user->addItem(new NavigationBarElement("/MySettings", "<span class='glyphicon glyphicon-user'></span> " . t('user_settings_title')));
    $nav_user->addItem(new NavigationBarSeparatorElement());
    $nav_user->addItem(new NavigationBarElement("/Logout", "<span class='glyphicon glyphicon-log-out'></span> " . t('logout')));

    $nav_right->addItem($nav_user);
} else {
    $nav_right->addItem(new NavigationBarElement("/Login", "<span class='glyphicon glyphicon-log-in'></span> " . t('login')));
}

$nav_els = [
//    $nav_left,
    $nav_right
];
NavigationBarManager::setNavEls($nav_els);
