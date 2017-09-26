
#include "Foundation/Common.h"
#include "Foundation/Document/Document.h"
#include "Foundation/Document/DocumentCompiler.h"
#include "Foundation/FileSystem/File.h"
#include "Foundation/FileSystem/Path.h"

#include "Foundation/Document/DocumentTypes.refl.meta.h"

#include <StormRefl/StormReflJsonStd.h>
#include <StormData/StormDataPath.h>

#include <sb/vector.h>

Document::Document(NotNullPtr<DocumentCompiler> compiler, czstr path) :
  m_Compiler(compiler),
  m_Path(path),
  m_FileId(crc64(path)),
  m_State(DocumentState::kLoading),
  m_RefCount(0)
{
  SetUnloaded();
}

Document::~Document()
{
  for (auto & link : m_Links)
  {
    link.m_Document->RemoveDependency(this, link.m_Link.m_RemotePath.data());
    link.m_Document->DecRef();
  }
}

void Document::TearDown()
{
  m_Links.clear();
}

const std::string & Document::GetPath() const
{
  return m_Path;
}

uint64_t Document::GetFileId() const
{
  return m_FileId;
}

DocumentState Document::GetState() const
{
  return m_State;
}

std::string Document::GetDocumentJson()
{
  std::string str;
  m_Compiled.Encode(str);
  return str;
}

void Document::ParseFull(const char * file_data)
{
  std::vector<DocumentLinkData> old_links = std::move(m_Links);
  for (auto & link : old_links)
  {
    link.m_Document->RemoveDependency(this, link.m_Link.m_RemotePath.data());
  }

  std::vector<DocumentLink> links;
  SetUnloaded();

  bool file_error = false;

  m_FileJson = Json::CreateEmptyObject();
  m_Compiled = Json::CreateEmptyObject();

  if (StormReflParseJson(links, file_data, file_data) == false)
  {
    file_error = true;
  }
  else if (m_FileJson.Parse(file_data) != JsonParseResult::kNone)
  {
    file_error = true;
  }

  if (file_error)
  {
    for (auto & link : old_links)
    {
      link.m_Document->DecRef();
    }

    SetFileError();
    return;
  }

  for (auto & link : links)
  {
    auto doc = m_Compiler->GetDocument(link.m_SourceAsset.data());
    m_Links.emplace_back(DocumentLinkData{ doc, doc->GetFileId(), false, false, std::move(link) });
  }

  for (auto & link : m_Links)
  {
    link.m_Document->AddRef();
    link.m_Document->AddDependency(this, link.m_Link.m_RemotePath.data());
  }

  for (auto & link : old_links)
  {
    link.m_Document->DecRef();
  }

  if (m_LinksChangedHandler)
  {
    m_LinksChangedHandler(GetFileId(), this);
  }

  CheckForCompleteLoad();
}

void Document::FileError()
{
  SetFileError();
}

void Document::Save(const std::string & root_path)
{
  auto full_path = GetFullPath(m_Path, root_path);
  File file = FileOpen(full_path.data(), FileOpenMode::kWrite);
  if (file.GetFileOpenError() > 0)
  {
    return;
  }

  std::vector<DocumentLink> links;
  for (auto link : m_Links)
  {
    links.emplace_back(link.m_Link);
  }

  std::string link_data;
  StormReflEncodeJson(links, link_data);

  file.Write(link_data.data());
  file.Write("\n\n");

  std::string json_data;
  m_FileJson.EncodePretty(json_data);
  file.Write(json_data);

  FileClose(file);

  if (m_State == DocumentState::kLoadFailure)
  {
    SetCompletedLoad();
  }
}

void Document::SetChangeHandler(DocumentChangeHandler && change_handler)
{
  m_ChangeHandler = std::move(change_handler);
}

void Document::SetStateChangeHandler(DocumentStateChangeHandler && change_handler)
{
  m_StateChangeHandler = std::move(change_handler);
}

void Document::SetLinksChangeHandler(DocumentLinksChangeHandler && change_handler)
{
  m_LinksChangedHandler = std::move(change_handler);
}

