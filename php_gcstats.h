#ifndef PHP_GARBAGE_STATS_H
#define PHP_GARBAGE_STATS_H

extern zend_module_entry garbage_stats_module_entry;
#define phpext_garbage_stats_ptr &garbage_stats_module_entry

#define PHP_GARBAGE_STATS_VERSION "0.1.0"

#if defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_GARBAGESTATS_API __attribute__ ((visibility("default")))
#else
#	define PHP_GARBAGESTATS_API
#endif

#endif	/* PHP_GARBAGESTATS_H */
