#ifndef CTDD_H
#define CTDD_H

// ctdd - Single header unit test framework for C
// To use this, checkout the examples at tests/

#include <stdio.h>
#include <time.h>

#define __CTDD_MESSAGE_LEN 1024

#define __ctdd_fail_code 0
#define __ctdd_success_code 1

typedef struct __CTDD_SUITE_STATS {

  int status;
  unsigned long num_asserts;
  clock_t time;
} __CTDD_TEST_STATS;

// where error messages are temporarily stored
static char __ctdd_error_message[__CTDD_MESSAGE_LEN];
// total number of test cases in this suite
static unsigned long __ctdd_num_test_cases_in_suite = 0;
// total testing time
static clock_t __ctdd_time = 0;
// status code
static int __ctdd_test_status = __ctdd_success_code;

// define multi statement macro more easily
#define __ctdd_code_block(code_block) do {\
  code_block\
} while(0)

#define __ctdd_link_suite_struct(test_suite) int* __ctdd_test_suite_struct_##test_suite = &__ctdd_test_status
#define __ctdd_link_suite_func(test_suite) void (*__ctdd_test_suite_func_##test_suite)() = &test_suite
#define __ctdd_use_suite_func(test_suite) extern void (*__ctdd_test_suite_func_##test_suite)()
#define __ctdd_use_suite_struct(test_suite) extern int* __ctdd_test_suite_struct_##test_suite

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
    __ctdd_test_status = __ctdd_success_code;\
    test();\
    if(__ctdd_test_status == __ctdd_fail_code) {\
      fprintf(stderr, "\x1b[31m%lu\n\x1b[1mFAIL!\x1b[0m\n%s\n", __ctdd_num_test_cases_in_suite, __ctdd_error_message);\
      return;\
    } else {\
      fprintf(stderr, "\x1b[32m%lu\x1b[0m\n", __ctdd_num_test_cases_in_suite);\
    }\
  )

// runs test suite
#define ctdd_run_suite(test_suite)\
  __ctdd_use_suite_struct(test_suite);\
  __ctdd_use_suite_func(test_suite);\
  __ctdd_code_block(\
    fprintf(stderr, "%s\n", #test_suite);\
    __ctdd_test_suite_func_##test_suite();\
    if(*__ctdd_test_suite_struct_##test_suite == __ctdd_fail_code) {\
      fprintf(stderr, "fail at %s\n", #test_suite);\
      return 1;\
    }\
  )

// assert condition
#define ctdd_assert(test, message) __ctdd_code_block(\
    if(!(test)) {\
      snprintf(__ctdd_error_message, __CTDD_MESSAGE_LEN, "\t%s failed:\n\t\x1b[33m%s:%d: \"%s\"\x1b[0m", __func__, __FILE__, __LINE__, message);\
      __ctdd_test_status = __ctdd_fail_code;\
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
