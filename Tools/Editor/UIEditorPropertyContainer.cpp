
#include <QMenu>
#include <QKeyEvent>
#include <QPainter>
#include <QStyle>
#include <QStyleOptionFrame>
#include <QMouseEvent>

#include <StormRefl/StormReflJson.h>
#include <StormData/StormDataJson.h>

#include "UIEditor.h"
#include "UIEditorPropertyContainer.h"

UIEditorPropertyContainer::UIEditorPropertyContainer(NotNullPtr<UIEditor> editor, UIDef & ui, Delegate<void> && size_change_cb, QWidget * parent) :
  QWidget(parent),
  m_Editor(editor),
  m_UI(ui),
  m_SizeChanged(std::move(size_change_cb))
{
  setFocusPolicy(Qt::ClickFocus);
}

void UIEditorPropertyContainer::RepositionChildren()
{
  int height = 0;
  int w = width() - 1;

  setMinimumHeight(height);
}

void UIEditorPropertyContainer::SizeChanged()
{
  RepositionChildren();
  m_SizeChanged();
}

void UIEditorPropertyContainer::resizeEvent(QResizeEvent * ev)
{
  RepositionChildren();
}
