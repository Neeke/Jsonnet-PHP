/*
  +----------------------------------------------------------------------+
  | Jsonnet                                                              |
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

#include "php_jsonnet.h"
#include "libjsonnet.h"

ZEND_DECLARE_MODULE_GLOBALS(jsonnet)

static int le_jsonnet;

const zend_function_entry jsonnet_functions[] =
{
    PHP_FE(jsonnet_get_version, NULL)
    PHP_FE(jsonnet_get_author,  NULL)
    {
        NULL, NULL, NULL
    }
};

ZEND_BEGIN_ARG_INFO_EX(jsonnet_evaluateFile_arginfo, 0, 0, 1)
ZEND_ARG_INFO(0, file_path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(jsonnet_evaluateSnippet_arginfo, 0, 0, 1)
ZEND_ARG_INFO(0, snippet_string)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(jsonnet_fmtFile_arginfo, 0, 0, 1)
ZEND_ARG_INFO(0, file_path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(jsonnet_fmtSnippet_arginfo, 0, 0, 1)
ZEND_ARG_INFO(0, snippet_string)
ZEND_END_ARG_INFO()

const zend_function_entry jsonnet_methods[] =
{
    PHP_ME(JSONNET_RES_NAME, __construct,   NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(JSONNET_RES_NAME, __destruct,    NULL, ZEND_ACC_PUBLIC | ZEND_ACC_DTOR)

    PHP_ME(JSONNET_RES_NAME, evaluateFile,          jsonnet_evaluateFile_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(JSONNET_RES_NAME, evaluateSnippet,       jsonnet_evaluateSnippet_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(JSONNET_RES_NAME, fmtFile,               jsonnet_fmtFile_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(JSONNET_RES_NAME, fmtSnippet,            jsonnet_fmtSnippet_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)

    {
        NULL, NULL, NULL
    }
};

const zend_module_dep jsonnet_deps[] = {
    ZEND_MOD_REQUIRED("json")
    ZEND_MOD_END
};

zend_module_entry jsonnet_module_entry =
{
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER_EX, NULL,
    jsonnet_deps,
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
    jsonnet_ce = JSONNET_ZEND_REGISTER_CLASS(&jsonnet);
    jsonnet_ce->ce_flags = ZEND_ACC_IMPLICIT_PUBLIC;

    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(jsonnet)
{
    UNREGISTER_INI_ENTRIES();

    return SUCCESS;
}

PHP_RINIT_FUNCTION(jsonnet)
{
    return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(jsonnet)
{
    return SUCCESS;
}

PHP_MINFO_FUNCTION(jsonnet)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "Jsonnet support", "Enabled");
    php_info_print_table_row(2, "Jsonnet LibJsonnet Information", LIB_JSONNET_VERSION);
    php_info_print_table_row(2, "Jsonnet Version", JSONNET_PHP_VERSION);
    php_info_print_table_row(2, "Jsonnet Author", JSONNET_PHP_AUTHOR);
    php_info_print_table_row(2, "Jsonnet Supports", "https://github.com/Neeke/Jsonnet-PHP");
    php_info_print_table_end();

    DISPLAY_INI_ENTRIES();
}


PHP_FUNCTION(jsonnet_get_version)
{
    JSONNET_RETURN_STRINGL(JSONNET_PHP_VERSION, strlen(JSONNET_PHP_VERSION));
}

PHP_FUNCTION(jsonnet_get_author)
{
    JSONNET_RETURN_STRINGL(JSONNET_PHP_AUTHOR, strlen(JSONNET_PHP_AUTHOR));
}

PHP_METHOD(JSONNET_RES_NAME, __construct)
{

}

PHP_METHOD(JSONNET_RES_NAME, __destruct)
{

}

PHP_METHOD(JSONNET_RES_NAME, evaluateFile)
{
    int argc = ZEND_NUM_ARGS();
    int _file_path_len, error;

    char *output, *_file_path = NULL;
    struct JsonnetVm *vm;

    zval *err, *result, *resultZval;

    if (zend_parse_parameters(argc TSRMLS_CC, "s", &_file_path, &_file_path_len) == FAILURE)
        return;

    if (argc > 0 && _file_path_len > 0)
    {

        vm = jsonnet_make();
        output = jsonnet_evaluate_file(vm, _file_path, &error);

        if (error)
        {
            JSONNET_MAKE_ZVAL(err);
            JSONNET_ZVAL_STRING(err,output);

            jsonnet_realloc(vm, output, 0);
            jsonnet_destroy(vm);

            zend_throw_exception(php_com_exception_class_entry, Z_STRVAL_P(err), CODE_ERROR TSRMLS_CC);
            JSONNET_ZVAL_PTR_DTOR(err);
            RETURN_FALSE;
        }

        JSONNET_MAKE_ZVAL(result);
        JSONNET_ZVAL_STRING(result,output);

        jsonnet_realloc(vm, output, 0);
        jsonnet_destroy(vm);

        JSONNET_MAKE_ZVAL(resultZval);
        php_json_decode(resultZval, Z_STRVAL_P(result), Z_STRLEN_P(result), 1, 512 TSRMLS_CC);

        if(Z_TYPE_P(resultZval) == IS_NULL)
        {
            JSONNET_ZVAL_PTR_DTOR(result);
            JSONNET_ZVAL_PTR_DTOR(resultZval);
            zend_throw_exception(php_com_exception_class_entry, "Jsonnet::evaluateFile #error", CODE_ERROR TSRMLS_CC);
            return;
        }

        JSONNET_ZVAL_PTR_DTOR(result);
        RETURN_ZVAL(resultZval,1,1);
    }

    zend_throw_exception(php_com_exception_class_entry, "Jsonnet::evaluateFile('filePath'), filePath is null", CODE_ERROR TSRMLS_CC);
}

PHP_METHOD(JSONNET_RES_NAME, evaluateSnippet)
{
    int argc = ZEND_NUM_ARGS();
    int _snippet_string_len, error;

    char *output, *_snippet_string = NULL;
    struct JsonnetVm *vm;

    zval *err, *result, *resultZval;

    if (zend_parse_parameters(argc TSRMLS_CC, "s", &_snippet_string, &_snippet_string_len) == FAILURE)
        return;

    if (argc > 0 && _snippet_string_len > 0)
    {
        vm = jsonnet_make();
        output = jsonnet_evaluate_snippet(vm, "snippet", _snippet_string, &error);

        if (error)
        {
            JSONNET_MAKE_ZVAL(err);
            JSONNET_ZVAL_STRING(err,output);

            jsonnet_realloc(vm, output, 0);
            jsonnet_destroy(vm);

            zend_throw_exception(php_com_exception_class_entry, Z_STRVAL_P(err), CODE_ERROR TSRMLS_CC);
            JSONNET_ZVAL_PTR_DTOR(err);
            RETURN_FALSE;
        }

        JSONNET_MAKE_ZVAL(result);
        JSONNET_ZVAL_STRING(result,output);

        jsonnet_realloc(vm, output, 0);
        jsonnet_destroy(vm);

        JSONNET_MAKE_ZVAL(resultZval);
        php_json_decode(resultZval, Z_STRVAL_P(result), Z_STRLEN_P(result), 1, 512 TSRMLS_CC);

        if(Z_TYPE_P(resultZval) == IS_NULL)
        {
            JSONNET_ZVAL_PTR_DTOR(result);
            JSONNET_ZVAL_PTR_DTOR(resultZval);
            zend_throw_exception(php_com_exception_class_entry, "Jsonnet::evaluateSnippet #error", CODE_ERROR TSRMLS_CC);
            return;
        }

        JSONNET_ZVAL_PTR_DTOR(result);
        RETURN_ZVAL(resultZval,1,1);
    }

    zend_throw_exception(php_com_exception_class_entry, "Jsonnet::evaluateSnippet('string'), string is null", CODE_ERROR TSRMLS_CC);
}

PHP_METHOD(JSONNET_RES_NAME, fmtFile)
{
    int argc = ZEND_NUM_ARGS();
    int _file_path_len, error;

    char *output, *_file_path = NULL;
    struct JsonnetVm *vm;

    zval *err, *result;

    if (zend_parse_parameters(argc TSRMLS_CC, "s", &_file_path, &_file_path_len) == FAILURE)
        return;

    if (argc > 0 && _file_path_len > 0)
    {

        vm = jsonnet_make();
        output = jsonnet_fmt_file(vm, _file_path, &error);

        if (error)
        {
            JSONNET_MAKE_ZVAL(err);
            JSONNET_ZVAL_STRING(err,output);

            jsonnet_realloc(vm, output, 0);
            jsonnet_destroy(vm);

            zend_throw_exception(php_com_exception_class_entry, Z_STRVAL_P(err), CODE_ERROR TSRMLS_CC);
            JSONNET_ZVAL_PTR_DTOR(err);
            RETURN_FALSE;
        }

        JSONNET_MAKE_ZVAL(result);
        JSONNET_ZVAL_STRING(result,output);

        jsonnet_realloc(vm, output, 0);
        jsonnet_destroy(vm);

        if(Z_TYPE_P(result) == IS_NULL)
        {
            JSONNET_ZVAL_PTR_DTOR(result);
            zend_throw_exception(php_com_exception_class_entry, "Jsonnet::fmtFile #error", CODE_ERROR TSRMLS_CC);
            return;
        }

        RETURN_ZVAL(result,1,1);
    }

    zend_throw_exception(php_com_exception_class_entry, "Jsonnet::fmtFile('filePath'), filePath is null", CODE_ERROR TSRMLS_CC);
}

PHP_METHOD(JSONNET_RES_NAME, fmtSnippet)
{
    int argc = ZEND_NUM_ARGS();
    int _snippet_string_len, error;

    char *output, *_snippet_string = NULL;
    struct JsonnetVm *vm;

    zval *err, *result;

    if (zend_parse_parameters(argc TSRMLS_CC, "s", &_snippet_string, &_snippet_string_len) == FAILURE)
        return;

    if (argc > 0 && _snippet_string_len > 0)
    {

        vm = jsonnet_make();
        output = jsonnet_fmt_snippet(vm, "snippet", _snippet_string, &error);

        if (error)
        {
            JSONNET_MAKE_ZVAL(err);
            JSONNET_ZVAL_STRING(err,output);

            jsonnet_realloc(vm, output, 0);
            jsonnet_destroy(vm);

            zend_throw_exception(php_com_exception_class_entry, Z_STRVAL_P(err), CODE_ERROR TSRMLS_CC);
            JSONNET_ZVAL_PTR_DTOR(err);
            RETURN_FALSE;
        }

        JSONNET_MAKE_ZVAL(result);
        JSONNET_ZVAL_STRING(result,output);

        jsonnet_realloc(vm, output, 0);
        jsonnet_destroy(vm);

        if(Z_TYPE_P(result) == IS_NULL)
        {
            JSONNET_ZVAL_PTR_DTOR(result);
            zend_throw_exception(php_com_exception_class_entry, "Jsonnet::fmtSnippet #error", CODE_ERROR TSRMLS_CC);
            return;
        }

        RETURN_ZVAL(result,1,1);
    }

    zend_throw_exception(php_com_exception_class_entry, "Jsonnet::fmtSnippet('string'), string is null", CODE_ERROR TSRMLS_CC);
}
