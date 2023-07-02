#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "s21_calc.h"

int main_calc(char *str, char *res_string, double x) {
  int error = 0;
  double result;
  char *correct_str = calloc(MAXSIZE + 1, sizeof(char));
  list_t *notation = init('\0');

  if (!(error = is_correct_str(str, correct_str))) {
    error = polish_notation(correct_str, &notation);
  }
  if (!error) {
    error = calculate(notation, &result, x);
  }
  if (!error) {
    sprintf(res_string, "%.7lf", result);
  } else if (error == 404) {
    strcat(res_string, "NAN");
  } else if (error == 405) {
    strcat(res_string, "INF");
  } else {
    strcat(res_string, "ERROR");
  }
  double tmp;
  char ch;
  while (notation != NULL && error == 1) {
    if (notation->type == 1)
      popDouble(&notation, &tmp);
    else
      popChar(&notation, &ch);
  }
  free(correct_str);
  return error;
}

int is_correct_str(char *str, char *new_str) {
  int error = 0;
  int type = 1;
  int j = 0;
  if (strchr("*^/m)", *str)) {
    error = 1;
  } else {
    for (int i = 0; str[i] != '\0' && !error; i++) {
      type = is_type(str[i]);
      if (type == 0) {
        if (str[i] == '.' &&
            ((is_type(str[i + 1]) == 1 && i == 0) ||
             (is_type(str[i - 1]) == 1 || is_type(str[i + 1]) == 1))) {
          new_str[j] = '.';
          j++;
          continue;
        }
        error = 1;
      } else if (str[i] == 'm') {
        if (strncmp(str + i, "mod", 3) == 0) {
          new_str[j] = 'm';
          if (strchr("-+*^/m", str[i - 1])) {
            error = 1;
          }
          j++;
          i = i + 2;
        }
      } else if (type == 1 || type == 2 || type == 3 || type == 6) {
        if ((is_type(str[i]) == 3) && (is_type(str[i - 1]) == 3) && i != 0) {
          error = 1;
        }
        if ((is_type(str[i]) == 2) &&
            ((is_type(str[i + 1]) == 1) ||
             ((is_type(str[i - 1]) == 1) && i != 0))) {
          error = 1;
        }
        new_str[j] = str[i];
        j++;
      } else if (type == 4) {
        i = change_op(str, new_str, i, j);
        j++;
      } else if (type == 5) {
      }
      if (i > 244) {
        error = 1;
      }
    }
    if (is_type(new_str[j - 1]) == 3) error = 1;
  }
  return error;
}

int change_op(char *str, char *new_str, int pos, int new_pos) {
  str = str + pos;
  pos += 2;
  if (strncmp(str, "cos(", 4) == 0) {
    new_str[new_pos] = 'c';
  } else if (strncmp(str, "sin(", 4) == 0) {
    new_str[new_pos] = 's';
  } else if (strncmp(str, "tan(", 4) == 0) {
    new_str[new_pos] = 't';
  } else if (strncmp(str, "log(", 4) == 0) {
    new_str[new_pos] = 'l';
  } else if (strncmp(str, "asin(", 5) == 0) {
    new_str[new_pos] = 'S';
    pos++;
  } else if (strncmp(str, "acos(", 5) == 0) {
    new_str[new_pos] = 'C';
    pos++;
  } else if (strncmp(str, "atan(", 5) == 0) {
    new_str[new_pos] = 'T';
    pos++;
  } else if (strncmp(str, "sqrt(", 5) == 0) {
    new_str[new_pos] = 'r';
    pos++;
  } else if (strncmp(str, "ln(", 3) == 0) {
    new_str[new_pos] = 'L';
    pos--;
  } else {
    pos -= 2;
  }
  return pos;
}

int is_type(char c) {
  int type = 0;
  if (c > 47 && c < 58) {
    type = 1;
  } else if (c == 'x' || c == 'X') {
    type = 2;
  } else if (strchr("+^-*/m", c)) {
    type = 3;
  } else if (strchr("cCsStTlLra", c)) {
    type = 4;
  } else if (c == ' ') {
    type = 5;
  } else if (c == '(' || c == ')') {
    type = 6;
  }
  return type;
}
