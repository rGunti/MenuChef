<?php
class NavigationBarManager {
    private static $nav_els;
    /** @return NavigationBarElementBase[] */
    public static function getNavEls() { return self::$nav_els; }
    /** @param $nav_els NavigationBarElementBase[] */
    public static function setNavEls($nav_els) { self::$nav_els = $nav_els; }

    public static function render() {
        foreach (self::getNavEls() as $nav) {
            $nav->render();
        }
    }
}

abstract class NavigationBarElementBase {
    protected $active;
    /** @return bool */
    public function getIsActive() { return $this->active; }
    /** @param $active bool */
    public function setIsActive($active) { $this->active = $active; }

    protected $disabled;
    /** @return bool */
    public function getIsDisabled() { return $this->disabled; }
    /** @param $disabled bool */
    public function setIsDisabled($disabled) { $this->disabled = $disabled; }

    protected $link;
    /** @return string */
    public function getLink() { return $this->link; }
    /** @param $link string */
    public function setLink($link) { $this->link = $link; }

    protected $title;
    /** @return string */
    public function getTitle() { return $this->title; }
    /** @param $title string */
    public function setTitle($title) { $this->title = $title; }

    protected $activeOnPath;
    /** @return string */
    public function getActiveOnPath() { return $this->activeOnPath; }
    /** @param $activeOnPath string */
    public function setActiveOnPath($activeOnPath) { $this->activeOnPath = $activeOnPath; }

    /** @return bool */
    public function getIsActiveOnPath() {
        if (empty($this->getActiveOnPath())) {
            return false;
        } else {
            $path = ($this->getActiveOnPath() == "*") ? $this->getLink() : $this->getActiveOnPath();
            return PathUtils::pathMatches(PathUtils::getCurrentPath(), $path);
        }
    }

    public abstract function render();
}

abstract class NavigationBarCollectionElementBase extends NavigationBarElementBase {
    public function __construct() {
        $this->item_collection = [];
        $this->setLink('#');
    }

    /** @var NavigationBarElementBase[] */
    protected $item_collection;
    /** @return \NavigationBarElementBase[] */
    public function getItemCollection() { return $this->item_collection; }
    /** @param $item_collection array */
    public function setItemCollection($item_collection) { $this->item_collection = $item_collection; }

    /** @param $item NavigationBarElementBase */
    public function addItem($item) { array_push($this->item_collection, $item); }

    /** @return bool */
    public function hasEnabledItems() {
        foreach ($this->item_collection as $item) {
            if ($item->getIsActiveOnPath()) { return true; }
        }
        return false;
    }
}

class TopNavigationBarCollection extends NavigationBarCollectionElementBase {
    const SIDE_LEFT = "navbar-nav";
    const SIDE_RIGHT = "navbar-nav navbar-right";

    protected $side;
    /** @return string */
    public function getSide() { return $this->side; }
    /** @param $side string */
    public function setSide($side) { $this->side = $side; }

    public function render() {
        echo "<ul class=\"nav " . $this->getSide() . "\">";
        foreach ($this->getItemCollection() as $item) {
            $item->render();
        }
        echo "</ul>";
    }
}

class TopNavigationBarMenu extends NavigationBarCollectionElementBase {
    public function render() {
        echo "<li class=\"dropdown " . ($this->getIsActive() || $this->hasEnabledItems() ? "active" : "") . "\">";
        echo "<a href=\"" . PathUtils::getLink($this->getLink()) .
            "\" class=\"dropdown-toggle " . ($this->getIsDisabled() ? 'disabled' : '') .
            "\" data-toggle=\"dropdown\" role=\"button\" aria-haspopup=\"true\" aria-expanded=\"false\">" .
            $this->getTitle() . " <span class=\"caret\"></span></a>";
        echo "<ul class=\"dropdown-menu\">";
        foreach ($this->getItemCollection() as $item) {
            $item->render();
        }
        echo "</ul></li>";
    }
}

class NavigationBarElement extends NavigationBarElementBase {
    public function __construct($link = "#", $title = "_", $active = false, $disabled = false, $activeOnPath = "*") {
        $this->setLink($link);
        $this->setTitle($title);
        $this->setIsActive($active);
        $this->setIsDisabled($disabled);
        $this->setActiveOnPath($activeOnPath);
    }

    public function render() {
        echo "<li class=\"" .
            ($this->getIsActive() || (!$this->getIsDisabled() && $this->getIsActiveOnPath()) ? "active " : "") .
            ($this->getIsDisabled() ? "disabled " : "") .
            "\"><a href=\"" . PathUtils::getLink($this->getLink()) . "\">" . $this->getTitle() . "</a></li>";
    }
}

class NavigationBarSeparatorElement extends NavigationBarElementBase {
    public function render() {
        echo "<li role=\"separator\" class=\"divider\" " . ($this->getIsActive() ? "class=\"active\"" : "") . "></li>";
    }
}
