#pragma once


#include <QObject>

class FocusWatcher : public QObject
{
  Q_OBJECT
public:
  explicit FocusWatcher(QObject *parent = 0);

protected:
  bool eventFilter(QObject *obj, QEvent *event) override;

signals:
  void focusChanged(bool in);

public slots:
};
