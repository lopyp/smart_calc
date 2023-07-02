#ifndef SRC_CREDIT_H_
#define SRC_CREDIT_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_calc.h"

#define MAXSIZE 255

void credit_calc(long double loan, long double term, long double interest_rate,
                 int type, long double *payments, long double *total_interest,
                 long double *total, long double *max, long double *min);

#endif  // SRC_CREDIT_H_
