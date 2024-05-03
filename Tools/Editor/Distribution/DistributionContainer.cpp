
#include "DistributionContainer.h"
#include "EditorContainer.h"

DistributionContainer::DistributionContainer(EditorContainer * editor) :
  m_Editor(editor)
{
  setFocusPolicy(Qt::ClickFocus);
  setAttribute(Qt::WA_InputMethodEnabled);
  setAttribute(Qt::WA_X11NetWmWindowTypeDialog);

  m_ListContainer = std::make_unique<ScrollingPanel>(this);
  m_List = m_ListContainer->CreateWidget<DistributionList>([this](){ m_ListContainer->recalculate(); },
      [this](int build_id){ m_Editor->DownloadBuild(build_id); });
  m_List->Refresh();

  m_Refresh = std::make_unique<QPushButton>("Refresh", this);
  connect(m_Refresh.get(), &QPushButton::pressed, this, &DistributionContainer::refresh);

  m_FilterPlatform = std::make_unique<QCheckBox>("Filter For Only This Platform", this);
  m_FilterPlatform->setChecked(true);
  connect(m_FilterPlatform.get(), &QCheckBox::stateChanged, this, &DistributionContainer::refresh);

  resize(1024, 720);
}

void DistributionContainer::refresh()
{
  m_List->Refresh();
}

void DistributionContainer::resizeEvent(QResizeEvent * ev)
{
  m_FilterPlatform->setGeometry(5, 5, 250, 20);
  m_Refresh->setGeometry(width() - 155, 5, 150, 20);
  m_ListContainer->setGeometry(0, 40, width() - 1, height() - 41);
}

void DistributionContainer::closeEvent(QCloseEvent * ev)
{
  m_Editor->NotifyClientWindowClosed(this);
}
