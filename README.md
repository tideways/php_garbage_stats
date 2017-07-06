# garbage collection statistics for PHP

Collect statistics about every run of the PHP garbage collector and its efficency.

The PHP garbage collector runs when to many objects or arrays are in use and
attempts to detect the ones with cycles that are not in use anymore and clean
them up. The PHP engine keeps statistics about this internally, but doesn't
expose them to userland.

## Requirements

- Linux
- PHP 7+

## Installation

This repository is a PHP extension and must be installed as an extension into PHP.
For your global PHP installation in your systemt the installation after cloning this repository:

    phpize
    ./configure
    make
    sudo make install

If you have multiple PHP versions the setup boils down to:

    /path/to/phpize
    ./configure --with-php-config=/path/to/php-config
    make
    sudo make install

## Usage

For CLI scripts, you can print out a report immediately from the extension without having to change the code:

    $ php -dgc_stats.enable=1 -dgc_stats.show_report=1 my_script.php
    ## Garbage Collection Statistics for PHP by Tideways ##
    Use https://tideways.io to get realtime information about garbage collection in production.

    Found 7 garbage collection runs in current script.

    Collected | Efficency% | Duration | Memory Before | Memory After | Reduction% | Function
    ----------|------------|----------|---------------|--------------|------------|---------
            0 |     0.00 % |  0.01 ms |        365856 |       366352 |    -0.14 % | gc_collect_cycles
        10000 |   100.00 % |  3.19 ms |       4651352 |       491848 |    89.43 % | foo
         9000 |    90.00 % |  2.27 ms |       4694712 |       951208 |    79.74 % | Test::foo

    Enable the gc run collection by setting the ini variable:

```php
<?php

ini_set('gc_stats.enable', 1);
```

To access the statistics call `$retun = gc_stats()`:

```php
<?php

gc_collect_cycles();
$stats = gc_stats();
var_dump($stats);

/*
array(1) {
  [0]=>
  array(6) {
    ["collected"]=>
    int(200)
    ["duration"]=>
    int(200)
    ["memory_before"]=>
    int(400000)
    ["memory_after"]=>
    int(300000)
    ["function"]=>
    string(17) "gc_collect_cycles"
    ["stack"]=>
    array(1) {
      [0]=>
      array(3) {
        ["file"]=>
        string(%d) "/tmp/test.php"
        ["line"]=>
        int(12)
        ["function"]=>
        string(17) "gc_collect_cycles"
      }
    }
  }
}
*/
```

Each run entry contains several data points:

- `collected` is the number of items that the garbage collector cleaned up.
- `duration` is the time in microseconds it took to perform the cleanup.
- `memory_before` is the value of `memory_get_usage()` before the cleanup was started.
- `memory_after` is the value of `memory_get_usage()` after the cleanup.
- `function` is the name of the PHP function inside which the garbage
  collection is triggered. If this is `gc_collect_cycles()` it means the
  trigger was done explicitly, with all other function names triggering happend
  automatically when the GC is enabled.
- `stack` is the return value of `debug_backtrace(DEBUG_BACKTRACE_IGNORE_ARGS)`
