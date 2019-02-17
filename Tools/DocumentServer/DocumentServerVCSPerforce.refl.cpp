

#ifdef ENABLE_PERFORCE

#include "DocumentServerVCSPerforce.refl.meta.h"

#include "Foundation/Assert/Assert.h"
#include "Foundation/FileSystem/Path.h"

#include "StormRefl/StormReflJsonStd.h"
#include "StormRefl/StormReflMetaEnum.h"

#include "p4/clientapi.h"

#include "gsl/gsl"
#include "hash/Hash64.h"

#include <unordered_map>

#include <filesystem>
namespace fs = std::filesystem;

class DocumentServerVCSUser : public ClientUser
{
public:

  void OutputError(const char *err) override
  {
    m_ErrorCallback(err);
  }

  void OutputInfo(char level, const char * info) override
  {
    m_InfoCallback(level, info);
  }

  void OutputStat(StrDict * list)
  {
    m_StatCallback(list);
  }

  Delegate<void, czstr> m_ErrorCallback;
  Delegate<void, char, czstr> m_InfoCallback;
  Delegate<void, StrDict *> m_StatCallback;
};


DocumentServerVCSPerforce::DocumentServerVCSPerforce()
{

}

DocumentServerVCSPerforce::~DocumentServerVCSPerforce()
{

}

bool DocumentServerVCSPerforce::Init(const std::string_view & settings, const std::string_view & project_dir,
                                const std::string & self_path, Delegate<void, const std::string &> && error_callback)
{
  m_ErrorCallback = std::move(error_callback);

  DocumentServerVCSPerforceInitData settings_data;
  if(!StormReflParseJson(settings_data, settings))
  {
    m_ErrorCallback("Could not parse settings");
    return false;
  }

  m_RootPath = settings_data.RootPath.size() > 0 ? settings_data.RootPath : project_dir;
  m_RootPath = std::filesystem::canonical(m_RootPath).string();
  m_SelfPath = std::filesystem::relative(self_path, m_RootPath).string();
  m_User = settings_data.User;
  m_Pass = settings_data.Password;
  m_Port = settings_data.Port;
  m_Client = settings_data.Client;
  return true;
}

void DocumentServerVCSPerforce::GetStatus(std::vector<DocumentServerVCSQuery> & queries)
{
  std::vector<std::string> file_strs;
  std::vector<const char *> file_ptrs;
  file_ptrs.reserve(queries.size());

  std::unordered_map<uint64_t, std::size_t> file_index_lookup;

  for(auto & elem : queries)
  {
    std::string converted_path = elem.m_FilePath;
    if(!ConvertPath(converted_path))
    {
      m_ErrorCallback(std::string("File ") + converted_path + " is not in the root directory");
    }

    file_strs.emplace_back(std::move(converted_path));
  }

  std::size_t lookup_index = 0;
  for(auto & elem : file_strs)
  {
    file_ptrs.push_back(elem.data());
    file_index_lookup.emplace(std::make_pair(crc64(elem), lookup_index));
    lookup_index++;
  }

  WithClient([&](ClientApi & client)
  {
    client.SetArgv(file_ptrs.size(), (char * const *)file_ptrs.data());
    client.Run("fstat");
  },
  [&](czstr error)
  {
    m_ErrorCallback(error);
  },
  [&](char level, czstr info)
  {
    m_ErrorCallback(info);
  },
  [&](StrDict * list)
  {

  });
}

void DocumentServerVCSPerforce::Add(std::vector<DocumentServerVCSOperation> & files)
{
  std::vector<DocumentServerVCSQuery> status_queries;
  for(auto & elem : files)
  {
    status_queries.emplace_back(DocumentServerVCSQuery{ elem.m_FilePath });
  }

  GetStatus(status_queries);

  for(std::size_t elem_index = 0, end = files.size(); elem_index < end; ++elem_index)
  {
    auto & status = status_queries[elem_index];
    auto & elem = files[elem_index];

    if(status.m_Status == VCSStatus::kNew)
    {
      std::string converted_path = elem.m_FilePath;
      if (!ConvertPath(converted_path))
      {
        m_ErrorCallback(std::string("File ") + converted_path + " is not in the root directory");
      }

      elem.m_Success = false;
    }
    else
    {
      elem.m_Success = false;
    }
  }
}

void DocumentServerVCSPerforce::Remove(const std::string_view & file_path)
{
  std::string converted_path = std::string(file_path.data(), file_path.size());
  if(!ConvertPath(converted_path))
  {
    m_ErrorCallback(std::string("File ") + converted_path + " is not in the root directory");
    return;
  }


}

void DocumentServerVCSPerforce::Revert(const std::string_view & file_path)
{
  std::string converted_path = std::string(file_path.data(), file_path.size());
  if(!ConvertPath(converted_path))
  {
    m_ErrorCallback(std::string("File ") + converted_path + " is not in the root directory");
    return;
  }

}

template <typename Visitor, typename ErrorCb>
void DocumentServerVCSPerforce::WithClient(Visitor && visitor, ErrorCb && errorcb)
{
  WithClient(std::forward<Visitor>(visitor), std::forward<ErrorCb>(errorcb),
      [this](char, czstr info) { m_ErrorCallback(info); }, [](StrDict *){});
}

template <typename Visitor, typename ErrorCb, typename InfoCb>
void DocumentServerVCSPerforce::WithClient(Visitor && visitor, ErrorCb && errorcb, InfoCb && infocb)
{
  WithClient(std::forward<Visitor>(visitor), std::forward<ErrorCb>(errorcb), std::forward<InfoCb>(infocb), [](StrDict *){});
}

template <typename Visitor, typename ErrorCb, typename InfoCb, typename StatCb>
void DocumentServerVCSPerforce::WithClient(Visitor && visitor, ErrorCb && errorcb, InfoCb && infocb, StatCb && statcb)
{
  DocumentServerVCSUser ui;
  ClientApi client;
  StrBuf msg;
  Error e;

  ui.m_ErrorCallback = [&](czstr error){ errorcb(error); };
  ui.m_InfoCallback = [&](char level, czstr info){ infocb(level, info); };
  ui.m_StatCallback = [&](StrDict * list) { statcb(list); };

  if(!m_Port.empty())
  {
    client.SetPort(m_Port.c_str());
  }

  client.Init(&e);
  if(e.Test())
  {
    e.Fmt(&msg);
    m_ErrorCallback(msg.Text());
  }

  if(!m_Client.empty())
  {
    client.SetClient(m_Client.c_str());
  }

  if(!m_User.empty())
  {
    client.SetUser(m_User.c_str());
  }

  if(!m_Pass.empty())
  {
    client.SetPassword(m_Pass.c_str());
  }

  client.SetUi(&ui);
  visitor(client);
}

bool DocumentServerVCSPerforce::ConvertPath(std::string & path)
{
  std::error_code ec;

  auto fs_path = fs::path(path);
  if(fs_path.is_absolute() == false)
  {
    auto abs_path = fs::path(m_RootPath) / fs::path(m_SelfPath) / fs_path;
    fs_path = fs::absolute(abs_path, ec);

    if(ec)
    {
      return false;
    }

    auto test_path = fs_path.string();
    fs_path = fs::canonical(fs_path, ec);

    if(ec)
    {
      return false;
    }
  }

  fs_path = fs::relative(fs_path, fs::path(m_RootPath), ec);
  if(ec)
  {
    return false;
  }

  path = fs_path.string();
  return true;
}

#endif