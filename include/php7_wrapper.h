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

#if PHP_VERSION_ID >= 70000

# define JSONNET_MAKE_ZVAL(z) zval _stack_zval_##z; z = &(_stack_zval_##z)

# define JSONNET_ZEND_REGISTER_CLASS(z) zend_register_internal_class_ex(z, NULL);
# define JSONNET_ZVAL_STRING(z, s) ZVAL_STRING(z, s)
# define JSONNET_ZVAL_STRINGL(z, s, l) ZVAL_STRINGL(z, s, l)
# define JSONNET_RETURN_STRINGL(k, l) RETURN_STRINGL(k, l)
# define JSONNET_ZVAL_PTR_DTOR(z) zval_ptr_dtor(z)

#else

# define JSONNET_MAKE_ZVAL(z) MAKE_STD_ZVAL(z)
# define JSONNET_ZEND_REGISTER_CLASS(z) zend_register_internal_class_ex(z, NULL, NULL TSRMLS_CC);
# define JSONNET_ZVAL_STRING(z, s) ZVAL_STRING(z, s, 1)
# define JSONNET_ZVAL_STRINGL(z, s, l) ZVAL_STRINGL(z, s, l, 1)
# define JSONNET_RETURN_STRINGL(k, l) RETURN_STRINGL(k, l, 1)
# define JSONNET_ZVAL_PTR_DTOR(z) zval_ptr_dtor(&z)

#endif