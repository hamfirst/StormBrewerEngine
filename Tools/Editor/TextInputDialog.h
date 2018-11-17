#pragma once

#include <QDialog>

#include <vector>
#include <string>

#include "ui_TextInputDialog.h"

class TextInputDialog : public QDialog
{
  Q_OBJECT
public:
  TextInputDialog(const QString & prompt, QWidget *parent = Q_NULLPTR);

  QString GetValue();

private:

  Ui::TextInputDialogClass ui;
};


