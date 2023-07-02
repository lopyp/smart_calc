#include "s21_credit.h"

void credit_calc(long double loan, long double term, long double interest_rate,
                 int type, long double *payments, long double *total_interest,
                 long double *total, long double *max, long double *min) {
  long double rate_per_mouth = interest_rate / 1200;
  if (type == 1) {
    long double A = rate_per_mouth * pow((1. + rate_per_mouth), term) /
                    (pow((1. + rate_per_mouth), term) - 1.);
    *payments = A * loan;
    *total = *payments * term;
    *total_interest = *total - loan;
  } else {
    long double month = loan / term;
    *max = month + loan * interest_rate * 30.42 / 36524.25;
    *min = month + month * interest_rate * 30.42 / 36524.25;
    *payments = (*max + *min) / 2.;
    *total = *payments * term;
    *total_interest = *total - loan;
  }
}
