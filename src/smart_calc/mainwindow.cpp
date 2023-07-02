#include "mainwindow.h"

#include <cstring>
#include <iterator>

#include "./ui_mainwindow.h"
#include "credit.h"
#include "qcustomplot.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "../s21_calc.h"
#ifdef __cplusplus
}
#endif

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_ac_clicked() { ui->lineEdit->setText(""); }

void MainWindow::on_pushButton_c_clicked() { ui->lineEdit->backspace(); }

void MainWindow::on_pushButton_exit_clicked() { MainWindow::close(); }

void MainWindow::on_pushButton_1_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "1");
}

void MainWindow::on_pushButton_2_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "2");
}

void MainWindow::on_pushButton_3_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "3");
}

void MainWindow::on_pushButton_4_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "4");
}

void MainWindow::on_pushButton_5_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "5");
}

void MainWindow::on_pushButton_6_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "6");
}

void MainWindow::on_pushButton_7_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "7");
}

void MainWindow::on_pushButton_8_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "8");
}

void MainWindow::on_pushButton_9_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "9");
}

void MainWindow::on_pushButton_0_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "0");
}

void MainWindow::on_pushButton_x_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "x");
}

void MainWindow::on_pushButton_dot_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + ".");
}

void MainWindow::on_pushButton_sum_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "+");
}

void MainWindow::on_pushButton_sub_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "-");
}

void MainWindow::on_pushButton_mul_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "*");
}

void MainWindow::on_pushButton_div_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "/");
}

void MainWindow::on_pushButton_mod_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "mod");
}

void MainWindow::on_pushButton_exp_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "^");
}

void MainWindow::on_pushButton_sin_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "sin(");
}

void MainWindow::on_pushButton_cos_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "cos(");
}

void MainWindow::on_pushButton_tan_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "tan(");
}

void MainWindow::on_pushButton_asin_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "asin(");
}

void MainWindow::on_pushButton_acos_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "acos(");
}

void MainWindow::on_pushButton_atan_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "atan(");
}

void MainWindow::on_pushButton_log_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "log(");
}

void MainWindow::on_pushButton_ln_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "ln(");
}

void MainWindow::on_pushButton_sqrt_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "sqrt(");
}

void MainWindow::on_pushButton_brec_op_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "(");
}

void MainWindow::on_pushButton_brec_close_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + ")");
}

void MainWindow::on_pushButton_credit_clicked() {
  credit window;
  window.setModal(true);
  window.exec();
}

void MainWindow::on_pushButton_res_clicked() {
  bool ok = 0;
  char str[1024] = "\0";
  QByteArray str_input = ui->lineEdit->text().toLatin1();
  memcpy(str, str_input, ui->lineEdit->text().length() + 1);
  char res_string[1024] = "\0";
  double x = ui->x_val->text().toDouble(&ok);
  if (ok) {
    main_calc(str, res_string, x);
    QString new_line;
    new_line = QString::fromLocal8Bit(res_string);
    ui->lineEdit->setText(new_line);
  } else {
    ui->lineEdit->setText("ERROR");
  }
}

void MainWindow::on_pushButton_plot_clicked() {
  bool ok = 0;
  int min_y, max_x, min_x, max_y;
  max_x = ui->max_x->text().toInt(&ok);
  if (ok) max_y = ui->max_y->text().toInt(&ok);
  if (ok) min_x = ui->min_x->text().toInt(&ok);
  if (ok) min_y = ui->min_y->text().toInt(&ok);
  if (ok) {
    int range_x = max_x - min_x;
    char str[1024] = "";
    char *res_string = (char *)calloc(20, sizeof(char));
    QByteArray str_input = ui->lineEdit->text().toLatin1();
    memcpy(str, str_input, ui->lineEdit->text().length() + 1);
    int var = 0;
    int error;
    double result;
    QVector<double> x(1024), y(1024);
    for (int i = 0; i < 1024; ++i) {
      memset(res_string, '\0', 20);
      x[i] = min_x + range_x * (i / 1024.); 
      main_calc(str, res_string, x[i]);
      if (!strcmp(res_string, "INF"))
        y[i] = INFINITY;
      else if (!strcmp(res_string, "NAN"))
        y[i] = NAN;
      else if (strcmp(res_string, "ERROR"))
        y[i] = strtod(res_string, NULL);
    }
    ui->customPlot->addGraph();
    QPen bluePen;
    bluePen.setColor(QColor(30, 40, 255, 150));
    bluePen.setStyle(Qt::SolidLine);
    bluePen.setWidthF(5);
    ui->customPlot->graph(0)->setPen(bluePen);
    ui->customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->setRange(min_x, max_x);
    ui->customPlot->yAxis->setRange(min_y, max_y);
    ui->customPlot->replot();
    free(res_string);
  }
}
