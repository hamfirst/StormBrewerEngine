#pragma once

#include <QWidget>
#include <QScrollBar>

#include "Runtime/UI/UIDef.refl.h"

#include "PropertyEditorWidget.h"
#include "DocumentValueWatcher.h"

class UIEditor;

class UIEditorPropertyContainer : public QWidget
{
  Q_OBJECT;

public:
  UIEditorPropertyContainer(NotNullPtr<UIEditor> editor, UIDef & ui, Delegate<void> && size_change_cb, QWidget * parent = nullptr);


protected:
  void RepositionChildren();
  void SizeChanged();

protected:

  void resizeEvent(QResizeEvent * ev);

private:
  NotNullPtr<UIEditor> m_Editor;
  UIDef & m_UI;

  Delegate<void> m_SizeChanged;
};
