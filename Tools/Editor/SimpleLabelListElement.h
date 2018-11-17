#pragma once

#include <QWidget>

#include "Foundation/Common.h"

class SimpleLabelListElement : public QWidget
{
public:

  SimpleLabelListElement(QWidget * parent = nullptr);

  void SetText(czstr text);
  void SetSelected(bool selected);
  void SetClickedCallback(Delegate<void> && cb);

protected:
  void paintEvent(QPaintEvent * ev) override;
  void mousePressEvent(QMouseEvent * ev) override;

private:
  QString m_Text;
  Delegate<void> m_ClickedDelegate;

  bool m_Selected;
};

