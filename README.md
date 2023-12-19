# ctdd

A simple, single-header C unit test framework. Heavely inspired by [minunit](https://github.com/siu/minunit).

## How to Use

Just copy the `ctdd.h` file to wherever you want and include it in your test files.
You can either put everything in the same file or use one test suite per `.c` file.

Mind that additional header files to expose test suites and test cases functions are not needed.

## Example

* `test_main.c`

```
#include "../ctdd.h"
int main() {

  ctdd_run_suite(test_suite1);
  ctdd_run_suite_with_report(test_suite2);
  ctdd_run_suite_and_save_to_csv(test_suite1, "tests.csv");
}
```

* `test_suite1.c`

```
#include "../ctdd.h"
ctdd_test(test1) {

  ctdd_check(1 == 2 - 1); // expression inside ctdd_check must evaluate to true for the test to pass
  if(4 != 2 + 2) {
    ctdd_fail("lol, math is wrong"); // fail will fail when executed. You must give it a message to display
  }
  ctdd_assert(6 == 3 * 2, "i guess just multiplication doesn't work"); // similar to ctdd_check, but lets you choose the message
}

ctdd_suite(test_module1) {
  ctdd_configure(setup, teardown); // set fixtures to be used for each test case
  ctdd_run_test(test1); // must be called for each test
}
```
