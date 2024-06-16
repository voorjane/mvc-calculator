#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QDialog>
#include <QMessageBox>

extern "C" {
#include "s21_calc.h"
}

namespace Ui {
class GraphWindow;
}

class GraphWindow : public QDialog {
  Q_OBJECT

 public:
  explicit GraphWindow(QWidget *parent = nullptr);
  ~GraphWindow();

 private slots:
  void on_button_clicked();

 private:
  Ui::GraphWindow *ui;
};

#endif  // GRAPHWINDOW_H
