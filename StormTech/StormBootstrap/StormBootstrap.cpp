
#include "StormBootstrap/StormBootstrap.h"

#include "StormSockets/StormSocketBackend.h"
#include "StormSockets/StormSocketClientFrontendHttp.h"

#include <cstdio>
#include <cassert>

#ifdef _INCLUDEOS
#include <kernel/os.hpp>
#else
#include <thread>
#endif

StormBootstrap::StormBootstrap(int argc, const char ** argv)
{
  if(argc >= 1)
  {
    m_ExecutablePath = argv[0];

#ifdef _MSC_VER
    auto end = m_ExecutablePath.rfind('\\');
#else
    auto end = m_ExecutablePath.rfind('/');
#endif

    if(end != std::string::npos)
    {
      m_ExecutableDirectory = m_ExecutablePath.substr(0, end);
    }
  }

  for(int index = 1; index < argc; ++index)
  {
    if(argv[index][0] == '-')
    {
      if(argv[index][1] == '-')
      {
        auto equals = strchr(argv[index], '=');

        if(equals == nullptr)
        {
          m_Values.emplace(std::make_pair(std::string(argv[index] + 2), Value{ Priority::kCommandLine }));
        }
        else
        {
          std::string name(argv[index] + 2, equals - 1);
          m_Values.emplace(std::make_pair(name, Value{ Priority::kCommandLine, equals + 1 }));
        }
      }
      else
      {
        for(auto ptr = argv[index] + 1; *ptr != 0; ++ptr)
        {
          std::string str;
          str += *ptr;

          m_Values.emplace(std::make_pair(str, Value{Priority::kCommandLine}));
        }
      }
    }
    else
    {
      m_Args.push_back(argv[index]);
    }
  }
}


StormBootstrap::~StormBootstrap()
{
  Cleanup();
}

void StormBootstrap::LoadConfigFile(const std::string_view & path, std::function<void(const std::string &)> && callback)
{
  m_CurrentPriority = Priority::kFileConfig;
  auto fp = fopen(path.data(), "rb");
  if(fp == nullptr)
  {
    callback("");
    return;
  }

  fseek(fp, 0, SEEK_END);
  auto len = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  std::string str(len, ' ');
  fread(str.data(), 1, len, fp);
  fclose(fp);

  callback(str);
}


void StormBootstrap::RequestUrl(const std::string_view & url, const std::string_view & headers, std::function<void(const std::string &)> && callback)
{
  InitNetwork();
  auto frontend = (StormSockets::StormSocketClientFrontendHttp *)m_Frontend;

  StormSockets::StormURI uri;
  StormSockets::ParseURI(url.data(), uri);

  auto connection_id = frontend->RequestConnect(uri, "GET", nullptr, 0, headers.data(), headers.length());
  m_Jobs.emplace(std::make_pair(connection_id.m_Index.Raw, std::move(callback)));
}

void StormBootstrap::PostUrl(const std::string_view & url, const std::string_view & headers, const std::string_view & body, std::function<void(const std::string &)> && callback)
{
  InitNetwork();
  auto frontend = (StormSockets::StormSocketClientFrontendHttp *)m_Frontend;

  StormSockets::StormURI uri;
  StormSockets::ParseURI(url.data(), uri);

  auto connection_id = frontend->RequestConnect(uri, "GET", body.data(), body.length(), headers.data(), headers.length());
  m_Jobs.emplace(std::make_pair(connection_id.m_Index.Raw, std::move(callback)));
}

void StormBootstrap::Run()
{
  m_CurrentPriority = Priority::kWebConfig;

  while(m_Jobs.size() > 0)
  {
    auto frontend = (StormSockets::StormSocketClientFrontendHttp *) m_Frontend;
    StormSockets::StormSocketEventInfo event;
    while (frontend->GetEvent(event))
    {
      auto job_itr = m_Jobs.find((unsigned int) event.ConnectionId.m_Index.Raw);
      switch (event.Type)
      {
      case StormSockets::StormSocketEventType::ClientConnected:
        break;
      case StormSockets::StormSocketEventType::ClientHandShakeCompleted:
        break;
      case StormSockets::StormSocketEventType::Data:
        if (job_itr != m_Jobs.end())
        {
          auto response = event.GetHttpResponseReader();
          auto body = response.GetBodyReader();
          std::string str((std::size_t) body.GetRemainingLength(), ' ');
          body.ReadByteBlock(str.data(), body.GetRemainingLength());

          job_itr->second(str);
          m_Jobs.erase(job_itr);
        }
        break;
      case StormSockets::StormSocketEventType::Disconnected:
        if (job_itr != m_Jobs.end())
        {
          job_itr->second("");
          m_Jobs.erase(job_itr);
        }
        frontend->FinalizeConnection(event.ConnectionId);
        break;
      }
    }

#ifdef _INCLUDEOS
    OS::block();
#else
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
#endif
  }

  Cleanup();
}

