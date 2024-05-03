#pragma once


#include <chrono>

#include <QCheckBox>

#include "Shared/Foundation/Common.h"
#include "Shared/Foundation/Delegate/Delegate.h"

class GenericCheckbox : public QCheckBox
{
  Q_OBJECT;
public:

  GenericCheckbox(QWidget * parent = nullptr);

  void RemoteUpdate(bool val);
  void SetUpdateCallback(Delegate<void> && callback);

  bool GetChecked();

public slots:

  void handleCheckChanged(int state);

private:

  bool m_IgnoreUpdate;

  Delegate<void> m_UpdateCallback;
};

