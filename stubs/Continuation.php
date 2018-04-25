<?php
/**
 * stubs/Continuation.php
 *
 * @author CismonX
 */

namespace Context;

class Continuation
{
    /**
     * Resume current continuation.
     *
     * @param callable $ctx_func[optional] (Continuation&) -> Continuation
     * @return Continuation
     */
    function resume(callable $ctx_func) {}
    /**
     * Swap context with another continuation.
     *
     * @param Continuation $other
     * @return void
     */
    function swap(Continuation $other) {}
}