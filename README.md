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

### PHP Re Result
```
/usr/local/php/php-7.0.6-zts-debug/bin/php --re jsonnet

Extension [ <persistent> extension #40 JsonNet version v1.3.0 ] {

  - Constants [2] {
    Constant [ string JSONNET_PHP_VERSION ] { v1.3.0 }
    Constant [ string JSONNET_PHP_AUTHOR ] { Chitao.Gao  [ neeke@php.net ] }
  }

  - Functions {
    Function [ <internal:JsonNet> function jsonnet_get_version ] {
    }
    Function [ <internal:JsonNet> function jsonnet_get_author ] {
    }
  }

  - Classes [1] {
    Class [ <internal:JsonNet> class JsonNet ] {

      - Constants [0] {
      }

      - Static properties [0] {
      }

      - Static methods [4] {
        Method [ <internal:JsonNet> static public method evaluateFile ] {

          - Parameters [1] {
            Parameter #0 [ <required> $file_path ]
          }
        }

        Method [ <internal:JsonNet> static public method evaluateSnippet ] {

          - Parameters [1] {
            Parameter #0 [ <required> $snippet_string ]
          }
        }

        Method [ <internal:JsonNet> static public method fmtFile ] {

          - Parameters [1] {
            Parameter #0 [ <required> $file_path ]
          }
        }

        Method [ <internal:JsonNet> static public method fmtSnippet ] {

          - Parameters [1] {
            Parameter #0 [ <required> $snippet_string ]
          }
        }
      }

      - Properties [0] {
      }

      - Methods [2] {
        Method [ <internal:JsonNet, ctor> public method __construct ] {
        }

        Method [ <internal:JsonNet, dtor> public method __destruct ] {
        }
      }
    }
  }
}
```

###CodeTips
```
<?php
/**
 * @author neeke@php.net
 * Date: 18/3/29 下午7:51
 */

const JSONNET_PHP_VERSION = 'v1.3.0';
const JSONNET_PHP_AUTHOR  = 'neeke@php.net';

const CODE_SUCCESS = 1000;
const CODE_ERROR   = 900;

/**
 * @return string
 */
function jsonnet_get_version()
{
    return JSONNET_PHP_VERSION;
}

function jsonnet_get_author()
{
    return JSONNET_PHP_AUTHOR;
}

class JsonNet
{
    public function __construct()
    {
        #JsonNet init
    }

    public function __destruct()
    {
        #JsonNet destroy
    }

    /**
     * @param $file_path
     *
     * @return array
     * @throws Exception
     */
    static public function evaluateFile($file_path)
    {
        throw new Exception('JsonNet::evaluateFile #error', CODE_ERROR);

        return array();
    }

    /**
     * @param $snippet_string
     *
     * @return array
     * @throws Exception
     */
    static public function evaluateSnippet($snippet_string)
    {
        throw new Exception('JsonNet::evaluateSnippet #error', CODE_ERROR);

        return array();
    }

    /**
     * @param $file_path
     *
     * @return array
     * @throws Exception
     */
    static public function fmtFile($file_path)
    {
        throw new Exception('JsonNet::fmtFile #error', CODE_ERROR);

        return array();
    }

    /**
     * @param $snippet_string
     *
     * @return array
     * @throws Exception
     */
    static public function fmtSnippet($snippet_string)
    {
        throw new Exception('JsonNet::fmtSnippet #error', CODE_ERROR);

        return array();
    }

}
```