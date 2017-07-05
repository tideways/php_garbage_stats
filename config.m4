PHP_ARG_ENABLE(garbage_stats, weather to enable garbage_stats support, [    --enable-garbage-stats      Enable garbage stats support])

if test "$PHP_GARBAGE_STATS" != "no"; then
    PHP_NEW_EXTENSION(garbage_stats, gcstats.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
