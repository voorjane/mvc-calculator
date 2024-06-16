/*!
 * \mainpage Программа на QT, расширенная версия калькулятора, выполненная на
 * языке C
 */

/*!
 \file
 \brief Заголовочный файл, в котором описаны все функции, связанные с
 вычислением математического выражения в инфиксной форме
*/

#ifndef SRC_S21_CALC_H_
#define SRC_S21_CALC_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// Максимальная длина выражения
#define MAX_SIZE 255
/// Количество операторов
#define OPCOUNT 7
/// Количество функций
#define FUNCOUNT 12

/// Код результата сравнения
enum check { FALSE, TRUE };
/// Код результата вычисления
enum calc_results { OK, UNMATCHED_PARENTHESES, CALC_ERR };

/// Структура, которая описывает стек для хранения чисел и операторов
typedef struct {
  /// стек операторов
  char op_stack[MAX_SIZE];
  /// стек чисел
  double db_stack[MAX_SIZE];
  /// индекс оператора на вершине стека
  int op_top;
  /// индекс числа на вершине стека
  int db_top;
} Stack;

/*!
 * @brief Инициализирует стек
 * @param s - стек
 */
void init(Stack* s);

/*!
 * @brief Добавляет оператор типа char в стек
 * @param s - стек
 * @param c - оператор
 */
void push(Stack* s, char c);

/*!
 * @brief Добавляет число типа double в стек
 * @param s - стек
 * @param value - число
 */
void push_value(Stack* s, double value);

/*!
 * @brief Показывает оператор на вершине стека, не удаляя его
 * @param s - стек
 * @return оператор
 */
char peek(Stack* s);

/*!
 * @brief Вытаскивает оператор с вершины стека операторов
 * @param s - стек
 * @param op - указатель на оператор
 * @return код ошибки (0 - Ок, 1 - Ошибка вычисления)
 */
int pop(Stack* s, char* op);

/*!
 * @brief Вытаскивает число с вершины стека чисел
 * @param s - стек
 * @param val - указатель на число
 * @return код ошибки (0 - Ок, 1 - Ошибка вычисления)
 */
int pop_value(Stack* s, double* val);

// CALCULATE FUNCTIONS

/*!
 * @brief Производит вычисление выражения в инфиксной форме
 * @param expression - выражение в инфиксной форме
 * @param result - результат вычисления
 * @param x - дополнительная переменная, необходима, если в выражении
 * присутствует x
 * @return код ошибки (0 - Ок, 1 - Несбалансированные скобки, 2 - Ошибка
 * вычисления)
 */
int s21_calculate(char* expression, double* result, double x);

/*!
 * @brief Производит операцию, результат вычисления помещает в стек
 * @param stack - стек
 * @param op - оператор
 * @return код ошибки (0 - Ок, 1 - Несбалансированные скобки, 2 - Ошибка
 * вычисления)
 */
int performOperation(Stack* stack, char op);

// SUPPORT FUNCTIONS

/*!
 * @brief Проверяет приоритет функции или оператора
 * @param c - символ (оператор или функция)
 * @return приоритет функции или оператора
 */
int precedence(char c);

/*!
 * @brief Проверяет, является ли символ оператором
 * @param c - символ
 * @return код (0 - False, 1 - True)
 */
int is_operator(char c);

/*!
 * @brief Проверяет, является ли символ числом или точкой
 * @param currentChar - символ
 * @return код (0 - False, 1 - True)
 */
int is_num(char currentChar);

/*!
 * @brief Проверяет, является ли символ пробелом
 * @param currentChar - символ
 * @return код (0 - False, 1 - True)
 */
int is_space(char currentChar);

/*!
 * @brief Проверка, является ли символ функцией
 * @param c - символ
 * @return код (0 - False, 1 - True)
 */
int is_function(char c);

/*!
 * @brief Проверка числа для арк-функций
 * @param value - число
 * @return код (0 - False, 1 - True)
 */
int arc_check(double value);

/*!
 * @brief Проверка числа для функции логарифма
 * @param value - число
 * @return код (0 - False, 1 - True)
 */
int log_check(double value);

/*!
 * @brief Подготовка выражения для функции вычисления
 * @param expression - выражение
 * @return код ошибки (0 - Ок, 2 - Ошибка вычисления)
 */
int expressionPreparation(char* expression);

/*!
 * @brief Заменяет все вхождения подстроки на символ
 * @param string - строка
 * @param substring - подстрока
 * @param replacement - символ, на который заменяется подстрока
 */
void strReplace(char* string, char* substring, char replacement);

#endif  // SRC_S21_CALC_H_
