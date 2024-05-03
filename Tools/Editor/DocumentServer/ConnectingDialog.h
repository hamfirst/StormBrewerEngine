#pragma once

#include <QDialog>

#include "ui_ConnectingDialog.h"

class ConnectingDialog : public QDialog
{
  Q_OBJECT

public:
  explicit ConnectingDialog(QWidget *parent = Q_NULLPTR);

private:

  Ui::ConnectingDialogClass ui;
};

