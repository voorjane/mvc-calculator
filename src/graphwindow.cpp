#include "graphwindow.h"

#include "ui_graphwindow.h"

GraphWindow::GraphWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::GraphWindow) {
  ui->setupUi(this);
}

GraphWindow::~GraphWindow() { delete ui; }

void GraphWindow::on_button_clicked() {
  QVector<double> x, y;
  double x_start = 0, x_end = 0, y_start = 0, y_end = 0, x_cur = 0, step = 0.1;
  x_start = ui->x_begin->text().toDouble();
  x_end = ui->x_end->text().toDouble() + step;
  y_start = ui->y_begin->text().toDouble();
  y_end = ui->y_end->text().toDouble();

  ui->widget->xAxis->setRange(x_start, x_end);
  ui->widget->yAxis->setRange(y_start, y_end);
  for (x_cur = x_start; x_cur <= x_end; x_cur += step) {
    x.push_back(x_cur);
    double result = 0;
    int err = s21_calculate(ui->expression->text().toLocal8Bit().data(),
                            &result, x_cur);
    if (err) {
      x.pop_back();
      continue;
    }
    y.push_back(result);
  }
  if (x.empty()) QMessageBox::critical(this, "Error", "Ошибка вычисления");
  ui->widget->clearGraphs();
  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();
}
