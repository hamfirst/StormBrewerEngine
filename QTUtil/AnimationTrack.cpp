#include "AnimationTrack.h"

#include <algorithm>

#include <QPainter>
#include <QMenu>

static bool EventSortFunc(const AnimationTrackEventInfo & a, const AnimationTrackEventInfo & b)
{
  if(a.m_Frame < b.m_Frame)
    return true;
  if(b.m_Frame < a.m_Frame)
    return false;
  if(a.m_Delay < b.m_Delay)
    return true;
  if(b.m_Delay < a.m_Delay)
    return false;
  return a.m_Id < b.m_Id;
};

AnimationTrack::AnimationTrack(QWidget *parent) :
  QWidget(parent),
  m_ScrollBar(std::make_unique<QScrollBar>(Qt::Horizontal, this))
{
  connect(m_ScrollBar.get(), &QScrollBar::valueChanged, this, &AnimationTrack::scrollValueChanged);
  setMouseTracking(true);
}

void AnimationTrack::SetFrames(std::vector<AnimationTrackFrameInfo> && frames)
{
  m_Frames = std::move(frames);
  updateScroll();
  update();
}

void AnimationTrack::SetEvents(std::vector<AnimationTrackEventInfo> && events)
{
  m_Events = std::move(events);

  std::sort(m_Events.begin(), m_Events.end(), EventSortFunc);
  update();
}

QSize AnimationTrack::sizeHint() const
{
  auto total_length = 0;
  for(auto & elem : m_Frames)
  {
    total_length += elem.m_FrameLength;
  }

  auto last_ev = std::make_pair(-1, -1);
  int cur_events = 0;
  int max_events = 0;

  for(auto & ev : m_Events)
  {
    bool frame_match = last_ev.first == ev.m_Frame && last_ev.second == ev.m_Delay;
    if(ev.m_Frame >= m_Frames.size())
    {
      if(last_ev.first >= m_Frames.size())
      {
        frame_match = true;
      }
    }
    else if(ev.m_Frame == last_ev.first)
    {
      if(ev.m_Delay >= m_Frames[ev.m_Frame].m_FrameLength && last_ev.second >= m_Frames[ev.m_Frame].m_FrameLength)
      {
        frame_match = true;
      }
    }

    if(frame_match)
    {
      cur_events++;
    }
    else
    {
      max_events = std::max(max_events, cur_events);
      last_ev.first = ev.m_Frame;
      last_ev.second = ev.m_Delay;
      cur_events = 1;
    }
  }

  return QSize(total_length * 10 + 20, max_events * 40 + 20 + m_ScrollBar->sizeHint().height());
}

void AnimationTrack::scrollValueChanged(int value)
{
  update();
}

void AnimationTrack::handleAddEvent()
{
  emit newEvent(m_SelectedFrame, m_SelectedFrameDelay);
}

void AnimationTrack::handleDeleteEvent()
{
  emit deleteEvent(m_MenuEvent);
}

