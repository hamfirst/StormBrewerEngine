#pragma once

#include <QWidget>
#include <QGridLayout>

#include "GameClientWidget.h"
#include "GameServerWidget.h"

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
  std::unique_ptr<GameServerWidget> m_Server;
};

