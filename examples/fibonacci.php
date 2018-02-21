<?php
/**
 * examples/fibonacci.php
 *
 * A simple demonstration for using ext-context.
 * Generates the first ten fibonacci numbers.
 * Ported from Boost.Context's official documentation.
 *
 * @author CismonX
 */

use Context\Continuation;

$a = 0;
$source = Context\callcc(function (Continuation &$sink) use (&$a) {
    $b = 1;
    for (;;) {
        $sink = $sink->resume();
        $next = $a + $b;
        $a = $b;
        $b = $next;
    }
    return $sink;
});
for ($j = 0; $j < 10; ++$j) {
    echo $a, ' ';
    $source = $source->resume();
}
