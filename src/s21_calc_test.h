/*!
  \file
  \brief Заголовочный файл, в котором описаны функции для тестов
 */

#ifndef SRC_S21_CALC_TEST_H
#define SRC_S21_CALC_TEST_H

#include "check.h"
#include "s21_calc.h"
#include "s21_credit.h"

/// Эпсилон
#define S21_EPS 1e-7

/*!
 * @brief Запускает тесты для функций калькулятора
 * @param suite - тест-кейсы
 */
void s21_calc_test(Suite *suite);

/*!
 * @brief Тесты для калькулятора
 * @result результат тестов
 */
Suite *suite_calc(void);

#endif  // SRC_S21_CALC_TEST_H
