
#pragma once

#include <QWidget>
#include <QPushButton>
#include <QCheckBox>

#include "Tools/Editor/UI/UtilityWidgets/ScrollingPanel.h"
#include "DistributionList.h"

class EditorContainer;

class DistributionContainer : public QWidget
{
  Q_OBJECT
public:
  DistributionContainer(EditorContainer * editor);

public slots:

  void refresh();

protected:

  void resizeEvent(QResizeEvent * ev);
  void closeEvent(QCloseEvent * ev);

private:
  EditorContainer * m_Editor;
  DistributionList * m_List;
  std::unique_ptr<ScrollingPanel> m_ListContainer;
  std::unique_ptr<QPushButton> m_Refresh;
  std::unique_ptr<QCheckBox> m_FilterPlatform;
};