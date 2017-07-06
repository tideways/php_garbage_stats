#ifndef PHP_GARBAGE_STATS_H
#define PHP_GARBAGE_STATS_H

extern zend_module_entry garbage_stats_module_entry;
#define phpext_garbage_stats_ptr &garbage_stats_module_entry

#define PHP_GARBAGE_STATS_VERSION "0.1.0"

ZEND_BEGIN_MODULE_GLOBALS(garbage_stats)
    zval runs;
    int enabled;
    int show_report;
ZEND_END_MODULE_GLOBALS(garbage_stats)

#ifdef ZTS
#define GSG(v) TSRMG(garbage_stats_globals_id, zend_garbage_stats_globals *, v)
#else
#define GSG(v) (garbage_stats_globals.v)
#endif

#if defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_GARBAGESTATS_API __attribute__ ((visibility("default")))
#else
#	define PHP_GARBAGESTATS_API
#endif

#endif	/* PHP_GARBAGESTATS_H */
