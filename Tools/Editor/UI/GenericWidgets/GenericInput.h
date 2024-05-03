#pragma once


#include <chrono>

#include <QLineEdit>

#include "Shared/Foundation/Common.h"
#include "Shared/Foundation/Delegate/Delegate.h"

class GenericInput : public QLineEdit
{
  Q_OBJECT;
public:

  GenericInput(QWidget * parent = nullptr);

  void timerExpired();

  void RemoteUpdate(czstr text);
  void SetUpdateCallback(Delegate<void> && callback);

  std::string GetText();

public slots:

  void handleTextChanged(const QString &text);

protected:
  virtual bool event(QEvent * ev) override;
  virtual void contextMenuEvent(QContextMenuEvent * ev) override;

private:

  bool m_PendingUpdate;
  bool m_IgnoreUpdate;

  Delegate<void> m_UpdateCallback;

  std::chrono::system_clock::time_point m_LastUpdate;
};

