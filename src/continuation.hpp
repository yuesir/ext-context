/**
 * continuation.hpp
 *
 * @author CismonX
 */

#pragma once

#include "php_context.hpp"

#include <boost/context/continuation.hpp>

namespace ctx = boost::context;

class continuation
{
    /// Boost.Context continuation instance.
    ctx::continuation continuation_;

public:
    /**
     * "Move" constructor.
     */
    explicit continuation(
        ctx::continuation&& other
    ) noexcept : continuation_(std::move(other)) {}

    /* {{{ proto Continuation Continuation::resume([callable ctx_func]);
     * Resume current continuation.
     * You can execute a new function on top of resumed continuation. */
    P3_METHOD_DECLARE(resume);
    /* }}} */

    /* {{{ proto void Continuation::swap(Continuation other);
     * Swap context with another continuation. */
    P3_METHOD_DECLARE(swap);
    /* }}} */

    /**
     * Whether the continuation is valid.
     */
    zend_bool toBool() const
    {
        return bool(continuation_);
    }

    /**
     * Comparation between two continuations.
     */
    int compare(const continuation& other) const;

    /**
     * Get rvalue refernce of wrapped continuation.
     */
    ctx::continuation&& get_continuation()
    {
        return std::move(continuation_);
    }

    /* {{{ proto Continuation callcc(callable ctx_func);
     * Capture current continuation and trigger context switch. */
    static P3_METHOD_DECLARE(callcc);
    /* }}} */

    static zend_class_entry* class_entry;
    static zend_object_handlers handlers;
};