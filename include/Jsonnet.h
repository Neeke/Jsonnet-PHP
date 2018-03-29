/*
  +----------------------------------------------------------------------+
  | JsonNet                                                              |
  +----------------------------------------------------------------------+
  | This source file is subject to version 2.0 of the Apache license,    |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.apache.org/licenses/LICENSE-2.0.html                      |
  | If you did not receive a copy of the Apache2.0 license and are unable|
  | to obtain it through the world-wide-web, please send a note to       |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Neeke.Gao  <neeke@php.net>                                   |
  +----------------------------------------------------------------------+
*/

#ifndef _JSONNET_H_
#define _JSONNET_H_

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "ext/standard/file.h"
#include "ext/standard/url.h"
#include "ext/standard/php_string.h"
#include "ext/json/php_json.h"
#include "Zend/zend_exceptions.h"
#include "php7_wrapper.h"

#define JSONNET_RES_NAME        "JsonNet"
#define JSONNET_PHP_VERSION     "v1.3.0"
#define JSONNET_PHP_AUTHOR      "Chitao.Gao  [ neeke@php.net ]"

#define SL_S(s)                 s, sizeof(s) - 1

#define CODE_SUCCESS            1000
#define CODE_ERROR              900

#endif /* _JSONNET_H_ */