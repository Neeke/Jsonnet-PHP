
#ifndef PHP_JSONNET_H
#define PHP_JSONNET_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "include/Jsonnet.h"

extern zend_module_entry jsonnet_module_entry;
#define phpext_jsonnet_ptr &jsonnet_module_entry

#ifdef PHP_WIN32
# define PHP_JSONNET_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
# define PHP_JSONNET_API __attribute__ ((visibility("default")))
#else
# define PHP_JSONNET_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(jsonnet);
PHP_MSHUTDOWN_FUNCTION(jsonnet);
PHP_RINIT_FUNCTION(jsonnet);
PHP_RSHUTDOWN_FUNCTION(jsonnet);
PHP_MINFO_FUNCTION(jsonnet);

PHP_FUNCTION(jsonnet_get_version);
PHP_FUNCTION(jsonnet_get_author);

zend_class_entry *jsonnet_ce,*php_com_exception_class_entry;

PHP_METHOD(JSONNET_RES_NAME, __construct);
PHP_METHOD(JSONNET_RES_NAME, __destruct);
PHP_METHOD(JSONNET_RES_NAME, evaluateFile);
PHP_METHOD(JSONNET_RES_NAME, evaluateSnippet);
PHP_METHOD(JSONNET_RES_NAME, fmtFile);
PHP_METHOD(JSONNET_RES_NAME, fmtSnippet);

ZEND_BEGIN_MODULE_GLOBALS(jsonnet)

ZEND_END_MODULE_GLOBALS(jsonnet)

extern ZEND_DECLARE_MODULE_GLOBALS(jsonnet);

#ifdef ZTS
#define JSONNET_G(v) TSRMG(jsonnet_globals_id, zend_jsonnet_globals *, v)
#else
#define JSONNET_G(v) (jsonnet_globals.v)
#endif

#endif /* PHP_JSONNET_H */

