#pragma once

#include <memory>

#include "Foundation/Common.h"

#include <QWidget>
#include <QScrollBar>

class ScrollingPanel : public QWidget
{
  Q_OBJECT;

public:
  ScrollingPanel(QWidget * parent = nullptr);

  void SetChildWidget(std::unique_ptr<QWidget> && widget);

  template <typename T, typename ... Args>
  T * CreateWidget(Args && ... args)
  {
    SetChildWidget(std::make_unique<T>(std::forward<Args>(args)..., this));
    return static_cast<T *>(m_Widget.get());
  }

public slots:

  void recalculate();
  void scrollChanged();

protected:
  virtual void resizeEvent(QResizeEvent * ev) override;
  virtual void wheelEvent(QWheelEvent * ev) override;
  virtual void paintEvent(QPaintEvent * ev) override;

public:

  std::unique_ptr<QWidget> m_Widget;
  bool m_ShowScrollbar;

  std::unique_ptr<QScrollBar> m_ScrollBar;
};