void Document::ApplyChange(const ReflectionChangeNotification & change, bool as_redo)
{
  ReflectionChangeNotification reverse_change;
  m_FileJson.ApplyChange(change, &reverse_change);

  if (change.m_Type == ReflectionNotifyChangeType::kSet)
  {
    auto compiled_json = m_Compiled.GetJsonAtPath(change.m_Path.data(), true);
    RecompileAtPath(change.m_Path.data(), *compiled_json);

    if (m_State == DocumentState::kLoaded)
    {
      ReflectionChangeNotification compiled_change = change;

      compiled_change.m_Data.clear();
      compiled_json->Encode(compiled_change.m_Data);
      m_ChangeHandler(m_FileId, this, compiled_change);
    }
  }
  else if (change.m_Type == ReflectionNotifyChangeType::kInsert)
  {
    std::string target_path = change.m_Path;
    target_path += '[';
    target_path += std::to_string(change.m_SubIndex);
    target_path += ']';

    auto compiled_json = m_Compiled.GetJsonAtPath(target_path.data(), true);
    RecompileAtPath(target_path.data(), *compiled_json);

    if (m_State == DocumentState::kLoaded)
    {
      ReflectionChangeNotification compiled_change = change;

      compiled_change.m_Data.clear();
      compiled_json->Encode(compiled_change.m_Data);
      m_ChangeHandler(m_FileId, this, compiled_change);
    }
  }
  else if (change.m_Type == ReflectionNotifyChangeType::kRevert)
  {
    Json json;
    if (RecompileAtPath(change.m_Path.data(), json))
    {
      auto compiled_json = m_Compiled.GetJsonAtPath(change.m_Path.data(), true);
      *compiled_json = std::move(json);

      if (m_State == DocumentState::kLoaded)
      {
        ReflectionChangeNotification compiled_change = change;
        compiled_change.m_Type = ReflectionNotifyChangeType::kSet;

        compiled_change.m_Data.clear();
        compiled_json->Encode(compiled_change.m_Data);
        m_ChangeHandler(m_FileId, this, compiled_change);
      }
    }
    else
    {
      m_Compiled.ApplyChange(change, nullptr);

      if (m_State == DocumentState::kLoaded)
      {
        m_ChangeHandler(m_FileId, this, change);
      }
    }
  }
  else
  {
    m_Compiled.ApplyChange(change, nullptr);

    if (m_State == DocumentState::kLoaded)
    {
      m_ChangeHandler(m_FileId, this, change);
    }
  }

  auto reverse_operation = std::function<void()>([this, rchange = std::move(reverse_change), as_redo]
  {
    ApplyChange(rchange, !as_redo);
  });

  if (as_redo)
  {
    m_CurrentRedo.emplace_back(std::move(reverse_operation));
  }
  else
  {
    m_CurrentUndo.emplace_back(std::move(reverse_operation));
  }

  for (auto & dep : m_Dependencies)
  {
    dep.m_Document->HandleLinkChanged(this, change);
  }
}

void Document::AddLink(const char * source_document, const char * source_path, const char * dest_path, bool as_redo)
{
  auto doc = m_Compiler->GetDocument(source_document);
  DocumentLink link = { source_document, source_path, dest_path };

  m_Links.emplace_back(DocumentLinkData{ doc, doc->GetFileId(), false, false, std::move(link) });
  if (m_LinksChangedHandler)
  {
    m_LinksChangedHandler(GetFileId(), this);
  }

  doc->AddDependency(this, source_path);

  auto reverse_operation = std::function<void()>([=, file_id = crc64(source_document), spath = std::string(source_path), dpath = std::string(dest_path)]
  {
    RemoveLink(file_id, spath.data(), dpath.data(), !as_redo);
  });

  if (as_redo)
  {
    m_CurrentRedo.emplace_back(std::move(reverse_operation));
  }
  else
  {
    m_CurrentUndo.emplace_back(std::move(reverse_operation));
  }
}

