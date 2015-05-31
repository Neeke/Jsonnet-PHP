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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "ext/standard/file.h"
#include "php_jsonnet.h"
#include "zend_extensions.h"
#include <sys/resource.h>
#include <stdlib.h>

#ifdef PHP_WIN32
#include "win32/time.h"
#elif defined(NETWARE)
#include <sys/timeval.h>
#include <sys/time.h>
#else
#include <sys/time.h>
#endif

#include "libjsonnet.h"


ZEND_DECLARE_MODULE_GLOBALS(jsonnet)

static int le_jsonnet;

const zend_function_entry jsonnet_functions[] = {
    PHP_FE(jsonnet_get_version, NULL)
    PHP_FE(jsonnet_get_author,  NULL)
    {NULL, NULL, NULL}
};

const zend_function_entry jsonnet_methods[] = {
        PHP_ME(JSONNET_RES_NAME, __construct,   NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
        PHP_ME(JSONNET_RES_NAME, __destruct,    NULL, ZEND_ACC_PUBLIC | ZEND_ACC_DTOR)

        PHP_ME(JSONNET_RES_NAME, evaluateFile,   NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)

        {NULL, NULL, NULL}
};

zend_module_entry jsonnet_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    JSONNET_RES_NAME,
    jsonnet_functions,
    PHP_MINIT(jsonnet),
    PHP_MSHUTDOWN(jsonnet),
    PHP_RINIT(jsonnet),
    PHP_RSHUTDOWN(jsonnet),
    PHP_MINFO(jsonnet),
#if ZEND_MODULE_API_NO >= 20010901
    JSONNET_PHP_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_JSONNET
ZEND_GET_MODULE(jsonnet)
#endif

PHP_INI_BEGIN()

PHP_INI_END()


static void php_jsonnet_init_globals(zend_jsonnet_globals *jsonnet_globals)
{

}


PHP_MINIT_FUNCTION(jsonnet)
{
    ZEND_INIT_MODULE_GLOBALS(jsonnet, php_jsonnet_init_globals, NULL);

    REGISTER_INI_ENTRIES();

    REGISTER_STRINGL_CONSTANT("JSONNET_PHP_VERSION",   JSONNET_PHP_VERSION,   sizeof(JSONNET_PHP_VERSION) - 1,  CONST_PERSISTENT | CONST_CS);
    REGISTER_STRINGL_CONSTANT("JSONNET_PHP_AUTHOR",    JSONNET_PHP_AUTHOR,    sizeof(JSONNET_PHP_AUTHOR) - 1,   CONST_PERSISTENT | CONST_CS);

    zend_class_entry jsonnet;
    INIT_CLASS_ENTRY(jsonnet, JSONNET_RES_NAME, jsonnet_methods);
    jsonnet_ce = zend_register_internal_class_ex(&jsonnet, NULL, NULL TSRMLS_CC);
    jsonnet_ce->ce_flags = ZEND_ACC_IMPLICIT_PUBLIC;

//    zend_declare_property_null(jsonnet_ce, ZEND_STRL(JSONNET_BUFFER_NAME), ZEND_ACC_STATIC TSRMLS_CC);
//    zend_declare_property_null(jsonnet_ce, ZEND_STRL(JSONNET_BUFFER_SIZE_NAME), ZEND_ACC_STATIC TSRMLS_CC);

    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(jsonnet)
{
    UNREGISTER_INI_ENTRIES();

    return SUCCESS;
}

PHP_RINIT_FUNCTION(jsonnet)
{
//    jsonnet_init_logger(TSRMLS_C);
//    jsonnet_init_buffer(TSRMLS_C);

    return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(jsonnet)
{
//    jsonnet_shutdown_buffer(TSRMLS_C);

    return SUCCESS;
}

PHP_MINFO_FUNCTION(jsonnet)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "JsonNet support", "Enabled");
    php_info_print_table_row(2, "jsonnet Information", JSONNET_VERSION);
    php_info_print_table_row(2, "Version", JSONNET_PHP_VERSION);
    php_info_print_table_row(2, "Author", JSONNET_PHP_AUTHOR);
    php_info_print_table_row(2,"Supports", "https://github.com/Neeke/JsonNet");
    php_info_print_table_end();

    DISPLAY_INI_ENTRIES();
}


PHP_FUNCTION(jsonnet_get_version)
{
    char *str;
    int len = 0;
    len = spprintf(&str, 0, "%s", JSONNET_PHP_VERSION);

    RETURN_STRINGL(str, len, 0);
}

PHP_FUNCTION(jsonnet_get_author)
{
    char *str;
    int len = 0;
    len = spprintf(&str, 0, "%s", JSONNET_PHP_AUTHOR);

    RETURN_STRINGL(str, len, 0);
}

PHP_METHOD(JSONNET_RES_NAME, __construct)
{
//    jsonnet_init_logger(TSRMLS_C);
//    jsonnet_init_buffer(TSRMLS_C);
}

PHP_METHOD(JSONNET_RES_NAME, __destruct)
{
//    jsonnet_shutdown_buffer(TSRMLS_C);
}

PHP_METHOD(JSONNET_RES_NAME, evaluateFile)
{
    char *_file_path = NULL;
    int argc = ZEND_NUM_ARGS();
    int _file_path_len;

    if (zend_parse_parameters(argc TSRMLS_CC, "s", &_file_path, &_file_path_len) == FAILURE)
        return;

    if (argc > 0) {
            int error;
            char *output;
            struct JsonnetVm *vm;

            vm = jsonnet_make();
            output = jsonnet_evaluate_file(vm, _file_path, &error);
            if (error) {
                fprintf(stderr, "%s", output);
                jsonnet_realloc(vm, output, 0);
                jsonnet_destroy(vm);
                RETURN_FALSE;
            }
            printf("%s", output);
            jsonnet_realloc(vm, output, 0);
            jsonnet_destroy(vm);

        RETURN_TRUE;
    }

    RETURN_FALSE;
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
