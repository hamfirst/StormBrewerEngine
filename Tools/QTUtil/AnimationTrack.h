#pragma once

#include <vector>
#include <memory>

#include <QWidget>
#include <QScrollBar>
#include <QPaintEvent>
#include <QResizeEvent>

struct AnimationTrackFrameInfo
{
  int m_FrameLength;
};

struct AnimationTrackEventInfo
{
  int m_Frame;
  int m_Delay;
  int m_Id;
  int m_Type;
};

enum class AnimationTrackDragMode
{
  kNone,
  kScrub,
  kDragEvent,
};

class AnimationTrack : public QWidget
{
  Q_OBJECT
public:
  explicit AnimationTrack(QWidget *parent = 0);

  void SetFrames(std::vector<AnimationTrackFrameInfo> && frames);
  void SetEvents(std::vector<AnimationTrackEventInfo> && events);

  QSize sizeHint() const override;

signals:
  void newEvent(int frame, int delay);
  void deleteEvent(int event_id);

  void selectedFrameChanged(int frame, int delay);
  void selectedEventChanged(int event_id);
  void eventMoved(int event_id, int frame, int delay);

public slots:
  void scrollValueChanged(int value);

  void handleAddEvent();
  void handleDeleteEvent();
protected:

  template <typename Visitor>
  QSize VisitEvents(Visitor && visitor);

  void paintEvent(QPaintEvent * ev) override;
  void resizeEvent(QResizeEvent * ev) override;

  void mousePressEvent(QMouseEvent * ev) override;
  void mouseReleaseEvent(QMouseEvent * ev) override;
  void mouseMoveEvent(QMouseEvent * ev) override;

  void leaveEvent(QEvent * ev) override;

  void updateScroll();

private:
  std::vector<AnimationTrackFrameInfo> m_Frames;
  std::vector<AnimationTrackEventInfo> m_Events;

  std::unique_ptr<QScrollBar> m_ScrollBar;
  AnimationTrackDragMode m_DragMode = AnimationTrackDragMode::kNone;

  int m_SelectedFrame = 0;
  int m_SelectedFrameDelay = 0;
  int m_SelectedEvent = -1;
  int m_SelectedEventFrame = 0;
  int m_SelectedEventFrameDelay = 0;

  int m_HighlightedFrame = -1;
  int m_HighlightedFrameDelay = -1;
  int m_HighlightedEvent = -1;

  int m_MenuEvent = -1;
};


