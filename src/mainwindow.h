#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QMainWindow>
#include <QMessageBox>

#include "creditwindow.h"
#include "graphwindow.h"
#include "qcustomplot.h"

extern "C" {
#include "s21_calc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  GraphWindow *graph;
  CreditWindow *credit;

 private slots:
  void digits();
  void clear();
  void dot();
  void operations();
  void funcShow();
  void functions();
  void calculate();
  void on_graph_triggered();
  void on_creditCalc_triggered();
  void on_creditButton_clicked();
  void on_graphButton_clicked();
};
#endif  // MAINWINDOW_H
