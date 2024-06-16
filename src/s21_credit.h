/*!
  \file
  \brief Заголовочный файл, в котором описаны функции для кредитного
  калькулятора
 */

#ifndef SRC_S21_CREDIT_H_
#define SRC_S21_CREDIT_H_

#include <math.h>
#include <stdio.h>
#include <time.h>

/// Коды для ошибок
enum errors { DONE, ERROR };

/*!
 * @brief Рассчет аннуитентного кредита
 * @param C - сумма кредита
 * @param S - срок кредита
 * @param M - процентная ставка
 * @param monthlyPayment - ежемесячный платеж
 * @param totalSum - долг + проценты
 * @param overPay - начисленные проценты
 * @return Возвращает код ошибки (0 - OK, 1 - Ошибка вычисления)
 */
int s21_annCredit(double C, double S, double M, double* monthlyPayment,
                  double* totalSum, double* overPay);

/*!
 * @brief Рассчет дифференцированного кредита
 * @param C - сумма кредита
 * @param S - срок кредита
 * @param P - процентная ставка
 * @param monthlyPstart - ежемесячный платеж (первый)
 * @param monthlyPend - ежемесячный платеж (последний)
 * @param totalSum - долг + проценты
 * @param overPay - начисленные проценты
 * @return Возвращает код ошибки (0 - OK, 1 - Ошибка вычисления)
 */
int s21_diffCredit(double C, double S, double P, double* monthlyPstart,
                   double* monthlyPend, double* totalSum, double* overPay);

/*!
 * @brief Проверяет, является ли год високосным
 * @param year - год
 * @return Возвращает код (0 - False, 1 - True)
 */
int isLeapYear(int year);

/*!
 * @brief Вычисляет количество дней в месяце
 * @param month - месяц
 * @param year - год
 * @return Возвращает количество дней в месяце
 */
double daysInMonth(int month, int year);

#endif  // SRC_S21_CREDIT_H_
