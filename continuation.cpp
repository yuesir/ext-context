/**
 * continuation.cpp
 *
 * @author CismonX
 */

#include "continuation.hpp"

#define PHP_CONTEXT_FUNCTION \
    [&fci, &fcc](ctx::continuation&& cont) { \
        auto obj = p3::allocObject<continuation>(class_entry, \
            [&cont](continuation* ptr) { \
                new(ptr) continuation(std::move(cont)); \
            }); \
        zval param, retval; \
        ZVAL_OBJ(&param, obj); \
        fci.params = &param; \
        fci.retval = &retval; \
        zend_call_function(&fci, &fcc); \
        return p3::toObject<continuation>(&retval)->get_continuation(); \
    }

P3_METHOD(continuation, resume)
{
    auto fci = empty_fcall_info;
    auto fcc = empty_fcall_info_cache;
    ZEND_PARSE_PARAMETERS_START(0, 1)
        Z_PARAM_OPTIONAL
        Z_PARAM_FUNC(fci, fcc);
    ZEND_PARSE_PARAMETERS_END();
    auto num_args = EX_NUM_ARGS();
    if (num_args) {
        fci.param_count = 1;
        fci.no_separation = 0;
    }
    RETVAL_OBJ(p3::allocObject<continuation>(class_entry,
        [num_args, &fci, &fcc, this](continuation* ptr) {
            new(ptr) continuation(num_args ?
                continuation_.resume_with(PHP_CONTEXT_FUNCTION) :
                continuation_.resume()
            );
        }));
}

P3_METHOD(continuation, swap)
{
    zval* obj;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS(obj, class_entry)
    ZEND_PARSE_PARAMETERS_END();
    auto other = p3::toObject<continuation>(obj);
    continuation_.swap(other->continuation_);
}

int continuation::compare(const continuation& other) const
{
    if (continuation_ == other.continuation_)
        return 0;
    if (continuation_ > other.continuation_)
        return 1;
    return 0;
}

P3_METHOD(continuation, callcc)
{
    auto fci = empty_fcall_info;
    auto fcc = empty_fcall_info_cache;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_FUNC(fci, fcc);
    ZEND_PARSE_PARAMETERS_END();
    fci.param_count = 1;
    fci.no_separation = 0;
    RETVAL_OBJ(p3::allocObject<continuation>(class_entry,
        [&fci, &fcc](continuation* ptr) {
            new(ptr) continuation(ctx::callcc(PHP_CONTEXT_FUNCTION));
        }));
}

zend_class_entry* continuation::class_entry;
zend_object_handlers continuation::handlers;