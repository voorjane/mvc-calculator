#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setFixedSize(340, 400);

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(dot()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_ac, SIGNAL(clicked()), this, SLOT(clear()));
  connect(ui->pushButton_par_left, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_par_right, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_func, SIGNAL(clicked()), this, SLOT(funcShow()));
  connect(ui->pushButton_eq, SIGNAL(clicked()), this, SLOT(calculate()));
  ui->pushButton_dot->setCheckable(true);
  ui->pushButton_func->setCheckable(true);
  ui->pushButton_cos->hide();
  ui->pushButton_sin->hide();
  ui->pushButton_tan->hide();
  ui->pushButton_acos->hide();
  ui->pushButton_asin->hide();
  ui->pushButton_atan->hide();
  ui->pushButton_mod->hide();
  ui->pushButton_sqrt->hide();
  ui->pushButton_log->hide();
  ui->pushButton_ln->hide();
}

MainWindow::~MainWindow() {
  delete ui;
  delete graph;
  delete credit;
}

void MainWindow::digits() {
  if (ui->expression->text() == "Error") ui->expression->setText("");
  QPushButton *button = (QPushButton *)sender();
  ui->expression->setText(ui->expression->text() + button->text());
}

void MainWindow::clear() {
  ui->expression->setText("");
  ui->pushButton_dot->setChecked(false);
  ui->pushButton_par_left->setChecked(false);
}

void MainWindow::dot() {
  if (ui->pushButton_dot->isChecked())
    ui->expression->setText(ui->expression->text() + ".");
}

void MainWindow::operations() {
  if (ui->expression->text() == "Error") ui->expression->setText("");
  QPushButton *button = (QPushButton *)sender();
  ui->expression->setText(ui->expression->text() + button->text());
  ui->pushButton_dot->setChecked(false);
}

void MainWindow::funcShow() {
  if (ui->pushButton_func->isChecked()) {
    setFixedSize(530, 400);
    ui->pushButton_cos->show();
    ui->pushButton_sin->show();
    ui->pushButton_tan->show();
    ui->pushButton_acos->show();
    ui->pushButton_asin->show();
    ui->pushButton_atan->show();
    ui->pushButton_mod->show();
    ui->pushButton_sqrt->show();
    ui->pushButton_log->show();
    ui->pushButton_ln->show();
  } else {
    setFixedSize(340, 400);
    ui->pushButton_cos->hide();
    ui->pushButton_sin->hide();
    ui->pushButton_tan->hide();
    ui->pushButton_acos->hide();
    ui->pushButton_asin->hide();
    ui->pushButton_atan->hide();
    ui->pushButton_mod->hide();
    ui->pushButton_sqrt->hide();
    ui->pushButton_log->hide();
    ui->pushButton_ln->hide();
  }
}

void MainWindow::functions() {
  if (ui->expression->text() == "Error") ui->expression->setText("");
  QPushButton *button = (QPushButton *)sender();
  ui->expression->setText(ui->expression->text() + button->text() + "(");
  ui->pushButton_par_left->setChecked(true);
}

void MainWindow::calculate() {
  int err = OK;
  if (ui->expression->text() == "")
    QMessageBox::critical(this, "Error", "Empty expression");
  else {
    bool ok;
    double result = 0, x = ui->str_x->text().toDouble(&ok);
    if (!ok && ui->expression->text().indexOf("x") != -1) err = CALC_ERR;
    if (err == OK)
      err = s21_calculate(ui->expression->text().toLocal8Bit().data(), &result,
                          x);
    if (err == OK)
      ui->expression->setText(QString::number(result, 'g', 11));
    else if (err == UNMATCHED_PARENTHESES) {
      QMessageBox::warning(this, "Error", "Unmatched parentheses");
      ui->expression->setText("Error");
    } else if (err == CALC_ERR) {
      QMessageBox::warning(this, "Error", "Calculation Error");
      ui->expression->setText("Error");
    }
  }
}

void MainWindow::on_graph_triggered() {
  graph = new GraphWindow(this);
  graph->setModal(true);
  graph->exec();
}

void MainWindow::on_creditCalc_triggered() {
  credit = new CreditWindow(this);
  credit->setModal(true);
  credit->exec();
}

void MainWindow::on_creditButton_clicked() {
  credit = new CreditWindow(this);
  credit->setModal(true);
  credit->exec();
}

void MainWindow::on_graphButton_clicked() {
  graph = new GraphWindow(this);
  graph->setModal(true);
  graph->exec();
}
