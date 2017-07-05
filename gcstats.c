#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_gcstats.h"

PHP_FUNCTION(gc_stats)
{
}


PHP_MINIT_FUNCTION(garbage_stats)
{
    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(garbage_stats)
{
    return SUCCESS;
}

PHP_MINFO_FUNCTION(garbage_stats)
{
}

const zend_function_entry garbage_stats_functions[] = {
    PHP_FE(gc_stats,	NULL)
    PHP_FE_END
};

zend_module_entry garbage_stats_module_entry = {
    STANDARD_MODULE_HEADER,
    "garbage_stats",
    garbage_stats_functions,
    PHP_MINIT(garbage_stats),
    PHP_MSHUTDOWN(garbage_stats),
    NULL,
    NULL,
    PHP_MINFO(garbage_stats),
    PHP_GARBAGE_STATS_VERSION,
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_GARBAGE_STATS
ZEND_GET_MODULE(garbage_stats)
#endif
