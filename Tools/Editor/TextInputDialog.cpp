#include "TextInputDialog.h"

TextInputDialog::TextInputDialog(const QString & prompt, QWidget *parent)
  : QDialog(parent)
{
  ui.setupUi(this);
  ui.prompt->setText(prompt);
  ui.lineEdit->setFocus();

  connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
  connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

QString TextInputDialog::GetValue()
{
  return ui.lineEdit->text();
}
