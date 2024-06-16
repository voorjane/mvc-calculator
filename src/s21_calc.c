#include "s21_calc.h"

// STACK FUNCTIONS

void init(Stack *s) {
  s->op_top = -1;
  s->db_top = -1;
}

void push(Stack *s, char c) { s->op_stack[++(s->op_top)] = c; }

char peek(Stack *s) { return s->op_top != -1 ? s->op_stack[s->op_top] : 0; }

void push_value(Stack *s, double value) { s->db_stack[++(s->db_top)] = value; }

int pop(Stack *s, char *op) {
  if (s->op_top < 0) return CALC_ERR;
  *op = s->op_stack[(s->op_top)--];
  return OK;
}

int pop_value(Stack *s, double *val) {
  if (s->db_top < 0) return CALC_ERR;
  *val = s->db_stack[(s->db_top)--];
  return OK;
}

// CALCULATE FUNCTIONS

int performOperation(Stack *stack, char op) {
  double operand1 = 0, operand2 = 0;
  int flag = OK;
  if (is_function(op)) {
    pop_value(stack, &operand1);
    switch (op) {
      case '~':
        push_value(stack, -operand1);
        break;
      case '#':
        push_value(stack, operand1);
        break;
      case 's':
        push_value(stack, sin(operand1));
        break;
      case 'S':
        if (arc_check(operand1))
          flag = CALC_ERR;
        else
          push_value(stack, asin(operand1));
        break;
      case 'c':
        push_value(stack, cos(operand1));
        break;
      case 'C':
        if (arc_check(operand1))
          flag = CALC_ERR;
        else
          push_value(stack, acos(operand1));
        break;
      case 't':
        push_value(stack, tan(operand1));
        break;
      case 'T':
        push_value(stack, atan(operand1));
        break;
      case 'q':
        if (log_check(operand1))
          flag = CALC_ERR;
        else
          push_value(stack, sqrt(operand1));
        break;
      case 'l':
        if (log_check(operand1))
          flag = CALC_ERR;
        else
          push_value(stack, log(operand1));
        break;
      case 'L':
        if (log_check(operand1))
          flag = CALC_ERR;
        else
          push_value(stack, log10(operand1));
        break;
    }
  } else if (is_operator(op)) {
    pop_value(stack, &operand1);
    pop_value(stack, &operand2);
    switch (op) {
      case '+':
        push_value(stack, operand2 + operand1);
        break;
      case '-':
        push_value(stack, operand2 - operand1);
        break;
      case '*':
        push_value(stack, operand2 * operand1);
        break;
      case '/':
        if (operand1 == 0.0)
          flag = CALC_ERR;
        else
          push_value(stack, operand2 / operand1);
        break;
      case '^':
        if (operand2 < 0.0 && (fmod(operand1, 1) != 0))
          flag = CALC_ERR;
        else
          push_value(stack, pow(operand2, operand1));
        break;
      case 'm':
        push_value(stack, fmod(operand2, operand1));
        break;
    }
  } else
    flag = UNMATCHED_PARENTHESES;
  return flag;
}

