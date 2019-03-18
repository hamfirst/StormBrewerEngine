

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>

#include <iostream>
#include <filesystem>

#include <miniz-cpp/zip_file.hpp>

#include "StormSockets/StormSocketBackend.h"
#include "StormSockets/StormSocketClientFrontendWebsocket.h"

#include "StormRefl/StormReflJsonStd.h"

#include "Packets.h"
#include "Settings.refl.meta.h"


int main(int argc, char ** argv)
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
      printf("project_dir.txt not found and PROJECT_DIR environment variable not set\n");
      return ENODATA;
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

  if(argc < 2)
  {
    printf("StormDistUpload <target directory>\n");
    return 0;
  }

  auto project_settings_dir_path = std::filesystem::path(project_dir) / "ProjectSettings";
  auto project_settings_file = project_settings_dir_path / "ProjectDistSettings.txt";

  auto settings_file = fopen(project_settings_file.string().c_str(), "rb");
  if(settings_file == nullptr)
  {
    printf("Could not open project credentials file\n");
    return 0;
  }

  fseek(settings_file, 0, SEEK_END);
  auto settings_file_size = ftell(settings_file);
  fseek(settings_file, 0, SEEK_SET);

  auto settings_buffer = std::make_unique<char[]>(settings_file_size + 1);
  fread(settings_buffer.get(), 1, settings_file_size, settings_file);
  fclose(settings_file);

  settings_buffer[settings_file_size] = 0;

  UploadSettings upload_settings;
  if(StormReflParseJson(upload_settings, settings_buffer.get()) == false)
  {
    printf("Could not parse credentials file\n");
    return 0;
  }

  printf("Compressing files...\n");

  miniz_cpp::zip_file file;
  for(auto p : std::filesystem::recursive_directory_iterator(argv[1]))
  {
    if(std::filesystem::is_directory(p))
    {
      continue;
    }
    auto actual_path = p.path().string();
    auto rel_path = std::filesystem::relative(p, argv[1]).string();

    for (auto & c : rel_path) { if (c == '\\') c = '/'; }

    auto data_file = fopen(actual_path.c_str(), "rb");
    if(data_file == nullptr)
    {
      printf("Could not open project credentials file\n");
      return 0;
    }

    fseek(data_file, 0, SEEK_END);
    auto data_file_size = ftell(data_file);
    fseek(data_file, 0, SEEK_SET);

    std::string data_buffer;
    data_buffer.resize(data_file_size);
    fread(data_buffer.data(), 1, data_file_size, data_file);
    fclose(data_file);

    auto status = std::filesystem::status(p.path());
    char perm_str[8];
    snprintf(perm_str, sizeof(perm_str), "%04o", (int)status.permissions());

    printf("  %s %s\n", perm_str, rel_path.c_str());
    file.writestr(rel_path, data_buffer, perm_str);
  }

  std::vector<uint8_t> data;
  file.save(data);


  printf("Done zipping data of size %zd!\n\n", data.size());

  StormSockets::StormSemaphore semaphore;

  StormSockets::StormSocketInitSettings settings;
  settings.MaxConnections = 4;
  settings.NumIOThreads = 1;
  settings.NumSendThreads = 1;
  auto backend = std::make_unique<StormSockets::StormSocketBackend>(settings);

  StormSockets::StormSocketClientFrontendWebsocketSettings client_settings;
  client_settings.EventSemaphore = &semaphore;
  auto frontend = std::make_unique<StormSockets::StormSocketClientFrontendWebsocket>(client_settings, backend.get());

  StormSockets::StormSocketClientFrontendWebsocketRequestData request_data;
  request_data.m_Protocol = upload_settings.m_DistServerIdent.size() ? upload_settings.m_DistServerIdent.c_str() : nullptr;
  auto connection_id = frontend->RequestConnect(upload_settings.m_DistServerAddress.c_str(), upload_settings.m_DistServerPort, request_data);

  bool upload_completed = false;

  while(true)
  {
    semaphore.WaitOne();

    StormSockets::StormSocketEventInfo event;
    while(frontend->GetEvent(event))
    {
      switch(event.Type)
      {
      case StormSockets::StormSocketEventType::ClientConnected:
        printf("Connected...\n");
        break;
      case StormSockets::StormSocketEventType::ClientHandShakeCompleted:
        {
          printf("Uploading...\n");
          auto packet = frontend->CreateOutgoingPacket(StormSockets::StormSocketWebsocketDataType::Binary, true);

          packet.WriteInt32((int)MessageType::kUpload);

#ifdef _MSC_VER
          const char * user_name = getenv("USERNAME");
#else
          const char * user_name = getenv("USER");
#endif
          if(user_name == nullptr)
          {
            user_name = "Unknown";
          }

          UploadRequest request;
          request.m_Platform = (int)CUR_PLATFORM;
          request.m_FileSize = data.size();
          strncpy(request.m_Name, user_name, sizeof(UploadRequest::m_Name));
          request.m_Name[sizeof(UploadRequest::m_Name) - 1] = 0;

          packet.WriteByteBlock(&request, 0, sizeof(UploadRequest));
          packet.WriteByteBlock(data.data(), 0, data.size());
          frontend->FinalizeOutgoingPacket(packet);
          frontend->SendPacketToConnection(packet, connection_id);
          frontend->FreeOutgoingPacket(packet);
        }
        break;
      case StormSockets::StormSocketEventType::Data:
        {
          printf("Got upload response...\n");
          auto & reader = event.GetWebsocketReader();

          if(reader.GetDataLength() < 4 || reader.ReadInt32() != (int)MessageType::kUploadSuccess)
          {
            printf("Upload failed!\n");
          }
          else
          {
            printf("Upload success!\n");
          }

          frontend->FreeIncomingPacket(reader);
          frontend->ForceDisconnect(event.ConnectionId);
          return 0;
        }

        break;
      case StormSockets::StormSocketEventType::Disconnected:
        printf("Disconnected before upload complete\nUpload failed!\n");
        return 0;
      }
    }
  }

  return 0;
}


