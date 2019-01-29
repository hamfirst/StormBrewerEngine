

#include <cstdio>
#include <cstdlib>
#include <cstring>

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
  auto project_dir = getenv("PROJECT_DIR");
  if(project_dir == nullptr)
  {
    printf("PROJECT_DIR environment variable not set\n");
  }

  if(argc < 2)
  {
    printf("StormDistUpload <target directory>\n");
    return 0;
  }

  auto project_settings_dir_path = std::filesystem::path(project_dir) / "ProjectSettings";
  auto project_settings_file = project_settings_dir_path / "ProjectCredentials.txt";

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
    auto str = p.path().string();
    printf("  %s\n", str.c_str());
    file.write(str);
  }

  std::vector<uint8_t> data;
  file.save(data);

  printf("Testing zip integrity\n");
  miniz_cpp::zip_file test_file(data);
  test_file.printdir();


  printf("Done zipping data of size %zd!\n\n", data.size());
  auto test_out_file = fopen("DistUpload.zip", "wb");
  fwrite(data.data(), data.size(), 1, test_out_file);
  fclose(test_out_file);

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

          const char * user_name = getenv("USERNAME");
          if(user_name == nullptr)
          {
            user_name = "Unknown";
          }

          UploadRequest request;
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
            printf("Upload failed\n");
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
        printf("Disconnected before upload complete\n");
        return 0;
      }
    }
  }

  return 0;
}


