# jsonnet
The Google Jsonnet for PHP

### Google Jsonnet Tutorial
Jsonnet language, from its most basic features to its powerful object model, punctuated with examples drawn from the world of cocktails. These examples are meant to be fun, and although a little contrived, do not restrict our thinking to any one particular application of Jsonnet.

Caveat: Note that Jsonnet unparses JSON in a simple way. In particular, it alphabetically reorders object fields in its output. This is natural and compatible with JSON, since if order is meaningful, an array of pairs should be used instead of an object. Also, unparsing JSON using a canonical ordering of field names makes it possible to use diff to compare outputs. However, the example output on this page has been manually re-ordered in order to allow easier visual comparison to the given input. The whitespace of the output has also been tweaked to make it fit more neatly on the page. So, if you run these examples yourself, the output might be different (but equivalent).

The git of Google JsonNet:  https://github.com/google/jsonnet

### Install Jsonnet for PHP
```
The pecl package is :  http://pecl.php.net/package/jsonnet

    pecl install jsonnet

or


    wget -O JsonNet.Latest.tar.gz https://pecl.php.net/get/jsonnet
    mkdir JsonNet-PHP && tar -xzvf JsonNet.Latest.tar.gz -C ./JsonNet-PHP
    cd JsonNet-PHP/JsonNet-1.0.0

    phpize
    ./configure
    make && make install

```


### Simple Syntax Improvements

#### Input (Jsonnet)
```
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

```

#### Output (JSON)
````
{
    "cocktails": {

        "Tom Collins": {
            "ingredients": [
                { "kind": "Farmers Gin", "qty": 1.5 },
                { "kind": "Lemon", "qty": 1 },
                { "kind": "Simple Syrup", "qty": 0.5 },
                { "kind": "Soda", "qty": 2 },
                { "kind": "Angostura", "qty": "dash" }
            ],
            "garnish": "Maraschino Cherry",
            "served": "Tall"
        },
        "Manhattan": {
            "ingredients": [
                { "kind": "Rye", "qty": 2.5 },
                { "kind": "Sweet Red Vermouth", "qty": 1 },
                { "kind": "Angostura", "qty": "dash" }
            ],
            "garnish": "Maraschino Cherry",
            "served": "Straight Up"
        }
    }
}
````

### Demo of PHP
```php

    JsonNet::evaluateFile('bar_menu.1.jsonnet');

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

```