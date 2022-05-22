#ifndef CTDD_H
#define CTDD_H

// ctdd - Single header unit test framework for C
// To use this, checkout the examples at tests/

#include <stdio.h>
#include <sys/time.h>

#define __CTDD_MESSAGE_LEN 1024

#define __ctdd_fail_code 0
#define __ctdd_success_code 1

typedef struct __CTDD_SUITE_VARS {
  // where error messages are temporarily stored
  char error_message[__CTDD_MESSAGE_LEN];

  unsigned long num_tests;
  unsigned long test_time_millisecs;
  unsigned long suite_time_millisecs;
  int status;
} __CTDD_SUITE_VARS;

static struct __CTDD_SUITE_VARS __ctdd_suite_vars = {0};

// define multi statement macro more easily
#define __ctdd_code_block(code_block) do {\
  code_block\
} while(0)

#define __ctdd_link_suite_field(test_suite, field, type)  type __ctdd_test_suite_##field_##test_suite = &__ctdd_suite_##field
#define __ctdd_use_suite_field(test_suite, field, type) extern type __ctdd_test_suite_##field_##test_suite
#define __ctdd_get_suite_field(test_suite, field) *__ctdd_test_suite_##field_##test_suite

#define __ctdd_link_suite_struct(test_suite) __CTDD_SUITE_VARS* __ctdd_test_suite_struct_##test_suite = &__ctdd_suite_vars
#define __ctdd_use_suite_struct(test_suite) extern __CTDD_SUITE_VARS* __ctdd_test_suite_struct_##test_suite
#define __ctdd_get_suite_struct(test_suite) __ctdd_test_suite_struct_##test_suite

#define __ctdd_link_suite_func(test_suite) void (*__ctdd_test_suite_func_##test_suite)() = &test_suite
#define __ctdd_use_suite_func(test_suite) extern void (*__ctdd_test_suite_func_##test_suite)()

// define a single test case, which calls ctdd_assert, ctdd_check and ctdd_fail
#define ctdd_test(test) static void test()

// define a test suite, which calls ctdd_run_test for each test case
#define ctdd_test_suite(test_suite)\
static void test_suite();\
__ctdd_link_suite_struct(test_suite);\
__ctdd_link_suite_func(test_suite);\
static void test_suite()

// runs a single test case
#define ctdd_run_test(test) __ctdd_code_block(\
    __ctdd_suite_vars.status = __ctdd_success_code;\
    struct timeval start;\
    struct timeval stop;\
    gettimeofday(&start, NULL);\
    test();\
    gettimeofday(&stop, NULL);\
    if(__ctdd_suite_vars.status == __ctdd_fail_code) {\
      fprintf(stderr, "\x1b[31m%lu\x1b[1m ❌\x1b[0m\n%s\n", __ctdd_suite_vars.num_tests, __ctdd_suite_vars.error_message);\
      return;\
    } else {\
      unsigned long secs = stop.tv_sec - start.tv_sec;\
      unsigned long millisecs = stop.tv_usec - start.tv_usec;\
      fprintf(stderr, "\x1b[32m%lu\x1b[1m ✅\x1b[0m %lu.%lu secs\n", __ctdd_suite_vars.num_tests, secs, millisecs);\
      __ctdd_suite_vars.num_tests++;\
      __ctdd_suite_vars.test_time_millisecs = secs * 10e6 + millisecs;\
    }\
  )

// runs test suite
#define ctdd_run_suite(test_suite)\
  __ctdd_use_suite_struct(test_suite);\
  __ctdd_use_suite_func(test_suite);\
  __ctdd_code_block(\
    fprintf(stderr, "%s\n", #test_suite);\
    __ctdd_test_suite_func_##test_suite();\
    if(__ctdd_get_suite_struct(test_suite)->status == __ctdd_fail_code) {\
      fprintf(stderr, "fail at %s\n", #test_suite);\
      return 1;\
    }\
  )

// assert condition
#define ctdd_assert(test, message) __ctdd_code_block(\
    if(!(test)) {\
      snprintf(\
          __ctdd_suite_vars.error_message,\
          __CTDD_MESSAGE_LEN,\
          "Test case '%s' \x1b[31mFAILED ❌\x1b[0m\n"\
            "\tFile: \x1b[33m%s\x1b[0m\n"\
            "\tLine: \x1b[33m%d\x1b[0m\n"\
            "\tExpression: \x1b[33m%s\x1b[0m",\
            __func__,\
            __FILE__,\
            __LINE__,\
            message);\
      __ctdd_suite_vars.status = __ctdd_fail_code;\
      return;\
    } else {\
      fprintf(stderr, ".");\
    }\
  )

// assert check
#define ctdd_check(test) ctdd_assert(test, #test)

// just fail
#define ctdd_fail(message) ctdd_assert(0, message)

#endif