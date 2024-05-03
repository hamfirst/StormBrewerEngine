#include "SelectFromListDialog.h"

SelectFromListDialog::SelectFromListDialog(const QStringList & items, QWidget *parent)
  : QDialog(parent)
{
  ui.setupUi(this);

  ui.listWidget->addItems(items);
  for (int index = 0; index < ui.listWidget->count(); ++index)
  {
    auto item = ui.listWidget->item(index);
    item->setData(Qt::UserRole, index);
  }

  ui.listWidget->sortItems();

  m_AllowEvents = true;
  m_SelectedIndex = -1;

  connect(ui.lineEdit, &QLineEdit::textChanged, this, &SelectFromListDialog::textChanged);
  connect(ui.listWidget, &QListWidget::itemSelectionChanged, this, &SelectFromListDialog::selectedItemChanged);

  ui.lineEdit->setFocus();
}

void SelectFromListDialog::textChanged()
{
  if (m_AllowEvents == false)
  {
    return;
  }

  if (ui.lineEdit->text().length() == 0)
  {
    return;
  }

  m_AllowEvents = false;

  QListWidgetItem * best_item = nullptr;
  for (int index = 0; index < ui.listWidget->count(); ++index)
  {
    auto item = ui.listWidget->item(index);

    if (item->text().startsWith(ui.lineEdit->text(), Qt::CaseInsensitive))
    {
      best_item = item;
      break;
    }
  }

  if (best_item != nullptr)
  {
    best_item->setSelected(true);
    m_SelectedIndex = best_item->data(Qt::UserRole).toInt();
  }

  m_AllowEvents = true;
}

void SelectFromListDialog::selectedItemChanged()
{
  if (m_AllowEvents == false)
  {
    return;
  }

  m_AllowEvents = false;

  auto selected_items = ui.listWidget->selectedItems();
  if (selected_items.count() > 0)
  {
    ui.lineEdit->setText(selected_items[0]->text());
    m_SelectedIndex = selected_items[0]->data(Qt::UserRole).toInt();
  }

  m_AllowEvents = true;
}

int SelectFromListDialog::GetSelectedIndex()
{
  return m_SelectedIndex;
}
