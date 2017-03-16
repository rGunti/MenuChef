<?php
//$nav_left = new TopNavigationBarCollection();
//$nav_left->setSide(TopNavigationBarCollection::SIDE_LEFT);

$nav_right = new TopNavigationBarCollection();
$nav_right->setSide(TopNavigationBarCollection::SIDE_RIGHT);

$nav_right->addItem(new NavigationBarElement("/Debug", "Debug"));
$nav_right->addItem(new NavigationBarElement("/Login", "Login"));

$nav_els = [
//    $nav_left,
    $nav_right
];
NavigationBarManager::setNavEls($nav_els);
