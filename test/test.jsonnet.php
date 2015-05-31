<?php
/**
 * @author ciogao@gmail.com
 * Date: 15-5-25 下午7:48
 */

try {
    var_dump(jsonnet_get_version());
    var_dump(jsonnet_get_author());


    var_dump(JsonNet::evaluateFile('bar_menu.1.jsonnet'));
    var_dump(JsonNet::evaluateFile('bar_menu.2.jsonnet'));
    var_dump(JsonNet::evaluateFile('bar_menu.3.jsonnet'));
    var_dump(JsonNet::evaluateFile('bar_menu.5.jsonnet'));
    var_dump(JsonNet::evaluateFile('bar_menu.6.jsonnet'));

    $Snippet = '
    {
        cocktails: {
            // Ingredient quantities are in fluid ounces.
            "Tom Collins": {
                ingredients: [
                    { kind: "Farmers Gin", qty: 1.5 },
                    { kind: "Lemon", qty: 1 },
                    { kind: "Simple Syrup", qty: 0.5 },
                    { kind: "Soda", qty: 2 },
                    { kind: "Angostura", qty: "dash" },
                ],
                garnish: "Maraschino Cherry",
                served: "Tall",
            },
            Manhattan: {
                ingredients: [
                    { kind: "Rye", qty: 2.5 },
                    { kind: "Sweet Red Vermouth", qty: 1 },
                    { kind: "Angostura", qty: "dash" },
                ],
                garnish: "Maraschino Cherry",
                served: "Straight Up",
            },
        }
    }
    ';

    var_dump(JsonNet::evaluateSnippet($Snippet));
} catch (Exception $e) {

    var_dump($e->getCode());
    var_dump($e->getMessage());
}

