
#include "DistributionList.h"
#include "EditorContainer.h"

#include <QTimer>
#include <QPainter>
#include <QMessageBox>

DistributionListItem::DistributionListItem(DistributionList * list, const BuildInfo & info, QWidget * parent) :
  QWidget(parent),
  m_List(list),
  m_BuildId(info.m_BuildId)
{

  m_BuildIdLabel = std::make_unique<QLabel>(QString("Build #") + QString::number(info.m_BuildId), this);
  m_TimeLabel = std::make_unique<QLabel>(QString::fromStdString(info.m_Date), this);
  m_CreatorLabel = std::make_unique<QLabel>(QString::fromStdString(info.m_Name), this);
  m_DownloadButton = std::make_unique<QPushButton>("Download", this);
  connect(m_DownloadButton.get(), &QPushButton::pressed, this, &DistributionListItem::download);

  const char * plat_str;
  switch(info.m_Platform)
  {
  default:
    plat_str = "Unknown";
    break;
  case DistPlatform::kWindows:
    plat_str = "Windows";
    break;
  case DistPlatform::kLinux:
    plat_str = "Linux";
    break;
  case DistPlatform::kMac:
    plat_str = "Mac";
    break;
  }
  m_PlatformLabel = std::make_unique<QLabel>(QString(plat_str), this);

  m_BuildIdLabel->setGeometry(5, 0, 100, 20);
  m_TimeLabel->setGeometry(100, 0, 200, 20);
  m_CreatorLabel->setGeometry(5, 20, 100, 20);
}

void DistributionListItem::download()
{
  auto reply = QMessageBox::question(this, "Downloading Build...", "Are you sure you want to download this build?",
                                QMessageBox::Yes|QMessageBox::No);
  if (reply == QMessageBox::Yes)
  {
    m_List->m_DownloadCallback(m_BuildId);
  }
}

void DistributionListItem::resizeEvent(QResizeEvent * ev)
{
  m_PlatformLabel->setGeometry(width() - 55, 0, 50, 20);
  m_DownloadButton->setGeometry(width() - 105, 20, 100, 20);
}

DistributionList::DistributionList(Delegate<void> && recalculate, Delegate<void, int> && download, QWidget * parent) :
  QWidget(parent),
  m_RecalculateCallback(std::move(recalculate)),
  m_DownloadCallback(std::move(download))
{
  QTimer * timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &DistributionList::updateDist);
  timer->start(10);

  m_Fetcher = std::make_unique<DistFetcher>();
  m_Label = std::make_unique<QLabel>(this);
  m_Label->setAlignment(Qt::AlignmentFlag::AlignHCenter);
}

void DistributionList::SetFilter(bool filter)
{
  m_Filter = filter;
}

void DistributionList::Refresh()
{
  if(m_Refreshing)
  {
    return;
  }

  m_Items.clear();

  m_Label->setText("Downloading build list...");
  m_Label->setVisible(true);

  m_Fetcher = std::make_unique<DistFetcher>();
  m_Refreshing = true;

  m_RecalculateCallback();
}

void DistributionList::updateDist()
{
  auto finished = m_Fetcher->Update();
  if(m_Refreshing && finished)
  {
    m_Refreshing = false;

    auto result = m_Fetcher->GetResult().value();

    if(result == DistFetcherResult::kDone)
    {
      auto vec = m_Fetcher->GetBuildInfo().value();

      if(vec.size() == 0)
      {
        m_Label->setVisible(true);
        m_Label->setText("No builds.");
      }
      else
      {
        m_Label->setVisible(false);
        for(auto & elem : vec)
        {
          if(m_Filter == false || elem.m_Platform == CUR_PLATFORM)
          {
            m_Items.push_back(std::make_unique<DistributionListItem>(this, elem, this));
          }
        }

        RepositionElements();

        for(auto & elem : m_Items)
        {
          elem->show();
        }
      }
    }
    else
    {
      switch (result)
      {
      case DistFetcherResult::kProjectDirNotFound:
        m_Label->setText("project_dir.txt not found and PROJECT_DIR environment variable not set");
        break;
      case DistFetcherResult::kProjectSettingsNotFound:
        m_Label->setText("Could not open project credentials file");
        break;
      case DistFetcherResult::kProjectSettingsInvalid:
        m_Label->setText("Could not parse credentials file");
        break;
      case DistFetcherResult::kConnectionFailed:
        m_Label->setText("Connection failed");
        break;
      case DistFetcherResult::kDisconnected:
        m_Label->setText("Disconnected before upload complete");
        break;
      case DistFetcherResult::kDownloadListFailed:
        m_Label->setText("Download list failed");
        break;
      case DistFetcherResult::kInvalidBuildId:
        m_Label->setText("Invalid build id");
        break;
      }

      m_Label->setVisible(true);
    }

    m_RecalculateCallback();
  }
}

void DistributionList::resizeEvent(QResizeEvent * ev)
{
  m_Label->setGeometry(0, height() / 3, width() - 1, 20);
  RepositionElements();
}

void DistributionList::RepositionElements()
{
  int y = 0;
  for(auto & elem : m_Items)
  {
    elem->setGeometry(0, y, width() - 1, 50);
    y += 50;
  }

  setMinimumSize(200, y);
}

