#pragma once

#include <QPushButton>

#include "GenericFrame.h"

#include <Foundation/Common.h>
#include <Foundation/Delegate/Delegate.h>

class GenericListFrame : public GenericFrame
{
  Q_OBJECT;
public:

  GenericListFrame(czstr title, bool show_add_button, bool show_remove_button, QWidget * parent = nullptr);

  void SetAddDelegate(Delegate<void> && callback);
  void SetRemoveDelegate(Delegate<void> && callback);

  void SetAddButtonEnabled(bool enable);
  void SetRemoveButtonEnabled(bool enable);

  void RepositionElements();

  template <typename T>
  T * CreateWidget();

protected:

  void resizeEvent(QResizeEvent * ev) override;

public slots:

  void handleAddButtonClick();
  void handleRemoveButtonClick();

private:

  Delegate<void> m_AddDelegate;
  std::unique_ptr<QPushButton> m_AddButton;

  Delegate<void> m_RemoveDelegate;
  std::unique_ptr<QPushButton> m_RemoveButton;
};