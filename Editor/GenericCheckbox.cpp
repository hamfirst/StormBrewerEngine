
#include <QTimer>

#include "GenericCheckbox.h"

GenericCheckbox::GenericCheckbox(QWidget * parent) :
  QCheckBox(parent),
  m_IgnoreUpdate(false)
{
  setTristate(false);
  connect(this, &GenericCheckbox::stateChanged, this, &GenericCheckbox::handleCheckChanged);
}

void GenericCheckbox::handleCheckChanged(int state)
{
  if (m_IgnoreUpdate)
  {
    return;
  }

  if (checkState() == Qt::PartiallyChecked)
  {
    return;
  }

  m_UpdateCallback();
}

void GenericCheckbox::RemoteUpdate(bool val)
{
  m_IgnoreUpdate = true;
  setCheckState(val ? Qt::Checked : Qt::Unchecked);
  m_IgnoreUpdate = false;
}

void GenericCheckbox::SetUpdateCallback(Delegate<void> && callback)
{
  m_UpdateCallback = std::move(callback);
}

bool GenericCheckbox::GetChecked()
{
  return checkState() == Qt::Checked;
}
