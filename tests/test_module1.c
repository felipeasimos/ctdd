#include "../ctdd.h"

ctdd_test(name1) {
  ctdd_check(1);
  ctdd_check(1);
  ctdd_check(1);
  ctdd_check(1);
}

ctdd_test_suite(test_module1) {
  ctdd_run_test(name1);
}
