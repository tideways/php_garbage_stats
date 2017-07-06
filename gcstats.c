#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_gcstats.h"
#include "zend_builtin_functions.h"

ZEND_DECLARE_MODULE_GLOBALS(garbage_stats)

int (*original_gc_collect_cycles)(void);
int gc_stats_collect_cycles(void);

PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("gc_stats.enable", "0", PHP_INI_ALL, OnUpdateLong, enabled, zend_garbage_stats_globals, garbage_stats_globals)
PHP_INI_END()

PHP_FUNCTION(gc_stats)
{
    RETURN_ZVAL(&GSG(runs), 1, 0);
}

static uint64_t clock_get_monotonic() {
    struct timespec s;
    clock_gettime(CLOCK_MONOTONIC, &s);

    return s.tv_sec * 1000000 + s.tv_nsec / 1000;
}

int gc_stats_collect_cycles(void)
{
    int ret;
    uint32_t collected;
    zval run, stack;
    zend_execute_data *execute_data;
    zend_function *current_function;
    long int memory;
    uint64_t start;

    if (!GSG(enabled)) {
        return original_gc_collect_cycles();
    }

    collected = GC_G(collected);
    start = clock_get_monotonic();
    memory = zend_memory_usage(0);
    execute_data = EG(current_execute_data);

    ret = original_gc_collect_cycles();

    array_init(&run);

    add_assoc_long(&run, "collected", GC_G(collected) - collected);
    add_assoc_long(&run, "duration", clock_get_monotonic() - start);
    add_assoc_long(&run, "memory_before", memory);
    add_assoc_long(&run, "memory_after", zend_memory_usage(0));

    current_function = execute_data->func;

    if (current_function->common.function_name) {
        add_assoc_str_ex(&run, "function", sizeof("function")-1, current_function->common.function_name);
    }

    if (current_function->common.scope && current_function->common.scope->name) {
        add_assoc_str_ex(&run, "class", sizeof("class")-1, current_function->common.scope->name);
    }

    zend_fetch_debug_backtrace(&stack, 0, DEBUG_BACKTRACE_IGNORE_ARGS, 0 TSRMLS_CC);
    add_assoc_zval(&run, "stack", &stack);

    zend_hash_next_index_insert(Z_ARRVAL(GSG(runs)), &run);

    return ret;
}

PHP_GINIT_FUNCTION(garbage_stats)
{
    garbage_stats_globals->enabled = 0;
}

PHP_GSHUTDOWN_FUNCTION(garbage_stats)
{
}


PHP_MINIT_FUNCTION(garbage_stats)
{
    REGISTER_INI_ENTRIES();

    original_gc_collect_cycles = gc_collect_cycles;
    gc_collect_cycles = gc_stats_collect_cycles;

    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(garbage_stats)
{
    gc_collect_cycles = original_gc_collect_cycles;

    return SUCCESS;
}

PHP_RINIT_FUNCTION(garbage_stats)
{
    zval_ptr_dtor(&GSG(runs));
    array_init(&GSG(runs));

    return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(garbage_stats)
{
    zval_ptr_dtor(&GSG(runs));
    ZVAL_NULL(&GSG(runs));

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
    STANDARD_MODULE_HEADER_EX,
    NULL,
    NULL,
    "garbage_stats",
    garbage_stats_functions,
    PHP_MINIT(garbage_stats),
    PHP_MSHUTDOWN(garbage_stats),
    PHP_RINIT(garbage_stats),
    PHP_RSHUTDOWN(garbage_stats),
    PHP_MINFO(garbage_stats),
    PHP_GARBAGE_STATS_VERSION,
    PHP_MODULE_GLOBALS(garbage_stats),
    PHP_GINIT(garbage_stats),
    PHP_GSHUTDOWN(garbage_stats),
    NULL,
    STANDARD_MODULE_PROPERTIES_EX
};

#ifdef COMPILE_DL_GARBAGE_STATS
ZEND_GET_MODULE(garbage_stats)
#endif
