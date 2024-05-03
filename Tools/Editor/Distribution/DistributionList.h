#pragma once

#include <memory>
#include <vector>

#include <QWidget>
#include <QLabel>
#include <QPushButton>

#include "Foundation/Delegate/Delegate.h"

#include "DistTools/DistFetcher.h"

class DistributionList;

class DistributionListItem : public QWidget
{
  Q_OBJECT
public:
  DistributionListItem(DistributionList * list, const BuildInfo & info, QWidget * parent = nullptr);

public slots:

  void download();

protected:

  void resizeEvent(QResizeEvent * ev) override;

private:
  DistributionList * m_List;
  int m_BuildId;

  std::unique_ptr<QLabel> m_BuildIdLabel;
  std::unique_ptr<QLabel> m_TimeLabel;
  std::unique_ptr<QLabel> m_PlatformLabel;
  std::unique_ptr<QLabel> m_CreatorLabel;
  std::unique_ptr<QPushButton> m_DownloadButton;
};

class DistributionList : public QWidget
{
  Q_OBJECT
public:
  DistributionList(Delegate<void> && recalculate, Delegate<void, int> && download, QWidget * parent);

  void SetFilter(bool filter);
  void Refresh();

public slots:
  void updateDist();

protected:

  void resizeEvent(QResizeEvent * ev) override;
  void closeEvent(QCloseEvent * ev) override;

  void RepositionElements();

private:

  friend class DistributionListItem;

  Delegate<void> m_RecalculateCallback;
  Delegate<void, int> m_DownloadCallback;

  std::unique_ptr<DistFetcher> m_Fetcher;
  std::unique_ptr<QLabel> m_Label;
  std::vector<std::unique_ptr<DistributionListItem>> m_Items;

  bool m_Refreshing = false;
  bool m_Filter = true;
};