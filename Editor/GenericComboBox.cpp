
#include <QTimer>
#include <QEvent>
#include <QKeyEvent>
#include <QContextMenuEvent>

#include "GenericComboBox.h"

extern Delegate<void> g_GlobalUndo;
extern Delegate<void> g_GlobalRedo;

GenericComboBox::GenericComboBox(QWidget * parent) :
        QComboBox(parent),
        m_IgnoreUpdate(false)
{
  connect(this, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &GenericComboBox::handleCurrentIndexChanged);
}

void GenericComboBox::RemoteUpdate(int index)
{
  m_IgnoreUpdate = true;
  setCurrentIndex(index);
  m_IgnoreUpdate = false;
}

void GenericComboBox::SetUpdateCallback(Delegate<void> && callback)
{
  m_UpdateCallback = std::move(callback);
}

void GenericComboBox::SetItemCallback(Delegate<const std::vector<std::string> &> && callback)
{
  m_ItemCallback = std::move(callback);
}

void GenericComboBox::handleCurrentIndexChanged(int index)
{
  if(m_IgnoreUpdate)
  {
    return;
  }

  m_UpdateCallback();
}

void GenericComboBox::UpdateItems(int current_index)
{
  m_IgnoreUpdate = true;

  auto & items = m_ItemCallback();
  for(int index = 0; index < static_cast<int>(items.size()); ++index)
  {
    if(index >= count())
    {
      addItem(QString(items[index].c_str()));
    }
    else
    {
      setItemText(index, QString(items[index].c_str()));
    }
  }

  while(count() > items.size())
  {
    removeItem(count() - 1);
  }

  if(currentIndex() != current_index)
  {
    setCurrentIndex(current_index);
  }

  m_IgnoreUpdate = false;
}
