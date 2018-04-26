/**
 * context.cpp
 * 
 * @author CismonX
 */

#include "continuation.hpp"

/* {{{ continuation_resume_arginfo */
ZEND_BEGIN_ARG_INFO(continuation_resume_arginfo, 0)
    ZEND_ARG_CALLABLE_INFO(0, ctx_func, 0)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ continuation_swap_arginfo */
ZEND_BEGIN_ARG_INFO(continuation_swap_arginfo, 0)
    ZEND_ARG_OBJ_INFO(0, other, Context\\continuation, 0)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ callcc_arginfo */
ZEND_BEGIN_ARG_INFO(callcc_arginfo, 0)
    ZEND_ARG_CALLABLE_INFO(0, ctx_func, 0)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ continuation_methods */
static zend_function_entry continuation_methods[] = {
    P3_ME(continuation, resume, continuation_resume_arginfo, ZEND_ACC_PUBLIC)
    P3_ME(continuation, swap, continuation_swap_arginfo, ZEND_ACC_PUBLIC)
    P3_ME(continuation, valid, nullptr, ZEND_ACC_PUBLIC)
    PHP_FE_END
};
/* }}} */

/* {{{ context_functions */
static zend_function_entry context_functions[] = {
    P3_STATIC_ME(Context\\callcc, continuation, callcc, callcc_arginfo, ZEND_ACC_PUBLIC)
    PHP_FE_END
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(context)
{
    p3::initClassEntry<continuation>("Context\\Continuation", continuation_methods);
    return SUCCESS;
}
/* }}} */

/* {{{ context_module_entry */
zend_module_entry context_module_entry = {
    STANDARD_MODULE_HEADER,
    "context",
    context_functions,
    PHP_MINIT(context),
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    PHP_CONTEXT_VERSION,
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_CONTEXT
ZEND_GET_MODULE(context)
#endif // COMPILE_DL_CONTEXT