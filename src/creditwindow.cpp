#include "creditwindow.h"

#include "ui_creditwindow.h"

CreditWindow::CreditWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::CreditWindow) {
  ui->setupUi(this);
  setFixedSize(400, 200);
  ui->annuitent->setChecked(true);
}

CreditWindow::~CreditWindow() { delete ui; }

void CreditWindow::on_calcDebt_clicked() {
  ui->monthlyPay->setReadOnly(false);
  ui->totalDebt->setReadOnly(false);
  ui->debtPercents->setReadOnly(false);
  bool ok1, ok2, ok3;
  double C, M, S, monthlyPayment, totalSum, overPay, monthlyPstart, monthlyPend;
  S = ui->timeCredit->text().toInt(&ok1);
  C = ui->sumOfCredit->text().toDouble(&ok2);
  M = ui->percent->text().toDouble(&ok3);
  if (ok1 && ok2 && ok3) {
    setFixedSize(400, 300);
    if (ui->monthYear->currentText() == "Лет") S *= 12;
    int err, diffFlag = 0;
    if (ui->annuitent->isChecked())
      err = s21_annCredit(C, S, M, &monthlyPayment, &totalSum, &overPay);
    else {
      err = s21_diffCredit(C, S, M, &monthlyPstart, &monthlyPend, &totalSum,
                           &overPay);
      diffFlag = 1;
    }
    if (!err) {
      if (diffFlag) {
        ui->monthlyPay->setText(QString::number(monthlyPstart, 'g', 8));
        ui->monthlyPay->setText(ui->monthlyPay->text() + "...");
        ui->monthlyPay->setText(ui->monthlyPay->text() +
                                QString::number(monthlyPend, 'g', 8));
      } else
        ui->monthlyPay->setText(QString::number(monthlyPayment, 'g', 8));
      ui->totalDebt->setText(QString::number(totalSum, 'g', 8));
      ui->debtPercents->setText(QString::number(overPay, 'g', 8));
      ui->monthlyPay->setReadOnly(true);
      ui->totalDebt->setReadOnly(true);
      ui->debtPercents->setReadOnly(true);
    } else
      QMessageBox::critical(this, "Error", "Введены некорректные данные");
  } else
    QMessageBox::critical(this, "Error", "Введены некорректные данные");
}