void AnimationTrack::paintEvent(QPaintEvent * ev)
{
  QPainter p(this);

  int x = -m_ScrollBar->value() + 10;
  for(auto frame_index = 0, end = (int)m_Frames.size(); frame_index < end; ++frame_index)
  {
    auto & frame = m_Frames[frame_index];
    for(int delay = 0; delay < frame.m_FrameLength; ++delay)
    {
      if(frame_index == m_SelectedFrame && delay == m_SelectedFrameDelay)
      {
        p.setPen(QPen(QColor(150, 150, 255, 255), 4));
        p.drawLine(QPoint(x, 1), QPoint(x, 10));
        p.setPen(QPen(Qt::blue, 3));
        p.drawLine(QPoint(x - 3, 1), QPoint(x + 3, 1));
        p.drawLine(QPoint(x - 4, 1), QPoint(x - 4, 10));
        p.drawLine(QPoint(x + 3, 1), QPoint(x + 3, 10));
        p.drawLine(QPoint(x - 3, 10), QPoint(x, 16));
        p.drawLine(QPoint(x + 3, 10), QPoint(x, 16));
      }

      if(frame_index == m_HighlightedFrame && delay == m_HighlightedFrameDelay)
      {
        p.setPen(QPen(Qt::blue, delay == 0 ? 2 : 1));
        p.drawLine(QPoint(x - 1, delay == 0 ? 20 : 22), QPoint(x - 1, 30));
        p.drawLine(QPoint(x + 1, delay == 0 ? 20 : 22), QPoint(x + 1, 30));
        p.setPen(QPen(Qt::darkYellow, delay == 0 ? 2 : 1));
        p.drawLine(QPoint(x, delay == 0 ? 20 : 22), QPoint(x, 30));
      }
      else
      {
        p.setPen(QPen(Qt::black, delay == 0 ? 2 : 1));
        p.drawLine(QPoint(x, delay == 0 ? 20 : 22), QPoint(x, 30));
      }
      x += 10;
    }
  }

  VisitEvents([&](const AnimationTrackEventInfo & info, int x, int y)
  {
    if(info.m_Id == m_SelectedEvent)
    {
      p.setPen(QPen(Qt::black, 1));
      p.setBrush(QColor(255, 190, 0, 255));
    }
    else if(info.m_Id == m_HighlightedEvent)
    {
      p.setPen(QPen(Qt::black, 1));
      p.setBrush(QBrush(Qt::yellow));
    }
    else
    {
      p.setPen(QPen(Qt::black, 1));
      switch(info.m_Type % 7)
      {
      case 0:
        p.setBrush(QBrush(Qt::blue));
        break;
      case 1:
        p.setBrush(QBrush(Qt::darkBlue));
        break;
      case 2:
        p.setBrush(QBrush(Qt::darkGreen));
        break;
      case 3:
        p.setBrush(QBrush(Qt::green));
        break;
      case 4:
        p.setBrush(QBrush(Qt::cyan));
        break;
      case 5:
        p.setBrush(QBrush(Qt::gray));
        break;
      case 6:
        p.setBrush(QBrush(Qt::lightGray));
        break;
      }
    }

    p.drawEllipse(QPoint(x, y), 5, 5);
  });
}

void AnimationTrack::resizeEvent(QResizeEvent * ev)
{
  int h = m_ScrollBar->sizeHint().height();
  m_ScrollBar->setGeometry(0, height() - h - 1, width() - 1, h);

  updateScroll();
}

void AnimationTrack::mousePressEvent(QMouseEvent * ev)
{
  if (ev->button() == Qt::RightButton)
  {
    QMenu menu(this);
    connect(menu.addAction("Add"), &QAction::triggered, this, &AnimationTrack::handleAddEvent);

    if (m_HighlightedEvent != -1)
    {
      m_MenuEvent = m_HighlightedEvent;
      connect(menu.addAction("Delete"), &QAction::triggered, this, &AnimationTrack::handleDeleteEvent);
    }
    else
    {
      m_MenuEvent = -1;
    }

    menu.exec(mapToGlobal(ev->pos()));
    return;
  }

  if(m_HighlightedEvent != -1)
  {
    for(auto & event_info : m_Events)
    {
      if(event_info.m_Id == m_HighlightedEvent)
      {
        m_SelectedEvent = m_HighlightedEvent;
        m_SelectedEventFrame = event_info.m_Frame;
        m_SelectedEventFrameDelay = event_info.m_Delay;
        emit selectedEventChanged(m_SelectedEvent);

        m_DragMode = AnimationTrackDragMode::kDragEvent;

        m_HighlightedFrame = event_info.m_Frame;
        m_HighlightedFrameDelay = event_info.m_Delay;

        m_SelectedFrame = event_info.m_Frame;
        m_SelectedFrameDelay = event_info.m_Delay;
        emit selectedFrameChanged(m_SelectedFrame, m_SelectedFrameDelay);

        grabMouse();
        repaint();
        break;
      }
    }
  }
  else if(m_HighlightedFrame != -1 &&
          m_HighlightedFrameDelay != -1)
  {
    m_SelectedFrame = m_HighlightedFrame;
    m_SelectedFrameDelay = m_HighlightedFrameDelay;
    m_SelectedEvent = -1;
    emit selectedFrameChanged(m_SelectedFrame, m_SelectedFrameDelay);
    emit selectedEventChanged(-1);

    repaint();

    m_DragMode = AnimationTrackDragMode::kScrub;
    grabMouse();
  }
}