bool Document::RemoveLink(uint64_t file_id, const char * source_path, const char * dest_path, bool as_redo)
{
  for(std::size_t index = 0, end = m_Links.size(); index < end; index++)
  {
    auto & link = m_Links[index];
    if (link.m_FileId == file_id && link.m_Link.m_RemotePath == source_path && link.m_Link.m_LocalPath == dest_path)
    {
      auto reverse_operation = std::function<void()>([=, sdoc = std::string(link.m_Link.m_SourceAsset), spath = std::string(link.m_Link.m_LocalPath), rpath = std::string(link.m_Link.m_RemotePath)]
      {
        AddLink(sdoc.data(), spath.data(), rpath.data(), !as_redo);
      });

      if (as_redo)
      {
        m_CurrentRedo.emplace_back(std::move(reverse_operation));
      }
      else
      {
        m_CurrentUndo.emplace_back(std::move(reverse_operation));
      }

      auto local_path = link.m_Link.m_LocalPath;
      m_Links.erase(m_Links.begin() + index);

      if (m_LinksChangedHandler)
      {
        m_LinksChangedHandler(GetFileId(), this);
      }

      if (m_State == DocumentState::kLoaded)
      {
        Json json;
        if (RecompileAtPath(local_path.data(), json))
        {
          ReflectionChangeNotification change;
          change.m_Type = ReflectionNotifyChangeType::kSet;
          change.m_Path = local_path;
          json.Encode(change.m_Data);

          m_Compiled.ApplyChange(change, nullptr);

          if (m_ChangeHandler)
          {
            m_ChangeHandler(GetFileId(), this, change);
          }
        }
        else
        {
          ReflectionChangeNotification change;
          change.m_Type = ReflectionNotifyChangeType::kRevert;
          change.m_Path = local_path;

          m_Compiled.ApplyChange(change, nullptr);

          if (m_ChangeHandler)
          {
            m_ChangeHandler(GetFileId(), this, change);
          }
        }
      }
      else if (m_State == DocumentState::kDependentError)
      {
        CheckForFixedLoad();
      }

      return true;
    }
  }

  return false;
}

std::vector<std::tuple<std::string, std::string, std::string>> Document::GetLinks()
{
  std::vector<std::tuple<std::string, std::string, std::string>> links;
  for (auto & link : m_Links)
  {
    links.emplace_back(std::make_tuple(link.m_Link.m_SourceAsset, link.m_Link.m_RemotePath, link.m_Link.m_LocalPath));
  }

  return links;
}


void Document::CommitUndo()
{
  m_Undo.emplace_back([this, undo_list = std::move(m_CurrentUndo)]()
  {
    for (int index = (int)undo_list.size() - 1; index >= 0; --index)
    {
      undo_list[index]();
    }

    CommitRedo();
  });
}


void Document::CommitRedo()
{
  m_Redo.emplace_back([this, undo_list = std::move(m_CurrentRedo)]()
  {
    for (int index = (int)undo_list.size() - 1; index >= 0; --index)
    {
      undo_list[index]();
    }

    CommitUndo();
  });
}

void Document::CleanRedoList()
{
  m_Redo.clear();
}

bool Document::Undo()
{
  if (m_Undo.size() > 0)
  {
    auto & undo_op = m_Undo.back();
    undo_op();

    m_Undo.pop_back();
    return true;
  }

  return false;
}

bool Document::Redo()
{
  if (m_Redo.size() > 0)
  {
    auto & undo_op = m_Redo.back();
    undo_op();

    m_Redo.pop_back();
    return true;
  }

  return false;
}

void Document::AddRef()
{
  m_RefCount++;
}

void Document::DecRef()
{
  m_RefCount--;

  if (m_RefCount == 0)
  {
    m_Compiler->UnloadDocument(m_FileId);
    return;
  }
}

std::string Document::CreateEmptyFile()
{
  return "[]\n\n{}\n";
}


