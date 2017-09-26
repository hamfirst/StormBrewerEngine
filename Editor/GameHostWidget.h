#pragma once

#include <QWidget>
#include <QGridLayout>

#include "GameClientWidget.h"
#include "GameServerWidget.h"

class GameHostWidget : public QWidget
{
  Q_OBJECT
public:

  GameHostWidget(EditorContainer * editor, int number_of_clients, QWidget *parent = Q_NULLPTR);

protected:

  void closeEvent(QCloseEvent * ev) override;
  void resizeEvent(QResizeEvent * ev) override;

private:

  NotNullPtr<EditorContainer> m_Editor;

  std::unique_ptr<QGridLayout> m_Layout;

  std::vector<std::unique_ptr<GameClientWidget>> m_Clients;
  std::unique_ptr<GameServerWidget> m_Server;
};

