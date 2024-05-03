#pragma once


#include <chrono>

#include <QComboBox>

#include "Shared/Foundation/Common.h"
#include "Shared/Foundation/Delegate/Delegate.h"

class GenericComboBox : public QComboBox
{
Q_OBJECT;
public:

  GenericComboBox(QWidget * parent = nullptr);

  void RemoteUpdate(int index);
  void SetUpdateCallback(Delegate<void> && callback);
  void SetItemCallback(Delegate<const std::vector<std::string> &> && callback);
  void UpdateItems(int current_index);

public slots:

  void handleCurrentIndexChanged(int index);

private:

  bool m_IgnoreUpdate;

  Delegate<void> m_UpdateCallback;
  Delegate<const std::vector<std::string> &> m_ItemCallback;
};