bool Document::RecompileAtPath(czstr path, Json & outp_json)
{
  std::vector<std::pair<std::string, Json *>> linked_data;
  auto path_len = strlen(path);

  for (auto & link : m_Links)
  {
    if (StormDataMatchPathPartial(path, link.m_Link.m_LocalPath.data()))
    {
      auto link_path = link.m_Link.m_RemotePath + (path + link.m_Link.m_LocalPath.length());
      auto src_json = link.m_Document->m_Compiled.GetJsonAtPath(link_path.data(), false);

      if (src_json)
      {
        linked_data.emplace_back(std::make_pair("", src_json));
      }
    }
    else if (StormDataMatchPathPartial(link.m_Link.m_LocalPath.data(), path))
    {
      auto src_json = link.m_Document->m_Compiled.GetJsonAtPath(link.m_Link.m_LocalPath.data(), false);
      if (src_json)
      {
        linked_data.emplace_back(std::make_pair(link.m_Link.m_RemotePath.data() + path_len, src_json));
      }
    }
  }

  auto json = m_FileJson.GetJsonAtPath(path, false);
  if (json)
  {
    linked_data.emplace_back(std::make_pair("", json));
  }

  if (linked_data.size() == 0)
  {
    return false;
  }

  outp_json = {};
  for(auto & data : linked_data)
  {
    auto json = outp_json.GetJsonAtPath(data.first.data(), true);
    json->ApplyJson(*data.second);
  }

  return true;
}

void Document::CheckForCompleteLoad()
{
  bool all_load_complete = true;

  for (auto & link : m_Links)
  {
    if (link.m_Loaded == false)
    {
      all_load_complete = false;
      break;
    }
  }

  if (all_load_complete)
  {
    bool load_success = true;

    for (auto & link : m_Links)
    {
      if (link.m_Error == true)
      {
        load_success = true;
        break;
      }
    }

    if (load_success == false)
    {
      SetDependentError();
    }
    else
    {
      SetCompletedLoad();
    }
  }
}

void Document::CheckForFixedLoad()
{
  bool load_success = true;

  for (auto & link : m_Links)
  {
    if (link.m_Error == true)
    {
      load_success = false;
      break;
    }
  }

  if (load_success)
  {
    SetCompletedLoad();
  }
}

void Document::ProcessLinkLoad(DocumentLinkData & link)
{
  auto dst_json = link.m_Document->m_Compiled.GetJsonAtPath(link.m_Link.m_RemotePath.data(), false);
  if (dst_json == nullptr)
  {
    return;
  }

  auto json = m_Compiled.GetJsonAtPath(link.m_Link.m_LocalPath.data(), true);
  RecompileAtPath(link.m_Link.m_LocalPath.data(), *json);

  if (m_State == DocumentState::kLoaded && m_ChangeHandler)
  {
    ReflectionChangeNotification change;
    change.m_Type = ReflectionNotifyChangeType::kSet;
    change.m_Path = link.m_Link.m_LocalPath.data();
    json->Encode(change.m_Data);

    m_ChangeHandler(m_FileId, this, change);
  }
}

void Document::SetUnloaded()
{
  auto prev_state = m_State;
  m_State = DocumentState::kLoading;
  if (m_StateChangeHandler)
  {
    m_StateChangeHandler(m_FileId, this, m_State, prev_state);
  }
}

void Document::SetCompletedLoad()
{
  if (m_State == DocumentState::kLoaded)
  {
    return;
  }


  m_Compiled = m_FileJson;
  for (auto & link : m_Links)
  {
    ProcessLinkLoad(link);
  }

  for (auto & dep : m_Dependencies)
  {
    auto json = m_Compiled.GetJsonAtPath(dep.m_Path.data(), false);
    dep.m_Document->HandleLinkLoaded(this, dep.m_Path.data(), json);
  }

  auto prev_state = m_State;
  m_State = DocumentState::kLoaded;

  if (m_StateChangeHandler)
  {
    m_StateChangeHandler(m_FileId, this, m_State, prev_state);
  }
}

void Document::SetDependentError()
{
  if (m_State == DocumentState::kDependentError)
  {
    return;
  }

  for (auto & dep : m_Dependencies)
  {
    dep.m_Document->HandleLinkFailed(this, dep.m_Path.data());
  }

  auto prev_state = m_State;
  m_State = DocumentState::kDependentError;

  if (m_StateChangeHandler)
  {
    m_StateChangeHandler(m_FileId, this, m_State, prev_state);
  }
}

