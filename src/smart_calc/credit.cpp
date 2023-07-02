#include "credit.h"

#include "./ui_credit.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "../credit_calc/s21_credit.h"
#ifdef __cplusplus
}
#endif

credit::credit(QWidget *parent) : QDialog(parent), ui(new Ui::credit) {
  ui->setupUi(this);
  this->setFixedSize(470,620);
}

credit::~credit() { delete ui; }

void credit::on_pushButton_2_clicked() { credit::close(); }

void credit::on_pushButton_1_clicked() {
  int type = 1;
  if (ui->radioButton_diff->isChecked()) type = 2;
  char str[1024] = "";
  long double loan = ui->loan->text().toDouble();
  long double rate = ui->rate->text().toDouble();
  long double term = ui->term->text().toInt();
  if (loan > 0 && rate > 0 && term > 0) {
    long double payment = 0;
    long double max = 0;
    long double min = 0;
    long double interest = 0;
    long double total = 0;
    credit_calc(loan, term, rate, type, &payment, &interest, &total, &max,
                &min);
    QString payment_line, max_line, min_line, interest_line, total_line;
    payment_line = QString::number(payment, 'g', 9);
    ui->payment->setText(payment_line);
    if (type == 2) {
      max_line = QString::number(max, 'g', 9);
      ui->payment_2->setText(max_line);
      min_line = QString::number(min, 'g', 9);
      ui->payment_3->setText(min_line);
    } else {
      ui->payment_2->setText("");
      ui->payment_3->setText("");
    }
    interest_line = QString::number(interest, 'g', 9);
    ui->interest->setText(interest_line);
    total_line = QString::number(total, 'g', 9);
    ui->total->setText(total_line);
  }
}
