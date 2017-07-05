--TEST--
garbage_stats: No memleak, return empty runs
--FILE--
<?php

$data = gc_stats();

var_dump($data);
--EXPECTF--
array(0) {
}
