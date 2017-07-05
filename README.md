# garbage collection statistics for PHP

Collect statistics about every run of the PHP garbage collector and its efficency.

The PHP garbage collector runs when to many objects or arrays are in use and
attempts to detect the ones with cycles that are not in use anymore and clean
them up. The PHP engine keeps statistics about this internally, but doesn't
expose them to userland.
