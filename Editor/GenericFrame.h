#pragma once

#include <QGroupBox>

#include <Foundation/Common.h>
#include <Foundation/Delegate/Delegate.h>

class GenericFrame : public QGroupBox
{
  Q_OBJECT;
public:

  GenericFrame(czstr title, QWidget * parent = nullptr);

  void SetChildWidget(std::unique_ptr<QWidget> && widget);

  template <typename T>
  T * CreateWidget()
  {
    SetChildWidget(std::make_unique<T>(this));
    return static_cast<T *>(m_ChildWidget.get());
  }

protected:
  void UpdatePosition();

  void resizeEvent(QResizeEvent * ev) override;

private:

  std::unique_ptr<QWidget> m_ChildWidget;
};