void StormBootstrap::PrintDebug() const
{
  printf("StormBootstrap Debug Info:\n");
  printf("Executable path: %s\n", m_ExecutablePath.c_str());
  printf("Executable dir: %s\n\n", m_ExecutableDirectory.c_str());

  if(m_Args.empty())
  {
    printf("No program arguments\n\n");
  }
  else
  {
    printf("Arguments:\n");
    for(std::size_t index = 0; index < m_Args.size(); ++index)
    {
      printf("%d. %s\n", (int)index + 1, m_Args[index].c_str());
    }
    printf("\n");
  }

  if(m_Values.empty())
  {
    printf("No values\n\n");
  }
  else
  {
    printf("Values:\n");
    int index = 1;
    for (auto & elem : m_Values)
    {
      if(!elem.second.m_Data.empty())
      {
        printf("%d. %s = %s ", index, elem.first.c_str(), elem.second.m_Data.c_str());
      }
      else
      {
        printf("%d. %s ", index, elem.first.c_str());
      }

      switch(elem.second.m_Priority)
      {
      case Priority::kDefault:
        printf("Source: Default Value\n");
        break;
      case Priority::kFileConfig:
        printf("Source: File Config\n");
        break;
      case Priority::kWebConfig:
        printf("Source: Web Config\n");
        break;
      case Priority::kCommandLine:
        printf("Source: Command Line\n");
        break;
      case Priority::kPostRun:
        printf("Source: Post Run Value\n");
        break;
      }

      ++index;
    }
    printf("\n");

  }
}

void StormBootstrap::Set(const std::string_view & name, const std::string_view & value)
{
  auto itr = m_Values.find(name.data());
  if(itr == m_Values.end())
  {
    m_Values.emplace(std::make_pair(name.data(), Value{ m_CurrentPriority, value.data() }));
  }
  else if(itr->second.m_Priority <= m_CurrentPriority)
  {
    itr->second.m_Priority = m_CurrentPriority;
    itr->second.m_Data = value;
  }
}

std::string StormBootstrap::Get(const std::string_view & name) const
{
  auto itr = m_Values.find(name.data());
  if(itr == m_Values.end())
  {
    return {};
  }

  return itr->second.m_Data;
}

bool StormBootstrap::HasValue(const std::string_view & name) const
{
  auto itr = m_Values.find(name.data());
  if(itr == m_Values.end())
  {
    return false;
  }

  return true;
}

std::size_t StormBootstrap::GetNumArgs() const
{
  return m_Args.size();
}

const std::string & StormBootstrap::GetArg(int index) const
{
  static std::string empty_arg;
  return index < 0 || index >= (int)m_Args.size() ? empty_arg : m_Args[index];
}

const std::string & StormBootstrap::GetExecutablePath() const
{
  return m_ExecutablePath;
}

const std::string & StormBootstrap::GetExecutableDirectory() const
{
  return m_ExecutableDirectory;
}

void StormBootstrap::InitNetwork()
{
  static const int kMaxConnections = 8;
  if(m_Backend == nullptr)
  {
    StormSockets::StormSocketInitSettings backend_settings;
    backend_settings.MaxConnections = kMaxConnections;
    backend_settings.NumIOThreads = 1;
    backend_settings.NumSendThreads = 1;
    backend_settings.HeapSize = 0;
    backend_settings.LoadSystemCertificates = true;
    m_Backend = new StormSockets::StormSocketBackend(backend_settings);
  }

  if(m_Frontend == nullptr)
  {
    StormSockets::StormSocketClientFrontendHttpSettings http_settings;
    http_settings.MaxConnections = kMaxConnections;
    m_Frontend = new StormSockets::StormSocketClientFrontendHttp(http_settings, (StormSockets::StormSocketBackend *)m_Backend);
  }
}

void StormBootstrap::Cleanup()
{
  auto backend = (StormSockets::StormSocketBackend *)m_Backend;
  auto frontend = (StormSockets::StormSocketClientFrontendHttp *)m_Frontend;

  if(frontend)
  {
    delete frontend;
  }

  if(backend)
  {
    delete backend;
  }
}
