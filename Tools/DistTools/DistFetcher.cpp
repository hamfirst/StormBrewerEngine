
#include "DistFetcher.h"

#include <iostream>
#include <filesystem>

#include "StormSockets/StormSocketClientFrontendWebsocket.h"
#include "StormSockets/StormSocketBackend.h"

#include "StormRefl/StormReflJsonStd.h"

#include "Packets.h"
#include "Settings.refl.meta.h"


struct DistFetcherInternal
{
  std::optional<DistFetcherResult> m_Result;
  UploadSettings m_Settings;

  std::unique_ptr<StormSockets::StormSocketBackend> m_Backend;
  std::unique_ptr<StormSockets::StormSocketClientFrontendWebsocket> m_Frontend;
  StormSockets::StormSocketConnectionId m_ConnectionId;
  StormSockets::StormSemaphore m_Semaphore;

  std::optional<std::vector<uint8_t>> m_DownloadData;
  std::optional<std::vector<BuildInfo>> m_DownloadList;

  bool m_StartedConnection = false;
  bool m_Connected = false;
  bool m_WantsList = false;
  bool m_Complete = false;
  int m_BuildId = 0;
};

DistFetcher::DistFetcher()
{
  m_Data = std::make_unique<DistFetcherInternal>();
  m_Data->m_WantsList = true;

  if(ReadProjectSettings() == false)
  {
    return;
  }

  StartConnection();
}

DistFetcher::DistFetcher(int build_id)
{
  m_Data = std::make_unique<DistFetcherInternal>();
  m_Data->m_BuildId = build_id;

  if(ReadProjectSettings() == false)
  {
    return;
  }

  StartConnection();
}

DistFetcher::~DistFetcher()
{

}

bool DistFetcher::Update()
{
  if(m_Data->m_StartedConnection == false)
  {
    return false;
  }

  StormSockets::StormSocketEventInfo event;
  while(m_Data->m_Frontend->GetEvent(event))
  {
    switch(event.Type)
    {
    case StormSockets::StormSocketEventType::ClientConnected:
      m_Data->m_Connected = true;
      break;
    case StormSockets::StormSocketEventType::ClientHandShakeCompleted:
    {
      auto packet = m_Data->m_Frontend->CreateOutgoingPacket(StormSockets::StormSocketWebsocketDataType::Binary, true);

      if(m_Data->m_WantsList)
      {
        packet.WriteInt32((int)MessageType::kDownloadList);
        m_Data->m_Frontend->FinalizeOutgoingPacket(packet);
        m_Data->m_Frontend->SendPacketToConnection(packet, m_Data->m_ConnectionId);
        m_Data->m_Frontend->FreeOutgoingPacket(packet);
      }
      else
      {
        if(m_Data->m_BuildId == 0)
        {
          packet.WriteInt32((int) MessageType::kDownloadLatest);
          packet.WriteInt32((int)CUR_PLATFORM);
        }
        else
        {
          packet.WriteInt32((int) MessageType::kDownload);
          packet.WriteInt32(m_Data->m_BuildId);
        }
        m_Data->m_Frontend->FinalizeOutgoingPacket(packet);
        m_Data->m_Frontend->SendPacketToConnection(packet, m_Data->m_ConnectionId);
        m_Data->m_Frontend->FreeOutgoingPacket(packet);
      }
      break;
    }
    case StormSockets::StormSocketEventType::Data:
    {
      auto reader = event.GetWebsocketReader();
      if (m_Data->m_WantsList)
      {
        int data_length = reader.GetDataLength();
        if (data_length < 4)
        {
          m_Data->m_Frontend->FreeIncomingPacket(reader);
          m_Data->m_Frontend->ForceDisconnect(event.ConnectionId);
          return SetResult(DistFetcherResult::kDownloadListFailed);
        }

        int num_builds = reader.ReadInt32();
        data_length -= 4;

        std::vector <BuildInfo> builds;
        for (int index = 0; index < num_builds; ++index)
        {
          if (data_length < sizeof(DownloadList))
          {
            m_Data->m_Frontend->FreeIncomingPacket(reader);
            m_Data->m_Frontend->ForceDisconnect(event.ConnectionId);
            return SetResult(DistFetcherResult::kDownloadListFailed);
          }

          DownloadList list_elem;
          reader.ReadByteBlock(&list_elem, sizeof(DownloadList));
          data_length -= sizeof(DownloadList);

          time_t t = atoi(&list_elem.m_Name[ 1 ]);
          auto time_info = localtime(&t);

          const char * desc = strstr(list_elem.m_Name, "_");
          if (desc == nullptr)
          {
            desc = "Unknown";
          }
          else
          {
            desc++;
          }

          char timestr[256];
          strftime(timestr, sizeof(timestr), "%m/%d/%y %H:%M:%S", time_info);

          BuildInfo build;
          build.m_BuildId = list_elem.m_Id;
          build.m_Name = desc;
          build.m_Date = timestr;

          auto plat_chr = list_elem.m_Name[ 0 ];
          switch (plat_chr)
          {
          default:
            build.m_Platform = DistPlatform::kUnknown;
            break;
          case 'W':
            build.m_Platform = DistPlatform::kWindows;
            break;
          case 'L':
            build.m_Platform = DistPlatform::kLinux;
            break;
          case 'M':
            build.m_Platform = DistPlatform::kMac;
            break;
          }

          builds.emplace_back(std::move(build));
        }

        m_Data->m_DownloadList = std::move(builds);
      }
      else
      {
        if (reader.GetDataLength() > 0)
        {
          auto buffer_len = reader.GetDataLength();
          auto buffer = std::vector <uint8_t>();

          buffer.resize(buffer_len);
          reader.ReadByteBlock(buffer.data(), reader.GetDataLength());
          m_Data->m_DownloadData = std::move(buffer);
        }
        else
        {
          m_Data->m_Frontend->FreeIncomingPacket(reader);
          m_Data->m_Frontend->ForceDisconnect(event.ConnectionId);
          return SetResult(DistFetcherResult::kInvalidBuildId);
        }
      }

      m_Data->m_Frontend->FreeIncomingPacket(reader);
      m_Data->m_Frontend->ForceDisconnect(event.ConnectionId);
      return SetResult(DistFetcherResult::kDone);
    }
    case StormSockets::StormSocketEventType::Disconnected:
      if(m_Data->m_Connected)
      {
        if(m_Data->m_Complete)
        {
          return true;
        }

        return SetResult(DistFetcherResult::kDisconnected);
      }
      else
      {
        return SetResult(DistFetcherResult::kConnectionFailed);
      }
    }
  }

  return false;
}