int s21_calculate(char *expression, double *result, double x) {
  Stack stack;
  char op;
  init(&stack);
  if (expressionPreparation(expression) != OK) return CALC_ERR;
  for (size_t pos = 0; pos < strlen(expression); pos++) {
    char currentChar = expression[pos];
    if (is_space(currentChar)) {
      continue;
    } else if (is_num(currentChar)) {
      char *strvalue = (char *)malloc((MAX_SIZE + 1) * sizeof(char));
      if (strvalue) {
        int i = 0;
        while (is_num(currentChar)) {
          strvalue[i++] = currentChar;
          currentChar = expression[++pos];
        }
        strvalue[i + 1] = '\0';
        push_value(&stack, atof(strvalue));
        free(strvalue);
        currentChar = expression[--pos];
      }
    } else if (is_operator(currentChar) || is_function(currentChar)) {
      if (stack.op_top == -1)
        push(&stack, currentChar);
      else if ((precedence(currentChar) <= precedence(peek(&stack))) &&
               stack.op_top != -1) {
        while (precedence(currentChar) <= precedence(peek(&stack)) &&
               stack.op_top != -1) {
          if (pop(&stack, &op) == CALC_ERR) return CALC_ERR;
          performOperation(&stack, op);
        }
        push(&stack, currentChar);
      } else {
        push(&stack, currentChar);
      }
    } else if (currentChar == 'x') {
      push_value(&stack, x);
    } else if (currentChar == '(') {
      push(&stack, currentChar);
    } else if (currentChar == ')') {
      while (stack.op_top >= 0 && peek(&stack) != '(') {
        if (pop(&stack, &op) == CALC_ERR) return CALC_ERR;
        performOperation(&stack, op);
      }
      if (stack.op_top < 0 || peek(&stack) != '(') {
        return UNMATCHED_PARENTHESES;
      } else {
        if (pop(&stack, &op) == CALC_ERR) return CALC_ERR;
      }
    } else
      return CALC_ERR;
  }
  while (stack.op_top != -1) {
    if (pop(&stack, &op) == CALC_ERR) return CALC_ERR;
    int err = performOperation(&stack, op);
    if (err == CALC_ERR) return CALC_ERR;
    if (err == UNMATCHED_PARENTHESES) return UNMATCHED_PARENTHESES;
  }
  if (stack.db_top != 0) return CALC_ERR;
  pop_value(&stack, result);
  return OK;
}

// SUPPORT FUNCTIONS

int is_operator(char c) {
  const char operators[OPCOUNT] = "+-*/^m";
  for (int op = 0; op < OPCOUNT; op++) {
    if (c == operators[op]) return TRUE;
  }
  return FALSE;
}

int is_function(char c) {
  const char operators[FUNCOUNT] = "sScCtTqlL~#";
  for (int op = 0; op < FUNCOUNT; op++) {
    if (c == operators[op]) return TRUE;
  }
  return FALSE;
}

int precedence(char c) {
  int prec = 0;
  if (c == '~' || c == '#')
    prec = 5;
  else if (is_function(c))
    prec = 4;
  else if (c == '^' || c == 'm')
    prec = 3;
  else if (c == '*' || c == '/')
    prec = 2;
  else if (c == '+' || c == '-')
    prec = 1;
  return prec;
}

int is_num(char currentChar) {
  return currentChar == '.' ||
         (48 <= (int)(currentChar) && (int)(currentChar) <= 57);
}

int is_space(char currentChar) { return currentChar == ' '; }

void strReplace(char *string, char *substring, char replacement) {
  char *substring_source;
  while ((substring_source = strstr(string, substring))) {
    memmove(substring_source + 1, substring_source + strlen(substring),
            strlen(substring_source) - strlen(substring) + 1);
    memcpy(substring_source, &replacement, 1);
  }
}

int expressionPreparation(char *expression) {
  int flag = OK;
  if (expression[0] == '\0') flag = CALC_ERR;
  if (expression[0] == '-') expression[0] = '~';
  if (expression[0] == '+') expression[0] = '#';
  for (size_t i = 0; i < strlen(expression); i++) {
    if (expression[i] == '-' && expression[i - 1] == '(') expression[i] = '~';
    if (expression[i] == '+' && expression[i - 1] == '(') expression[i] = '#';
    if (is_operator(expression[i]) && is_operator(expression[i + 1]))
      flag = CALC_ERR;
    if (expression[i] == '(' && expression[i + 1] == ')') flag = CALC_ERR;
  }
  strReplace(expression, "mod", 'm');
  strReplace(expression, "acos", 'C');
  strReplace(expression, "atan", 'T');
  strReplace(expression, "asin", 'S');
  strReplace(expression, "cos", 'c');
  strReplace(expression, "sin", 's');
  strReplace(expression, "tan", 't');
  strReplace(expression, "sqrt", 'q');
  strReplace(expression, "ln", 'l');
  strReplace(expression, "log", 'L');
  return flag;
}

int arc_check(double value) { return value > 1 || value < -1; }

int log_check(double value) { return value < 0; }
