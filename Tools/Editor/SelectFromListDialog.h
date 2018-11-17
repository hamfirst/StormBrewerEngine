#pragma once

#include <QDialog>

#include <vector>
#include <string>

#include "ui_SelectFromListDialog.h"

class SelectFromListDialog : public QDialog
{
  Q_OBJECT
public:
  SelectFromListDialog(const QStringList & items, QWidget *parent = Q_NULLPTR);

public slots:

  void textChanged();
  void selectedItemChanged();

  int GetSelectedIndex();

private:

  Ui::SelectFromListDialogClass ui;

  bool m_AllowEvents;
  int m_SelectedIndex;
};


