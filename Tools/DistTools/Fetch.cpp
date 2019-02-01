

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

  bool download_list = true;
  int build_id = 0;

  if(argc >= 2)
  {
    if(!strcmp(argv[1], "--latest"))
    {
      download_list = false;
      build_id = 0;
    }
    else
    {
      build_id = atoi(argv[1]);
      if(build_id > 0)
      {
        download_list = false;
      }
    }
  }

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

  bool connected = false;

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
        connected = true;
        break;
      case StormSockets::StormSocketEventType::ClientHandShakeCompleted:
        {
          auto packet = frontend->CreateOutgoingPacket(StormSockets::StormSocketWebsocketDataType::Binary, true);

          if(download_list)
          {
            printf("Downloading list...\n");
            packet.WriteInt32((int)MessageType::kDownloadList);
            frontend->FinalizeOutgoingPacket(packet);
            frontend->SendPacketToConnection(packet, connection_id);
            frontend->FreeOutgoingPacket(packet);
          }
          else
          {
            printf("Downloading build...\n");
            packet.WriteInt32((int)MessageType::kDownload);
            packet.WriteInt32(build_id);
            frontend->FinalizeOutgoingPacket(packet);
            frontend->SendPacketToConnection(packet, connection_id);
            frontend->FreeOutgoingPacket(packet);
          }
        }
        break;
      case StormSockets::StormSocketEventType::Data:

        {
          auto & reader = event.GetWebsocketReader();
          if (download_list)
          {
            int data_length = reader.GetDataLength();
            if(data_length < 4)
            {
              printf("Download list failed");
              return 0;
            }

            int num_builds = reader.ReadInt32();
            data_length -= 4;

            if(num_builds == 0)
            {
              printf("No builds\n");
            }

            for(int index = 0; index < num_builds; ++index)
            {
              if(data_length < sizeof(DownloadList))
              {
                printf("Download list failed\n");
                return 0;
              }

              DownloadList list_elem;
              reader.ReadByteBlock(&list_elem, sizeof(DownloadList));
              data_length -= sizeof(DownloadList);

              time_t t = atoi(list_elem.m_Name);
              auto time_info = localtime(&t);

              const char * desc = strstr(list_elem.m_Name, "_");
              if(desc == nullptr)
              {
                desc = "Unknown";
              }
              else
              {
                desc++;
              }

              char timestr[256];
              strftime(timestr, sizeof(timestr), "%m/%d/%y %H:%M:%S", time_info);

              printf("%d. %s %s\n\n", list_elem.m_Id, timestr, desc);
            }
          }
          else
          {
            if(reader.GetDataLength() > 0)
            {
              printf("Got compressed build of size %d\n", reader.GetDataLength());
              printf("Decompressing build...\n");
              auto buffer_len = reader.GetDataLength();
              auto buffer = std::vector<uint8_t>();

              buffer.resize(buffer_len);
              reader.ReadByteBlock(buffer.data(), reader.GetDataLength());

              miniz_cpp::zip_file file(buffer);
              file.printdir();
              file.extractall(".");
            }
            else
            {
              printf("Invalid build id\n");
            }
          }

          frontend->FreeIncomingPacket(reader);
        }

        frontend->ForceDisconnect(event.ConnectionId);
        return 0;
      case StormSockets::StormSocketEventType::Disconnected:
        if(connected)
        {
          printf("Disconnected before upload complete\n");
        }
        else
        {
          printf("Connection failed\n");
        }
        return 0;
      }
    }
  }

  return 0;
}


