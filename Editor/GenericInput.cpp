
#include <QTimer>
#include <QEvent>
#include <QKeyEvent>
#include <QContextMenuEvent>

#include "GenericInput.h"

extern Delegate<void> g_GlobalUndo;
extern Delegate<void> g_GlobalRedo;

GenericInput::GenericInput(QWidget * parent) :
  QLineEdit(parent),
  m_IgnoreUpdate(false),
  m_PendingUpdate(false)
{
  connect(this, &GenericInput::textChanged, this, &GenericInput::handleTextChanged);

  installEventFilter(this);
}

void GenericInput::handleTextChanged(const QString &text)
{
  if (m_IgnoreUpdate)
  {
    return;
  }

  m_LastUpdate = std::chrono::system_clock::now();
  QTimer::singleShot(500, this, &GenericInput::timerExpired);

  m_PendingUpdate = true;
}

void GenericInput::timerExpired()
{
  if (std::chrono::system_clock::now() - m_LastUpdate > std::chrono::milliseconds(450))
  {
    m_LastUpdate = std::chrono::system_clock::now();
    m_UpdateCallback();

    m_PendingUpdate = false;
  }
}

void GenericInput::RemoteUpdate(czstr text)
{
  if (m_PendingUpdate)
  {
    return;
  }

  m_IgnoreUpdate = true;
  setText(text);
  m_IgnoreUpdate = false;
}

void GenericInput::SetUpdateCallback(Delegate<void> && callback)
{
  m_UpdateCallback = std::move(callback);
}

std::string GenericInput::GetText()
{
  return text().toStdString();
}

bool GenericInput::event(QEvent * ev)
{
  switch (ev->type())
  {
  case QEvent::KeyPress:
    {
      QKeyEvent * key_event = static_cast<QKeyEvent*>(ev);
      if (key_event->modifiers() & Qt::ControlModifier)
      {
        switch (key_event->key())
        {
        case Qt::Key_Z:
          if (key_event->modifiers() & Qt::ShiftModifier)
          {
            g_GlobalRedo();
          }
          else
          {
            g_GlobalUndo();
          }
          return true;
        case Qt::Key_Y:
          g_GlobalRedo();
          return true;
        }
      }
    }
    break;
  }

  return QLineEdit::event(ev);
}

void GenericInput::contextMenuEvent(QContextMenuEvent * ev)
{
  ev->ignore();
}
