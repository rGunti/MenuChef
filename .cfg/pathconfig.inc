<?php
return [
    "/" => new HomeRequest(),
    "/Debug" => new DebugViewRequest(),
    "/Debug/PhpInfo" => new PhpInfoRequest(),

    "/Login" => new LoginRequest(),
    "/Logout" => new LoginRequest(),

    "/MySettings" => new UserSettingsRequest(),

    "/AdminTools" => new PageNotFoundRequest(),
    "/AdminTools/Users" => new UserManagerRequest(),

    // AJAX Requests
    "/AJAX/Users" => new AjaxUserRequest(),
];