void Document::SetFileError()
{
  if (m_State == DocumentState::kLoadFailure)
  {
    return;
  }

  auto prev_state = m_State;
  m_State = DocumentState::kLoadFailure;

  for (auto & dep : m_Dependencies)
  {
    dep.m_Document->HandleLinkFailed(this, dep.m_Path.data());
  }

  for (auto & link : m_Links)
  {
    link.m_Document->RemoveDependency(this, link.m_Link.m_RemotePath.data());
  }

  m_Links.clear();
  m_FileJson = Json::CreateEmptyObject();
  m_Compiled = Json::CreateEmptyObject();

  if (m_StateChangeHandler)
  {
    m_StateChangeHandler(m_FileId, this, m_State, prev_state);
  }
}

void Document::HandleLinkLoaded(Document * source_document, const char * path, NullOptPtr<Json> json)
{
  for (auto & link : m_Links)
  {
    if (link.m_Document == source_document && link.m_Link.m_RemotePath == path)
    {
      if (m_State == DocumentState::kLoading)
      {
        link.m_Loaded = true;
        link.m_Error = false;

        CheckForCompleteLoad();
      }
      else if (m_State == DocumentState::kDependentError)
      {
        link.m_Error = false;

        CheckForFixedLoad();
      }
      else if (m_State == DocumentState::kLoaded)
      {
        ProcessLinkLoad(link);

        for (auto & dep : m_Dependencies)
        {
          if (StormDataMatchPathPartial(dep.m_Path.data(), path) || StormDataMatchPathPartial(path, dep.m_Path.data()))
          {
            auto json = m_Compiled.GetJsonAtPath(dep.m_Path.data(), false);
            dep.m_Document->HandleLinkLoaded(this, dep.m_Path.data(), json);
          }
        }
      }
    }
  }
}

void Document::HandleLinkFailed(Document * source_document, const char * path)
{
  for (auto & link : m_Links)
  {
    if (link.m_Document == source_document && link.m_Link.m_RemotePath == path)
    {
      link.m_Loaded = true;
      link.m_Error = true;

      if (m_State == DocumentState::kLoaded)
      {
        SetDependentError();
      }
      else if (m_State == DocumentState::kLoading)
      {
        CheckForCompleteLoad();
      }
    }
  }
}

void Document::HandleLinkChanged(Document * source_document, const ReflectionChangeNotification & change)
{
  for (auto & link : m_Links)
  {
    if (link.m_Document == source_document)
    {
      if (StormDataMatchPathPartial(change.m_Path.data(), link.m_Link.m_RemotePath.data()) ||
          StormDataMatchPathPartial(link.m_Link.m_RemotePath.data(), change.m_Path.data()))
      {
        auto compiled_json = m_Compiled.GetJsonAtPath(link.m_Link.m_LocalPath.data(), true);
        RecompileAtPath(link.m_Link.m_LocalPath.data(), *compiled_json);

        ReflectionChangeNotification compiled_change;
        compiled_change.m_Type = ReflectionNotifyChangeType::kSet;
        compiled_change.m_Path = link.m_Link.m_LocalPath;
        compiled_json->Encode(compiled_change.m_Data);
        m_ChangeHandler(m_FileId, this, compiled_change);
      }
    }
  }
}

void Document::AddDependency(Document * dependent, const char * path)
{
  m_Dependencies.emplace_back(DocumentDependency{ dependent, path });

  if (m_State == DocumentState::kLoaded)
  {
    auto json = m_Compiled.GetJsonAtPath(path, false);
    dependent->HandleLinkLoaded(this, path, json);
  }
  else if (m_State == DocumentState::kLoadFailure || m_State == DocumentState::kDependentError)
  {
    dependent->HandleLinkFailed(this, path);
  }
}

void Document::RemoveDependency(Document * dependent, const char * path)
{
  for (std::size_t index = 0, end = m_Dependencies.size(); index < end; index++)
  {
    auto & dep = m_Dependencies[index];
    if (dep.m_Document == dependent && dep.m_Path == path)
    {
      vremove_index_quick(m_Dependencies, index);
      return;
    }
  }
}
