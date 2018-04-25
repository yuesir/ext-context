PHP_ARG_ENABLE(context,         for context support,
[  --enable-context            Enable context support])

if test "$PHP_CONTEXT" != "no"; then
  PHP_REQUIRE_CXX()

  if test "$(ls p3.h 2>/dev/null)" = ""; then
    wget https://raw.githubusercontent.com/phplang/p3/master/p3.h &>/dev/null
  fi

  PHP_NEW_EXTENSION(context, context.cpp continuation.cpp, $ext_shared,, -std=c++11)
  PHP_ADD_LIBRARY(boost_context, 1, CONTEXT_SHARED_LIBADD)
  PHP_SUBST(CONTEXT_SHARED_LIBADD)
fi
