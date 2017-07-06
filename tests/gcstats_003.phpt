--TEST--
garbage_stats: trigger
--FILE--
<?php

ini_set("gc_stats.enable", 1);
gc_enable();

function foo() {
    bar();
}

function bar() {
    for ($i = 0; $i < 20000; $i++) {
        $a = new stdClass();
        $b = new stdClass();
        $b->a = $a;
        $a->b = $b;
        unset($a, $b);
    }
}

foo();

$data = gc_stats();

var_dump($data);
--EXPECTF--
array(4) {
  [0]=>
  array(6) {
    ["collected"]=>
    int(9998)
    ["duration"]=>
    int(%d)
    ["memory_before"]=>
    int(%d)
    ["memory_after"]=>
    int(%d)
    ["function"]=>
    string(3) "bar"
    ["stack"]=>
    array(2) {
      [0]=>
      array(3) {
        ["file"]=>
        string(%d) "%s"
        ["line"]=>
        int(7)
        ["function"]=>
        string(3) "bar"
      }
      [1]=>
      array(3) {
        ["file"]=>
        string(%d) "%s"
        ["line"]=>
        int(20)
        ["function"]=>
        string(3) "foo"
      }
    }
  }
  [1]=>
  array(6) {
    ["collected"]=>
    int(10000)
    ["duration"]=>
    int(%d)
    ["memory_before"]=>
    int(%d)
    ["memory_after"]=>
    int(%d)
    ["function"]=>
    string(3) "bar"
    ["stack"]=>
    array(2) {
      [0]=>
      array(3) {
        ["file"]=>
        string(%d) "%s"
        ["line"]=>
        int(7)
        ["function"]=>
        string(3) "bar"
      }
      [1]=>
      array(3) {
        ["file"]=>
        string(%d) "%s"
        ["line"]=>
        int(20)
        ["function"]=>
        string(3) "foo"
      }
    }
  }
  [2]=>
  array(6) {
    ["collected"]=>
    int(10000)
    ["duration"]=>
    int(%d)
    ["memory_before"]=>
    int(%d)
    ["memory_after"]=>
    int(%d)
    ["function"]=>
    string(3) "bar"
    ["stack"]=>
    array(2) {
      [0]=>
      array(3) {
        ["file"]=>
        string(%d) "%s"
        ["line"]=>
        int(7)
        ["function"]=>
        string(3) "bar"
      }
      [1]=>
      array(3) {
        ["file"]=>
        string(%d) "%s"
        ["line"]=>
        int(20)
        ["function"]=>
        string(3) "foo"
      }
    }
  }
  [3]=>
  array(6) {
    ["collected"]=>
    int(10000)
    ["duration"]=>
    int(%d)
    ["memory_before"]=>
    int(%d)
    ["memory_after"]=>
    int(%d)
    ["function"]=>
    string(3) "bar"
    ["stack"]=>
    array(2) {
      [0]=>
      array(3) {
        ["file"]=>
        string(%d) "%s"
        ["line"]=>
        int(7)
        ["function"]=>
        string(3) "bar"
      }
      [1]=>
      array(3) {
        ["file"]=>
        string(%d) "%s"
        ["line"]=>
        int(20)
        ["function"]=>
        string(3) "foo"
      }
    }
  }
}