void AnimationTrack::mouseReleaseEvent(QMouseEvent * ev)
{
  if(m_DragMode != AnimationTrackDragMode::kNone)
  {
    releaseMouse();
  }

  if(m_DragMode == AnimationTrackDragMode::kDragEvent)
  {
    emit eventMoved(m_SelectedEvent, m_SelectedEventFrame, m_SelectedEventFrameDelay);
  }

  m_DragMode = AnimationTrackDragMode::kNone;

  m_SelectedEvent = -1;
  m_SelectedEventFrame = 0;
  m_SelectedEventFrameDelay = 0;
  repaint();
}

void AnimationTrack::mouseMoveEvent(QMouseEvent * ev)
{
  auto prev_highlighted_event = m_HighlightedEvent;
  m_HighlightedEvent = -1;

  auto prev_highlighted_frame = m_HighlightedFrame;
  auto prev_highlighted_frame_delay = m_HighlightedFrameDelay;

  m_HighlightedFrame = -1;
  m_HighlightedFrameDelay = -1;

  auto prev_selected_event_frame = m_SelectedEventFrame;
  auto prev_selected_event_frame_delay = m_SelectedEventFrameDelay;

  m_SelectedEventFrame = 0;
  m_SelectedEventFrameDelay = 0;

  auto x = ev->x();
  x -= 5;

  if(m_DragMode == AnimationTrackDragMode::kDragEvent)
  {
    bool found_pos = false;
    for(int frame_index = 0, end = (int)m_Frames.size(); frame_index < end; ++frame_index)
    {
      for(int delay = 0; delay < m_Frames[frame_index].m_FrameLength; ++delay)
      {
        if(x < 10)
        {
          m_SelectedEventFrame = frame_index;
          m_SelectedEventFrameDelay = delay;

          m_HighlightedFrame = frame_index;
          m_HighlightedFrameDelay = delay;

          m_SelectedFrame = frame_index;
          m_SelectedFrameDelay = delay;
          emit selectedFrameChanged(m_SelectedFrame, m_SelectedFrameDelay);
          found_pos = true;
          break;
        }

        x -= 10;
      }

      if(found_pos)
      {
        break;
      }
    }

    if(found_pos == false && m_Frames.size() > 0)
    {
      m_SelectedEventFrame = (int)m_Frames.size() - 1;
      m_SelectedEventFrameDelay = m_Frames[m_SelectedEventFrame].m_FrameLength - 1;

      m_HighlightedFrame = m_SelectedEventFrame;
      m_HighlightedFrameDelay = m_SelectedEventFrameDelay;

      m_SelectedFrame = m_SelectedEventFrame;
      m_SelectedFrameDelay = m_SelectedEventFrameDelay;
      emit selectedFrameChanged(m_SelectedFrame, m_SelectedFrameDelay);
    }
  }
  else if(ev->y() < 35 || m_DragMode == AnimationTrackDragMode::kScrub)
  {
    if(ev->x() > 0)
    {
      for(int frame_index = 0, end = (int)m_Frames.size(); frame_index < end; ++frame_index)
      {
        for(int delay = 0; delay < m_Frames[frame_index].m_FrameLength; ++delay)
        {
          if(x < 10)
          {
            m_HighlightedFrame = frame_index;
            m_HighlightedFrameDelay = delay;

            if(m_DragMode != AnimationTrackDragMode::kNone)
            {
              if(m_HighlightedFrame != -1 &&
                 m_HighlightedFrameDelay != -1)
              {
                m_SelectedFrame = m_HighlightedFrame;
                m_SelectedFrameDelay = m_HighlightedFrameDelay;
                emit selectedFrameChanged(m_SelectedFrame, m_SelectedFrameDelay);
                repaint();
              }
            }

            break;
          }

          x -= 10;
        }

        if(m_HighlightedFrame >= 0)
        {
          break;
        }
      }
    }
  }
  else
  {
    VisitEvents([&](const AnimationTrackEventInfo & info, int x, int y)
    {
      auto dx = abs(x - ev->x());
      auto dy = abs(y - ev->y());

      if(dx <= 8 && dy <= 8)
      {
        m_HighlightedEvent = info.m_Id;
      }
    });
  }

  if(prev_highlighted_event != m_HighlightedEvent ||
     prev_highlighted_frame != m_HighlightedFrame ||
     prev_highlighted_frame_delay != m_HighlightedFrameDelay ||
     prev_selected_event_frame != m_SelectedEventFrame ||
     prev_selected_event_frame_delay != m_SelectedEventFrameDelay)
  {
    repaint();
  }
}

