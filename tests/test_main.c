#include "../ctdd.h"

ctdd_test(name2) {

  ctdd_check(1);
}

ctdd_test_suite(test_module2) {
  ctdd_run_test(name2);
}

int main() {
  ctdd_run_suite(test_module1);
  ctdd_run_suite(test_module2);
  ctdd_run_suite(test_module3);
  return 0;
}
