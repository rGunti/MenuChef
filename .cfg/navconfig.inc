<?php
//$nav_left = new TopNavigationBarCollection();
//$nav_left->setSide(TopNavigationBarCollection::SIDE_LEFT);

$nav_right = new TopNavigationBarCollection();
$nav_right->setSide(TopNavigationBarCollection::SIDE_RIGHT);

$nav_el_debug = new NavigationBarElement();
$nav_el_debug->setTitle("Debug");
$nav_el_debug->setLink("/Debug");
$nav_right->addItem($nav_el_debug);

$nav_el_login = new NavigationBarElement();
$nav_el_login->setTitle("Login");
$nav_el_login->setLink("/Login");
$nav_right->addItem($nav_el_login);

$nav_els = [
//    $nav_left,
    $nav_right
];
NavigationBarManager::setNavEls($nav_els);
