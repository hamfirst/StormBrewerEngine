#include "ConnectingDialog.h"

ConnectingDialog::ConnectingDialog(QWidget *parent)
  : QDialog(parent)
{
  ui.setupUi(this);
  setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
}
