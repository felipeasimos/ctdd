#include "../ctdd.h"

ctdd_test(name3) {

  ctdd_check(1);
  ctdd_check(1);
  ctdd_check(1);
  ctdd_check(1);
  ctdd_check(1);
  ctdd_check(1);
  ctdd_check(1);
  ctdd_check(1);
  ctdd_check(1);
  ctdd_check(1);
  ctdd_check(1);
  ctdd_check(1);
}

ctdd_test(name4) {

  ctdd_check(1);
  ctdd_check(1);
  ctdd_check(1);
  ctdd_check(1);
  ctdd_check(1);
  ctdd_check(1);
  ctdd_check(1);
  ctdd_check(1);
  ctdd_check(1);
}

ctdd_test_suite(test_module3) {
  ctdd_run_test(name3);
  ctdd_run_test(name4);
}

ctdd_test(name7) {
  ctdd_check(1);
}
ctdd_test(name8) {
  ctdd_check(1);
  ctdd_check(1);
  ctdd_check(1);
  ctdd_check(1);
  ctdd_check(1);
}
ctdd_test(name9) {
  ctdd_check(1);
  ctdd_check(1);
  ctdd_check(1);
  ctdd_check(1);
}

ctdd_test_suite(test_module5) {
  ctdd_run_test(name7);
  ctdd_run_test(name8);
  ctdd_run_test(name9);
}
