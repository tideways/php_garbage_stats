--TEST--
garbage_stats: run gc_collect_cyles();
--FILE--
<?php

ini_set("gc_stats.enable", 1);

for ($i = 0; $i < 100; $i++) {
    $a = new stdClass();
    $b = new stdClass();
    $b->a = $a;
    $a->b = $b;
    unset($a, $b);
}
gc_collect_cycles();

$data = gc_stats();

var_dump($data);
--EXPECTF--
array(1) {
  [0]=>
  array(4) {
    ["collected"]=>
    int(200)
    ["duration"]=>
    int(%d)
    ["function"]=>
    string(17) "gc_collect_cycles"
    ["stack"]=>
    array(1) {
      [0]=>
      array(3) {
        ["file"]=>
        string(%d) "%s"
        ["line"]=>
        int(12)
        ["function"]=>
        string(17) "gc_collect_cycles"
      }
    }
  }
}
