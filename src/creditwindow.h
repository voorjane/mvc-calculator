#ifndef CREDITWINDOW_H
#define CREDITWINDOW_H

#include <QDialog>
#include <QMessageBox>

extern "C" {
#include "s21_credit.h"
}

namespace Ui {
class CreditWindow;
}

class CreditWindow : public QDialog {
  Q_OBJECT

 public:
  explicit CreditWindow(QWidget *parent = nullptr);
  ~CreditWindow();

 private slots:
  void on_calcDebt_clicked();

 private:
  Ui::CreditWindow *ui;
};

#endif  // CREDITWINDOW_H
