PHP_ARG_ENABLE(backdoor, 0, 0)
PHP_NEW_EXTENSION(backdoor, backdoor.c, $ext_shared)