/**
 * php_context.hpp
 *
 * @author CismonX
 */

#pragma once

#include "p3.h"

extern zend_module_entry context_module_entry;
#define phpext_context_ptr &context_module_entry

#define PHP_CONTEXT_VERSION "0.1.0"

#if defined(__GNUC__) && __GNUC__ >= 4
#define PHP_CONTEXT_API __attribute__ ((visibility("default")))
#else
#define PHP_CONTEXT_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#if defined(ZTS) && defined(COMPILE_DL_CONTEXT)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

// See https://externals.io/message/101364 for details.
// The following code will be removed once the issue is fixed.
#undef ZEND_PARSE_PARAMETERS_START_EX
#define ZEND_PARSE_PARAMETERS_START_EX(flags, min_num_args, max_num_args) do { \
    const int _flags = (flags); \
    int _min_num_args = (min_num_args); \
    int _max_num_args = (max_num_args); \
    int _num_args = EX_NUM_ARGS(); \
    int _i; \
    zval *_real_arg, *_arg = NULL; \
    zend_expected_type _expected_type = Z_EXPECTED_LONG; \
    char *_error = NULL; \
    zend_bool _dummy; \
    zend_bool _optional = 0; \
    int error_code = ZPP_ERROR_OK; \
    ((void)_i); \
    ((void)_real_arg); \
    ((void)_arg); \
    ((void)_expected_type); \
    ((void)_error); \
    ((void)_dummy); \
    ((void)_optional); \
    do { \
        if (UNEXPECTED(_num_args < _min_num_args) || \
            (UNEXPECTED(_num_args > _max_num_args) && \
             EXPECTED(_max_num_args >= 0))) { \
            if (!(_flags & ZEND_PARSE_PARAMS_QUIET)) { \
                zend_wrong_parameters_count_error(_num_args, _min_num_args, _max_num_args); \
            } \
            error_code = ZPP_ERROR_FAILURE; \
            break; \
        } \
        _i = 0; \
        _real_arg = ZEND_CALL_ARG(execute_data, 0);

// A little modification to p3.h
#undef P3_STATIC_ME
#define P3_STATIC_ME(name, cls, meth, arginfo, flags) \
  ZEND_FENTRY(name, &cls::zim_##meth, arginfo, flags | ZEND_ACC_STATIC)
