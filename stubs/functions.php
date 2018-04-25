<?php
/**
 * stubs/functions.php
 *
 * @author CismonX
 */

namespace Context;

/**
 * Capture current continuation and trigger context switch.
 *
 * @param callable $ctx_func (Continuation&) -> Continuation
 * @return Continuation
 */
function callcc(callable $ctx_func) {}