#pragma once

#include <QWidget>
#include <QGridLayout>

#include "GameClientWidget.h"
#include "GameServerWidget.h"

#define WIDGET_MODE_HORIZONTAL 0
#define WIDGET_MODE_VERTICAL   1
#define WIDGET_MODE_4X4        2

#define WIDGET_MODE WIDGET_MODE_4X4

class GameHostWidget : public QWidget
{
  Q_OBJECT
public:

  GameHostWidget(EditorContainer * editor, QWidget *parent = Q_NULLPTR);

protected:

  void closeEvent(QCloseEvent * ev) override;
  void resizeEvent(QResizeEvent * ev) override;

private:

  NotNullPtr<EditorContainer> m_Editor;

  std::unique_ptr<QGridLayout> m_Layout;

  std::unique_ptr<GameClientWidget> m_Client1;
  std::unique_ptr<GameClientWidget> m_Client2;

#if WIDGET_MODE == WIDGET_MODE_4X4
  std::unique_ptr<GameClientWidget> m_Client3;
  std::unique_ptr<GameClientWidget> m_Client4;
#endif

  std::unique_ptr<GameServerWidget> m_Server;
};

