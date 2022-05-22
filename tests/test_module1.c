#include "../ctdd.h"

ctdd_test(name1) {
  ctdd_check(1 == 2 - 1); // expression inside ctdd_check must evaluate to true for the test to pass
  if(4 != 2 + 2) {
    ctdd_fail("lol, math is wrong"); // fail will fail when executed. You must give it a message to display
  }
  ctdd_assert(6 == 3 * 2, "i guess just multiplication doesn't work"); // similar to ctdd_check, but lets you choose the message
}

ctdd_test_suite(test_module1) {
  ctdd_run_test(name1);
}
