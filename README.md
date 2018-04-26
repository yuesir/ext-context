# ext-context

Context switching library for PHP.

## 1. Requirements

* PHP 7.0+

* Boost.Context (libboost version no lower than 1.65.0)

* Compiler which supports C++11

## 2. Documentation

* See [here](stubs/) for stubs.

* This library behaves similar to the Boost.Context library. See [here](http://www.boost.org/doc/libs/1_66_0/libs/context/doc/html/context/cc.html) for Boost's official documentation.

* See [here](examples/) for examples.

## 3. Notes

**The `resume()` method with callback will segfault. Working on it.**

Memory leaks may exist, as ZendMM will warn you if you are using a debug build of PHP.

These leaks are mostly caused by never-returning closures, which is nothing to be worried about, even in PHP-CLI.

However, a few third-party extensions use hackish ways to manage its memory, which may be a problem. make sure to test them before going into production.