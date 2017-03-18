<?php
return [
    "/" => new HomeRequest(),
    "/Debug" => new DebugViewRequest(),
    "/Debug/PhpInfo" => new PhpInfoRequest(),

    "/Login" => new LoginRequest(),
];
