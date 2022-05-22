#include "../ctdd.h"

ctdd_test(name2) {

  ctdd_check(1);
}

ctdd_test_suite(test_module2) {
  ctdd_run_test(name2);
}

ctdd_test(name5) {

  ctdd_check(1);
}

ctdd_test(name6) {

  ctdd_check(1);
}

ctdd_test_suite(test_module4) {
  ctdd_run_test(name5);
  ctdd_run_test(name6);
}

int main() {
  ctdd_run_suite_and_save_to_csv(test_module1, "test.csv");
  ctdd_run_suite(test_module2);
  ctdd_run_suite(test_module3);
  ctdd_run_suite(test_module4);
  ctdd_run_suite(test_module5);
  return 0;
}
