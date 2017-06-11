<?php
return [
    "/" => new HomeRequest(),
    "/Debug" => new DebugViewRequest(),
    "/Debug/PhpInfo" => new PhpInfoRequest(),

    "/Login" => new LoginRequest(),
    "/Logout" => new LoginRequest(),

    "/_Docs" => new AppDocumentRequest(),
    "/_Docs/ToS" => new AppDocumentRequest(),
    "/_Docs/Imprint" => new AppDocumentRequest(),
    "/_Docs/Copyright" => new AppDocumentRequest(),

    "/MySettings" => new UserSettingsRequest(),

    "/AdminTools" => new PageNotFoundRequest(),
    "/AdminTools/Users" => new UserManagerRequest(),
    "/AdminTools/Ingredient" => new IngredientRequest(),
    "/AdminTools/Units" => new UnitsRequest(),

    "/Meal" => new MealRequest(),
    "/Meal/*/Editor" => new MealEditorRequest(),

    // AJAX Requests
    "/AJAX/Users" => new AjaxUserRequest(),
    "/AJAX/Meal" => new AjaxMealRequest(),
    "/AJAX/Meal/*" => new AjaxMealRequest(),
    "/AJAX/Meal/*/LinkedMeals" => new AjaxLinkedMealRequest(),
    "/AJAX/Meal/*/ConnectedMeals" => new AjaxLinkedMealRequest(),
    "/AJAX/MealIngredients/*" => new AjaxMealIngredientRequest(),
    "/AJAX/Ingredients" => new AjaxIngredientRequest(),
    "/AJAX/Ingredients/*" => new AjaxIngredientRequest(),
    "/AJAX/LinkedMeal" => new AjaxLinkedMealRequest(),
    "/AJAX/Units" => new AjaxUnitsRequest(),
];
