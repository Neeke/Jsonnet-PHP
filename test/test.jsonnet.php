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
    var_dump(JsonNet::evaluateFile('utf8.jsonnet'));

    $Snippet = '
{
    cocktails: {
        "Bee\'s Knees": {
            // Construct the ingredients by using 4/3 oz
            // of each element in the given list.
            ingredients: [  // Array comprehension.
                { kind: i, qty: 4/3 }
                for i in ["Honey Syrup", "Lemon Juice", "Farmers Gin"]
            ],
            garnish: "Lemon Twist",
            served: "Straight Up",
        },
    } + {  // Object comprehension.
        [sd.name + "Screwdriver"]: {
            ingredients: [
                { kind: "Vodka", qty: 1.5, aa:sd.name },
                { kind: sd.fruit, qty: 3 },
            ],
            garnish: null,
            served: "On The Rocks"
        } for sd in [
            {name: "Yellow ", fruit: "Lemonade"},
            {name: "汉字", fruit: "Orange Juice"},
        ]
    }
}

    ';

    var_dump(JsonNet::evaluateSnippet($Snippet));
} catch (Exception $e) {

    var_dump($e->getCode());
    var_dump($e->getMessage());
}

