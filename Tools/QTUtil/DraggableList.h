

#include <vector>
#include <memory>

#include "QtLerpVar.h"

#include <QWidget>
#include <QFrame>
#include <QTime>
#include <QScrollBar>

class DraggableList : public QFrame
{
  Q_OBJECT
public:
  explicit DraggableList(Qt::Orientation orientation, bool invert = false, QWidget *parent = 0);

  void SetInitialWidgets(const std::vector<QWidget *> & widgets);

  void AddWidget(QWidget * widget, int index = -1);
  void RemoveWidget(QWidget * widget);
  void RemoveAllWidgets();

  void BringIntoView(int index);

  void StartDragging(int target_index);
  void Rearrange(int src_index, int target_index);

  void SetScaleToFit(bool enable);

  void SetSelection(int index, bool additive);
  void ResetSelection();
  void RemoveSelection(int index);
  bool IsSelected(int index);

protected:

  void resizeEvent(QResizeEvent *event) override;
  void wheelEvent(QWheelEvent * event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;

  void updateScrolls();
  void updateContent();
  int calculateContentSize() const;
  void finalizePositions(bool force);
  void updateDrag();
  int transformDragIndex(int index);

  std::vector<QWidget *> m_Widgets;
  std::vector<std::unique_ptr<QtLerpVar>> m_WidgetPositions;
  std::vector<bool> m_IsSelected;
  QScrollBar * m_Scroll;
  std::unique_ptr<QtLerpVar> m_ScrollVal;

  Qt::Orientation m_Orientation;

  bool m_Invert;
  bool m_IgnoreScrollEvents;

  bool m_Dragging;
  bool m_ScaleToFit;
  int m_DraggingOriginalIndex;
  int m_DraggingTargetIndex;
  int m_DragTimerLastUpdate;
  float m_DragScrollError;
  QElapsedTimer m_DragTimer;

signals:
  void dragComplete(int start_index, int end_index);

public slots:
  void scrollValueChanged(int value);
  void updateAnimations();
};