void AnimationTrack::leaveEvent(QEvent * ev)
{
  m_HighlightedEvent = -1;
  m_HighlightedFrame = -1;
  m_HighlightedFrameDelay = -1;
  repaint();
}

void AnimationTrack::updateScroll()
{
  QSize size = VisitEvents([](const AnimationTrackEventInfo & event, int x, int y)
  {

  });

  if(size.width() <= width())
  {
    m_ScrollBar->setValue(0);
    m_ScrollBar->hide();
  }
  else
  {
    m_ScrollBar->show();
    m_ScrollBar->setMaximum(size.width() - width());
    m_ScrollBar->setPageStep(width());
  }
}

template <typename Visitor>
QSize AnimationTrack::VisitEvents(Visitor && visitor)
{
  auto total_length = 0;
  for(auto & elem : m_Frames)
  {
    total_length += elem.m_FrameLength;
  }

  auto last_ev = std::make_pair(-1, -1);
  int cur_events = 1;
  int max_events = 0;

  auto events = m_Events;
  if(m_SelectedEvent != -1)
  {
    for(auto & ev : events)
    {
      if(ev.m_Id == m_SelectedEvent)
      {
        ev.m_Frame = m_SelectedEventFrame;
        ev.m_Delay = m_SelectedEventFrameDelay;
      }
    }

    std::sort(events.begin(), events.end(), EventSortFunc);
  }

  for(auto & ev : events)
  {
    bool frame_match = last_ev.first == ev.m_Frame && last_ev.second == ev.m_Delay;    
    int x = -m_ScrollBar->value() + 10;

    for(int frame_index = 0; frame_index < ev.m_Frame && frame_index < m_Frames.size(); frame_index++)
    {
      x += 10 * m_Frames[frame_index].m_FrameLength;
    }

    if(ev.m_Frame < m_Frames.size())
    {
      if(ev.m_Delay < m_Frames[ev.m_Frame].m_FrameLength)
      {
        x += 10 * ev.m_Delay;
      }
      else
      {
        x += 10 * (m_Frames[ev.m_Frame].m_FrameLength - 1);
      }
    }

    if(ev.m_Frame >= m_Frames.size())
    {
      if(last_ev.first >= m_Frames.size())
      {
        frame_match = true;
      }
    }
    else if(ev.m_Frame == last_ev.first)
    {
      if(ev.m_Delay >= m_Frames[ev.m_Frame].m_FrameLength && last_ev.second >= m_Frames[ev.m_Frame].m_FrameLength)
      {
        frame_match = true;
      }
    }

    int y = 40;

    if(frame_match)
    {
      y += 10 * cur_events;
      cur_events++;
      visitor(ev, x, y);
    }
    else
    {
      max_events = std::max(max_events, cur_events);
      last_ev.first = ev.m_Frame;
      last_ev.second = ev.m_Delay;
      cur_events = 1;

      visitor(ev, x, y);
    }
  }

  return QSize(total_length * 10 + 20, max_events * 40 + 20 + m_ScrollBar->sizeHint().height());
}

