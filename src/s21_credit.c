#include "s21_credit.h"

int s21_annCredit(double C, double S, double M, double* monthlyPayment,
                  double* totalSum, double* overPay) {
  if (S < 0 || M < 0) return ERROR;
  M = M / 12.0 / 100;
  double K = (M * pow(1 + M, S)) / (pow(1 + M, S) - 1);
  *monthlyPayment = round(C * K * 100) / 100;
  *totalSum = *monthlyPayment * S;
  *overPay = *totalSum - C;
  return DONE;
}

int s21_diffCredit(double C, double S, double P, double* monthlyPstart,
                   double* monthlyPend, double* totalSum, double* overPay) {
  if (P < 0.01 || S < 0) return ERROR;
  time_t currentTime = time(NULL);
  struct tm* time = localtime(&currentTime);
  int year = 1900 + time->tm_year, month = time->tm_mon, flag = 0;
  double mainDebt = C / S, creditBody = C, monthlyPay = 0;
  P /= 100;
  for (int i = 0; i < S; i++) {
    double debt = 0;
    if (month == 12) {
      year++;
      month = 0;
    }
    double daysInYear = isLeapYear(year) ? 366 : 365;
    double daysInM = daysInMonth(month, year);
    debt = (creditBody * P * daysInM) / daysInYear;
    monthlyPay = mainDebt + debt;
    if (!flag) {
      *monthlyPstart = monthlyPay;
      flag = 1;
    }
    *totalSum += monthlyPay;
    *overPay += debt;
    creditBody -= mainDebt;
    month++;
  }
  *monthlyPend = monthlyPay;
  return DONE;
}

int isLeapYear(int year) { return year % 400 == 0 || year % 4 == 0; }

double daysInMonth(int month, int year) {
  enum months { FEB = 1, APR = 3, JUN = 5, SEP = 8, NOV = 10 };
  double days = 31;
  switch (month) {
    case FEB:
      days = isLeapYear(year) ? 29 : 28;
      break;
    case APR:
    case JUN:
    case SEP:
    case NOV:
      days = 30;
      break;
    default:
      break;
  }
  return days;
}
