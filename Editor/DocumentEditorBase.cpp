
#include "DocumentEditorBase.h"

#include <QGroupBox>

#include <Foundation/Document/DocumentTypes.refl.meta.h>

#include <StormData/StormDataChangePacket.h>
#include <StormData/StormDataPath.h>
#include <StormRefl/StormReflJsonStd.h>

DocumentEditorBase::DocumentEditorBase(PropertyFieldDatabase & property_db, const std::string & root_path, DocumentOutputDelegate && output_delegate, QWidget *parent) :
  QWidget(parent),
  m_PropertyDb(property_db),
  m_RootPath(root_path),
  m_State(DocumentState::kLoading),
  m_OutputDelegate(std::move(output_delegate)),
  m_UnacknowledgedChanges(0),
  m_IgnoreChanges(false),
  m_TransactionEnabled(false),
  m_DocumentErrorLayout(nullptr),
  m_DocumentErrorLabel(nullptr)
{
  SetupDocumentStateMessage();
}

DocumentEditorBase::~DocumentEditorBase()
{

}

void DocumentEditorBase::QueueChange(const ReflectionChangeNotification & change)
{
  m_PendingChanges.emplace_back(std::make_pair(0, StormDataCreateChangePacket(change)));

  if (change.m_Type == ReflectionNotifyChangeType::kRemove)
  {
    auto change_path = change.m_Path + "[" + std::to_string(change.m_SubIndex) + "]";

    for (auto & link : m_Links)
    {
      if (StormDataMatchPathPartial(link.m_LocalPath.data(), change_path.data()))
      {
        m_PendingChanges.emplace_back(std::make_pair(2, StormReflEncodeJson(std::make_tuple(link.m_SourceAsset, link.m_RemotePath, link.m_LocalPath))));
      }
    }
  }

  AddHotSpot(change);

  if (m_TransactionEnabled == false)
  {
    CommitQueuedChanges();
  }
}

void DocumentEditorBase::QueueAddLink(czstr source_document, czstr remote_path, czstr local_path)
{
  m_PendingChanges.emplace_back(std::make_pair(1, StormReflEncodeJson(std::make_tuple(std::string(source_document), std::string(remote_path), std::string(local_path)))));

  if (m_TransactionEnabled == false)
  {
    CommitQueuedChanges();
  }
}

void DocumentEditorBase::QueueRemoveLink(czstr source_document, czstr remote_path, czstr local_path)
{
  m_PendingChanges.emplace_back(std::make_pair(2, StormReflEncodeJson(std::make_tuple(std::string(source_document), std::string(remote_path), std::string(local_path)))));

  if (m_TransactionEnabled == false)
  {
    CommitQueuedChanges();
  }
}

void DocumentEditorBase::BeginTransaction()
{
  m_TransactionEnabled = true;
}

void DocumentEditorBase::CommitQueuedChanges()
{
  if (m_PendingChanges.size() != 0)
  {
    m_OutputDelegate(DocumentServerMessageType::kChange, StormReflEncodeJson(m_PendingChanges));
    m_PendingChanges.clear();
  }

  m_TransactionEnabled = false;
}

void DocumentEditorBase::GotServerChangeOkay()
{
  if (m_UnacknowledgedChanges > 0)
  {
    m_UnacknowledgedChanges--;

    if (m_UnacknowledgedChanges == 0)
    {
      SyncHotSpots();
    }
  }
}

void DocumentEditorBase::LinksChanged(std::string link_data)
{
  std::vector<std::tuple<std::string, std::string, std::string>> links;
  StormReflParseJson(links, link_data.data());

  m_Links.clear();
  for (auto & link : links)
  {
    auto & src_asset = std::get<0>(link);
    auto & remote_path = std::get<1>(link);
    auto & local_path = std::get<2>(link);

    m_Links.emplace_back(DocumentLink{ src_asset, remote_path, local_path });
  }

  UpdateLinks();
}


void DocumentEditorBase::GotDocumentChange(ReflectionChangeNotification & change)
{
  AddHotSpot(change);
}

void DocumentEditorBase::GotDocumentStateChange(DocumentState state, const std::string & document_data)
{
  m_State = state;

  if (m_State != DocumentState::kLoaded)
  {
    SetupDocumentStateMessage();
  }
}

void DocumentEditorBase::DocumentChangeComplete()
{
  if (m_UnacknowledgedChanges == 0)
  {
    SyncHotSpots();
  }
}

void DocumentEditorBase::ClearExistingContent()
{
  if (m_DocumentErrorLayout)
  {
    delete m_DocumentErrorLayout;
    m_DocumentErrorLayout = nullptr;
  }

  if (m_DocumentErrorLabel)
  {
    delete m_DocumentErrorLabel;
    m_DocumentErrorLabel = nullptr;
  }
}

void DocumentEditorBase::SetupDocumentStateMessage()
{
  ClearExistingContent();

  m_DocumentErrorLayout = new QGridLayout();
  m_DocumentErrorLayout->setColumnMinimumWidth(0, 1);
  m_DocumentErrorLayout->setColumnStretch(0, 1);

  m_DocumentErrorLayout->setColumnMinimumWidth(0, 1);
  m_DocumentErrorLayout->setColumnStretch(1, 2);

  m_DocumentErrorLayout->setColumnMinimumWidth(2, 1);
  m_DocumentErrorLayout->setColumnStretch(2, 1);

  m_DocumentErrorLayout->setRowMinimumHeight(0, 1);
  m_DocumentErrorLayout->setRowStretch(0, 1);

  m_DocumentErrorLayout->setRowMinimumHeight(1, 1);
  m_DocumentErrorLayout->setRowStretch(1, 2);

  m_DocumentErrorLayout->setRowMinimumHeight(2, 1);
  m_DocumentErrorLayout->setRowStretch(2, 3);

  m_DocumentErrorLayout->setRowMinimumHeight(3, 1);
  m_DocumentErrorLayout->setRowStretch(3, 1);

  m_DocumentErrorLabel = new QLabel("Loading document...");
  m_DocumentErrorLabel->setAlignment(Qt::AlignHCenter);
  m_DocumentErrorLayout->addWidget(m_DocumentErrorLabel, 1, 1);

  setLayout(m_DocumentErrorLayout);
}

void DocumentEditorBase::AddHotSpot(const ReflectionChangeNotification & change)
{
  auto path = change.m_Path;
  if (change.m_Type == ReflectionNotifyChangeType::kInsert && change.m_Type == ReflectionNotifyChangeType::kRemove)
  {
    path += '[';
    path += std::to_string(change.m_SubIndex);
    path += ']';
  }

  bool found_change = false;
  for (auto & hot_spot : m_HotSpots)
  {
    if (StormDataMatchPathPartial(path.data(), hot_spot.data()))
    {
      found_change = true;
      break;
    }
    else if (StormDataMatchPathPartial(hot_spot.data(), path.data()))
    {
      hot_spot = path;
      found_change = true;
      break;
    }
  }

  if (found_change == false)
  {
    m_HotSpots.emplace_back(path);
  }
}
