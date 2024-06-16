#include "s21_calc_test.h"

START_TEST(calc_1) {
  char expression[MAX_SIZE] = "1+2+(4/2+cos(4))+3+sqrt(4)";
  double result = 0;
  s21_calculate(expression, &result, 0);
  ck_assert_ldouble_eq_tol(result, 1 + 2 + (4 / 2 + cos(4)) + 3 + sqrt(4),
                           S21_EPS);
  ck_assert_int_eq(s21_calculate(expression, &result, 0), OK);
}
END_TEST

START_TEST(calc_2) {
  char expression[MAX_SIZE] = "1 + (1 + 2";
  double result = 0;
  ck_assert_int_eq(s21_calculate(expression, &result, 0),
                   UNMATCHED_PARENTHESES);
}
END_TEST

START_TEST(calc_3) {
  char expression[MAX_SIZE] = "1 + () + 2";
  double result = 0;
  ck_assert_int_eq(s21_calculate(expression, &result, 0), CALC_ERR);
}
END_TEST

START_TEST(calc_4) {
  char expression[MAX_SIZE] = "-(2^0.5)";
  double result = 0;
  s21_calculate(expression, &result, 0);
  ck_assert_ldouble_eq_tol(result, -(pow(2, 0.5)), S21_EPS);
}
END_TEST

START_TEST(calc_5) {
  char expression[MAX_SIZE] = "-2-(-(-2))";
  double result = 0;
  s21_calculate(expression, &result, 0);
  ck_assert_ldouble_eq_tol(result, -4.0, S21_EPS);
}
END_TEST

START_TEST(calc_6) {
  char expression[MAX_SIZE] = "1+(((2+2)+5)/2)";

  double result = 0;
  s21_calculate(expression, &result, 0);
  ck_assert_ldouble_eq_tol(result, 5.5, S21_EPS);
}
END_TEST

START_TEST(calc_7) {
  char expression[MAX_SIZE] = "1.234+72.777+(+40.5/2+cos(4))+sin(1.5)";
  double result = 0;
  s21_calculate(expression, &result, 0);
  ck_assert_ldouble_eq_tol(
      result, 1.234 + 72.777 + (40.5 / 2 + cos(4)) + sin(1.5), S21_EPS);
}
END_TEST

START_TEST(calc_8) {
  char expression[MAX_SIZE] = "+1.234+72.777+40.5/2)";
  double result = 0;
  ck_assert_int_eq(s21_calculate(expression, &result, 0),
                   UNMATCHED_PARENTHESES);
}
END_TEST

START_TEST(calc_9) {
  char expression[MAX_SIZE] = "acos(x)+asin(0)*atan(-1)+log(10)+ln(2)";
  double result = 0;
  s21_calculate(expression, &result, 1);
  ck_assert_ldouble_eq_tol(
      result, acos(1) + asin(0) * atan(-1) + log10(10) + log(2), S21_EPS);
}
END_TEST

START_TEST(calc_10) {
  char expression[MAX_SIZE] = "tan(10)+(10 mod 3)";
  double result = 0;
  s21_calculate(expression, &result, 0);
  ck_assert_ldouble_eq_tol(result, tan(10) + fmod(10, 3), S21_EPS);
}
END_TEST

START_TEST(calc_11) {
  char expression[MAX_SIZE] = "1+++++++++2";
  double result = 0;
  ck_assert_int_eq(s21_calculate(expression, &result, 1), CALC_ERR);
}
END_TEST

START_TEST(calc_12) {
  char expression[MAX_SIZE] = "abc";
  double result = 0;
  ck_assert_int_eq(s21_calculate(expression, &result, 0), CALC_ERR);
}
END_TEST

START_TEST(calc_13) {
  char expression1[MAX_SIZE] = "atan(-2)";
  char expression2[MAX_SIZE] = "acos(-2)";
  char expression3[MAX_SIZE] = "asin(-2)";
  char expression4[MAX_SIZE] = "sqrt(-2)";
  char expression5[MAX_SIZE] = "log(-2)";
  char expression6[MAX_SIZE] = "ln(-2)";
  double result = 0;
  ck_assert_int_eq(s21_calculate(expression1, &result, 0), OK);
  ck_assert_int_eq(s21_calculate(expression2, &result, 0), CALC_ERR);
  ck_assert_int_eq(s21_calculate(expression3, &result, 0), CALC_ERR);
  ck_assert_int_eq(s21_calculate(expression4, &result, 0), CALC_ERR);
  ck_assert_int_eq(s21_calculate(expression5, &result, 0), CALC_ERR);
  ck_assert_int_eq(s21_calculate(expression6, &result, 0), CALC_ERR);
}
END_TEST

START_TEST(calc_14) {
  char expression1[MAX_SIZE] = "1 / 0";
  char expression2[MAX_SIZE] = "-2 ^ 0.5";
  double result = 0;
  ck_assert_int_eq(s21_calculate(expression1, &result, 0), CALC_ERR);
  ck_assert_int_eq(s21_calculate(expression2, &result, 0), CALC_ERR);
}
END_TEST

START_TEST(credit_calc_1) {
  double monthlyPayment, totalSum, overPay;
  s21_annCredit(2000000, 12, 15, &monthlyPayment, &totalSum, &overPay);
  ck_assert_ldouble_eq_tol(monthlyPayment, 180516.62, 0.001);
  ck_assert_ldouble_eq_tol(totalSum, 2166199.44, 0.001);
  ck_assert_ldouble_eq_tol(overPay, 166199.44, 0.001);
}
END_TEST

START_TEST(credit_calc_2) {
  double monthlyPayment, totalSum, overPay;
  ck_assert_int_eq(
      s21_annCredit(2000000, -1, 15, &monthlyPayment, &totalSum, &overPay),
      ERROR);
  ck_assert_int_eq(
      s21_annCredit(2000000, 12, -1, &monthlyPayment, &totalSum, &overPay),
      ERROR);
  ck_assert_int_eq(
      s21_annCredit(2000000, -1, -1, &monthlyPayment, &totalSum, &overPay),
      ERROR);
}
END_TEST

Suite* suite_calc(void) {
  Suite* suite = suite_create("s21_calc");
  TCase* testcase = tcase_create("case_calc");
  tcase_add_test(testcase, calc_1);
  tcase_add_test(testcase, calc_2);
  tcase_add_test(testcase, calc_3);
  tcase_add_test(testcase, calc_4);
  tcase_add_test(testcase, calc_5);
  tcase_add_test(testcase, calc_6);
  tcase_add_test(testcase, calc_7);
  tcase_add_test(testcase, calc_8);
  tcase_add_test(testcase, calc_9);
  tcase_add_test(testcase, calc_10);
  tcase_add_test(testcase, calc_11);
  tcase_add_test(testcase, calc_12);
  tcase_add_test(testcase, calc_13);
  tcase_add_test(testcase, calc_14);
  tcase_add_test(testcase, credit_calc_1);
  tcase_add_test(testcase, credit_calc_2);
  suite_add_tcase(suite, testcase);
  return suite;
}

int main(void) {
  SRunner* runner = srunner_create(suite_calc());
  srunner_set_fork_status(runner, CK_NOFORK);
  srunner_run_all(runner, CK_NORMAL);
  srunner_free(runner);
}
