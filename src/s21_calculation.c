#include "s21_calc.h"

int polish_notation(char *str, list_t **notation) {
  int error = 0;
  char char_tmp = '\0';
  int type = 0;
  for (char prev = '('; *str != '\0';) {
    type = is_type(*str);
    if (type == 1 || *str == '.') {
      pushBackDouble(notation, strtod(str, &str));
      prev = *str;
    } else if (type == 2) {
      pushBackChar(notation, 'x');
      prev = *(str++);
    } else if (type == 3) {
      notation_op(notation, &char_tmp, prev, str);
      prev = *(str++);
    } else if (type == 4) {
      push(notation, *str);
      prev = *(str++);
    } else if (*str == '(') {
      push(notation, *str);
      prev = *(str++);
    } else if (*str == ')') {
      if (notation_bracket(notation, &char_tmp)) {
        error = 1;
      }
      prev = *(str++);
    }
  }
  popChar(notation, &char_tmp);
  while (char_tmp != '\0') {
    if (char_tmp == '(') {
      error = 1;
    }
    pushBackChar(notation, char_tmp);
    popChar(notation, &char_tmp);
  }
  return error;
}

int calculate(list_t *val, double *result, double x) {
  int error = 0;
  double res = 0;
  list_t *tmp = init('\0');
  double val_1;
  double val_2;
  char op = '\0';
  char x_tmp = '\0';
  op = '0';
  do {
    if (val->type == 1) {
      popDouble(&val, &val_1);
      pushDouble(&tmp, val_1);
    } else if (val->type == 2) {
      popChar(&val, &x_tmp);
      pushDouble(&tmp, x);
    } else if (val->type == 3) {
      popChar(&val, &op);
      if (strchr("+-*/^m", op)) {
        popDouble(&tmp, &val_2);
        popDouble(&tmp, &val_1);
        operate_b(val_1, val_2, op, &res);
      } else {
        popDouble(&tmp, &val_1);
        operate_o(val_1, op, &res);
      }
      pushDouble(&tmp, res);
    }
  } while (val != NULL);
  popDouble(&tmp, &res);
  popChar(&val, &op);
  popChar(&tmp, &op);
  if (isnan(res))
    error = 404;
  else if (isinf(res)) {
    error = 405;
  } else
    *result = res;
  return error;
}

int priority(char val_1) {
  int prior = 0;
  if (val_1 == '+' || val_1 == '-') {
    prior = 1;
  } else if (val_1 == '*' || val_1 == '/' || val_1 == 'm') {
    prior = 2;
  } else if (val_1 == '^') {
    prior = 3;
  } else if (val_1 == '(') {
    prior = 0;
  }
  return prior;
}

int operate_b(double val_1, double val_2, char op, double *res) {
  int error = 0;
  if (op == '+') {
    *res = val_1 + val_2;
  } else if (op == '-') {
    *res = val_1 - val_2;
  } else if (op == '*') {
    *res = val_1 * val_2;
  } else if (op == '/') {
    *res = val_1 / val_2;
  } else if (op == 'm') {
    *res = fmod(val_1, val_2);
  } else if (op == '^') {
    *res = pow(val_1, val_2);
  }
  return error;
}

int operate_o(double val_1, char op, double *res) {
  int error = 0;
  if (op == 'c') {
    *res = cos(val_1);
  } else if (op == 'C') {
    *res = acos(val_1);
  } else if (op == 's') {
    *res = sin(val_1);
  } else if (op == 'S') {
    *res = asin(val_1);
  } else if (op == 't') {
    *res = tan(val_1);
  } else if (op == 'T') {
    *res = atan(val_1);
  } else if (op == 'l') {
    *res = log10(val_1);
  } else if (op == 'L') {
    *res = log(val_1);
  } else if (op == 'r') {
    *res = sqrt(val_1);
  }
  return error;
}

void notation_op(list_t **notation, char *char_tmp, char prev, char *str) {
  if ((prev == '(') && (*str == '-' || *str == '+')) {
    pushBackDouble(notation, 0);
  }
  peek(*notation, char_tmp);
  while ((priority(*str) <= priority(*char_tmp)) && (*char_tmp != '\0')) {
    popChar(notation, char_tmp);
    pushBackChar(notation, *char_tmp);
    peek(*notation, char_tmp);
  }
  push(notation, *str);
}

int notation_bracket(list_t **notation, char *char_tmp) {
  int error = 0;
  peek(*notation, char_tmp);
  while (*char_tmp != '(' && *char_tmp != '\0') {
    popChar(notation, char_tmp);
    pushBackChar(notation, *char_tmp);
    peek(*notation, char_tmp);
  }
  if (*char_tmp == '\0')
    error = 1;
  else
    popChar(notation, char_tmp);
  peek(*notation, char_tmp);
  if (is_type(*char_tmp) == 4) {
    popChar(notation, char_tmp);
    pushBackChar(notation, *char_tmp);
  }
  return error;
}
