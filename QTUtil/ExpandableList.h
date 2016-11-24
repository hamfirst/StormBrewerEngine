#pragma once

#include <vector>
#include <memory>

#include "LerpVar.h"

#include <QWidget>
#include <QScrollBar>
#include <QFrame>

class ExpandableList : public QWidget
{
  Q_OBJECT
public:
  explicit ExpandableList(Qt::Orientation orientation, QWidget *parent = 0);

  void SetInitialWidgets(std::vector<QWidget *> && widgets);
  void AddWidget(int index, QWidget * widget);
  void RemoveWidget(QWidget * widget);
  void RemoveAllWidgets();

  void SelectItem(QWidget * widget);
protected:

  void resizeEvent(QResizeEvent *event) override;
  void wheelEvent(QWheelEvent * event) override;

  void updateScrolls();
  void updateContent();
  int calculateContentSize() const;
  void finalizePositions(bool force);

  std::vector<QWidget *> m_Widgets;
  std::vector<std::unique_ptr<LerpVar>> m_WidgetPositions;
  std::vector<std::unique_ptr<LerpVar>> m_WidgetSizes;

  QScrollBar * m_Scroll;
  QFrame * m_Frame;
  std::unique_ptr<LerpVar> m_ScrollVal;

  Qt::Orientation m_Orientation;
  int m_SelectedItem;

  bool m_IgnoreScrollEvents;

signals:

public slots:
  void scrollValueChanged(int value);
  void updateAnimations();
};
