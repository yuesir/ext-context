PHP_ARG_ENABLE(context,         for context support,
[  --enable-context            Enable context support])

PHP_ARG_ENABLE(context-debug,   for debug support,
[  --enable-context-debug      Compile with debug symbols ], no, no)

if test "$PHP_CONTEXT" != "no"; then
  PHP_REQUIRE_CXX()

  if test "$(ls p3.h 2>/dev/null)" = ""; then
    wget https://raw.githubusercontent.com/phplang/p3/master/p3.h &>/dev/null
  fi

  CXXFLAGS="-std=c++11 "
  if test "$PHP_ASIO_DEBUG" != "no"; then
    CXXFLAGS+="-g -O0 "
  else
    CXXFLAGS+="-O2 "
  fi

  PHP_SUBST(CONTEXT_SHARED_LIBADD)
  PHP_ADD_LIBRARY(boost_context, 1, CONTEXT_SHARED_LIBADD)

  PHP_NEW_EXTENSION(context, context.cpp continuation.cpp, $ext_shared)
fi
