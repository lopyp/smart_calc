#ifndef SRC_CALC_H_
#define SRC_CALC_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct/data.h"

#define MAXSIZE 255

int main_calc(char *str, char *res_string, double x);
int is_type(char ch);
int is_correct_str(char *str, char *new_str);
int change_op(char *str, char *new_str, int pos, int new_pos);
int del_space(char *str, char **new_str);
int polish_notation(char *str, list_t **notationr);
int calculate(list_t *val, double *result, double x);
int operate_b(double val_1, double val_2, char op, double *res);
int operate_o(double val_1, char op, double *res);
int priority(char val);
void notation_op(list_t **notation, char *char_tmp, char prev, char *str);
int notation_bracket(list_t **notation, char *char_tmp);

#endif  // SRC_CALC_H_