void DistFetcher::Sync()
{
  if(m_Data->m_StartedConnection == false)
  {
    return;
  }

  while(m_Data->m_Result.has_value() == false)
  {
    m_Data->m_Semaphore.WaitOne();
    Update();
  }
}

std::optional<std::vector<BuildInfo>> DistFetcher::GetBuildInfo()
{
  return m_Data->m_DownloadList;
}

std::optional<std::pair<const void *, std::size_t>> DistFetcher::GetDownloadData()
{
  if(m_Data->m_DownloadData)
  {
    auto & vec = m_Data->m_DownloadData.value();
    return std::make_pair(vec.data(), vec.size());
  }

  return std::nullopt;
}

std::optional<DistFetcherResult> DistFetcher::GetResult()
{
  if(m_Data->m_Result)
  {
    return m_Data->m_Result.value();
  }

  return std::nullopt;
}

bool DistFetcher::ReadProjectSettings()
{
  std::string project_dir;
  auto project_dir_env = getenv("PROJECT_DIR");
  if(project_dir_env)
  {
    project_dir = project_dir_env;
  }
  else
  {
    auto fp = fopen("project_dir.txt", "rb");
    if(fp == nullptr)
    {
      m_Data->m_Result = DistFetcherResult::kProjectDirNotFound;
      return false;
    }

    fseek(fp, 0, SEEK_END);
    auto project_dir_file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    project_dir.resize(project_dir_file_size + 1);
    fread(project_dir.data(), project_dir_file_size, 1, fp);
    project_dir[project_dir_file_size] = 0;
    fclose(fp);

    while(isspace(project_dir.back()) || project_dir.back() == 0)
    {
      project_dir.pop_back();
    }

    project_dir = std::filesystem::canonical(std::filesystem::absolute(project_dir)).string();
  }

  auto project_settings_dir_path = std::filesystem::path(project_dir) / "ProjectSettings";
  auto project_settings_file = project_settings_dir_path / "ProjectDistSettings.txt";

  auto settings_file = fopen(project_settings_file.string().c_str(), "rb");
  if(settings_file == nullptr)
  {
    SetResult(DistFetcherResult::kProjectSettingsNotFound);
    return false;
  }

  fseek(settings_file, 0, SEEK_END);
  auto settings_file_size = ftell(settings_file);
  fseek(settings_file, 0, SEEK_SET);

  auto settings_buffer = std::make_unique<char[]>(settings_file_size + 1);
  fread(settings_buffer.get(), 1, settings_file_size, settings_file);
  fclose(settings_file);

  settings_buffer[settings_file_size] = 0;
  if(StormReflParseJson(m_Data->m_Settings, settings_buffer.get()) == false)
  {
    SetResult(DistFetcherResult::kProjectSettingsInvalid);
    return false;
  }

  return true;
}

void DistFetcher::StartConnection()
{
  StormSockets::StormSocketInitSettings settings;
  settings.MaxConnections = 4;
  settings.NumIOThreads = 1;
  settings.NumSendThreads = 1;
  settings.HeapSize = 0;
  settings.LoadSystemCertificates = false;
  m_Data->m_Backend = std::make_unique<StormSockets::StormSocketBackend>(settings);

  StormSockets::StormSocketClientFrontendWebsocketSettings client_settings;
  client_settings.EventSemaphore = &m_Data->m_Semaphore;
  m_Data->m_Frontend = std::make_unique<StormSockets::StormSocketClientFrontendWebsocket>(client_settings, m_Data->m_Backend.get());

  StormSockets::StormSocketClientFrontendWebsocketRequestData request_data;
  request_data.m_Protocol = m_Data->m_Settings.m_DistServerIdent.size() ? m_Data->m_Settings.m_DistServerIdent.c_str() : nullptr;
  m_Data->m_ConnectionId = m_Data->m_Frontend->RequestConnect(m_Data->m_Settings.m_DistServerAddress.c_str(), m_Data->m_Settings.m_DistServerPort, request_data);

  m_Data->m_StartedConnection = true;
}

bool DistFetcher::SetResult(DistFetcherResult result)
{
  m_Data->m_Complete = true;
  m_Data->m_Result = result;
  return true;
}
