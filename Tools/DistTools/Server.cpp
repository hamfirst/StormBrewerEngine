

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <iostream>
#include <filesystem>

#include "StormSockets/StormSocketBackend.h"
#include "StormSockets/StormSocketServerFrontendWebsocket.h"

#include "StormRefl/StormReflJsonStd.h"

#include "Settings.refl.meta.h"
#include "Packets.h"

static const int kMaxClients = 16;
static const int kMaxBuilds = 10;

int main(int argc, char ** argv)
{
  printf("Loading settings...\n");
  auto settings_file = fopen("ProjectCredentials.txt", "rb");
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

  ServerSettings server_settings;
  if(StormReflParseJson(server_settings, settings_buffer.get()) == false)
  {
    printf("Could not parse credentials file\n");
    return 0;
  }

  std::error_code ec;
  std::filesystem::create_directory("builds", ec);

  StormSockets::StormSemaphore semaphore;

  StormSockets::StormSocketInitSettings settings;
  settings.MaxConnections = kMaxClients;
  settings.NumIOThreads = 4;
  settings.NumSendThreads = 4;
  auto backend = std::make_unique<StormSockets::StormSocketBackend>(settings);

  StormSockets::StormSocketServerFrontendWebsocketSettings websocket_settings;
  websocket_settings.EventSemaphore = &semaphore;
  websocket_settings.ListenSettings.Port = server_settings.m_DistServerPort;
  websocket_settings.Protocol = server_settings.m_DistServerIdent.size() ? server_settings.m_DistServerIdent.c_str() : nullptr;
  auto frontend = std::make_unique<StormSockets::StormSocketServerFrontendWebsocket>(websocket_settings, backend.get());

  printf("Loading data...\n");
  struct BuildData
  {
    std::string m_Name;
    std::string m_Filename;
    StormSockets::StormWebsocketMessageWriter m_Packet;
  };

  std::unordered_map<int, BuildData> build_db;
  int next_build_id = 1;

  for(auto & p : std::filesystem::directory_iterator("builds"))
  {
    auto data_file = fopen(p.path().string().c_str(), "rb");
    if(data_file)
    {

      fseek(data_file, 0, SEEK_END);
      auto data_file_size = ftell(data_file);
      fseek(data_file, 0, SEEK_SET);

      auto data_buffer = std::make_unique <char[]>(data_file_size);
      fread(data_buffer.get(), 1, data_file_size, data_file);
      fclose(data_file);

      auto packet = frontend->CreateOutgoingPacket(StormSockets::StormSocketWebsocketDataType::Binary, true);
      packet.WriteByteBlock(data_buffer.get(), 0, data_file_size);
      frontend->FinalizeOutgoingPacket(packet);

      BuildData build_data;
      build_data.m_Name = p.path().stem().string();
      build_data.m_Filename = p.path().string();
      build_data.m_Packet = packet;
      build_db.emplace(std::make_pair(next_build_id, std::move(build_data)));

      next_build_id++;

      printf("  Adding build %s\n", p.path().string().c_str());
    }
  }

  printf("Starting server\n");

  while(true)
  {
    semaphore.WaitOne();

    StormSockets::StormSocketEventInfo event;
    while(frontend->GetEvent(event))
    {
      switch(event.Type)
      {
      case StormSockets::StormSocketEventType::ClientConnected:
        printf("Client %d Connected...\n", event.ConnectionId.GetIndex());
        break;
      case StormSockets::StormSocketEventType::ClientHandShakeCompleted:
        printf("Client %d Established\n", event.ConnectionId.GetIndex());
        break;
      case StormSockets::StormSocketEventType::Data:
        printf("Got client request from %d...\n", event.ConnectionId.GetIndex());

        {
          auto & reader = event.GetWebsocketReader();
          auto data_len = reader.GetDataLength();
          if (data_len < 4)
          {
            printf("Invalid server request (no type)\n");
            frontend->FreeIncomingPacket(reader);
            frontend->ForceDisconnect(event.ConnectionId);
            continue;
          }

          auto type = (MessageType)reader.ReadInt32();
          data_len -= 4;

          if(type == MessageType::kUpload)
          {
            UploadRequest req = {};
            if(data_len < sizeof(UploadRequest))
            {
              printf("Invalid server request (no upload req)\n");
              frontend->FreeIncomingPacket(reader);
              frontend->ForceDisconnect(event.ConnectionId);
              continue;
            }

            reader.ReadByteBlock(&req, sizeof(UploadRequest));
            data_len -= sizeof(UploadRequest);
            if(data_len != req.m_FileSize)
            {
              printf("Invalid server request (incorrect file size)\n");
              frontend->FreeIncomingPacket(reader);
              frontend->ForceDisconnect(event.ConnectionId);
              continue;
            }

            auto buffer = std::make_unique<uint8_t[]>(req.m_FileSize);
            reader.ReadByteBlock(buffer.get(), req.m_FileSize);

            char file_name[256];
            snprintf(file_name, sizeof(file_name), "%zd_%s", time(nullptr), &req.m_Name[0]);

            auto path = std::filesystem::path("builds") / file_name;
            auto write_file = fopen(path.string().c_str(), "wb");
            if(write_file)
            {
              fwrite(buffer.get(), req.m_FileSize, 1, write_file);
              fclose(write_file);
            }

            auto packet = frontend->CreateOutgoingPacket(StormSockets::StormSocketWebsocketDataType::Binary, true);
            packet.WriteByteBlock(buffer.get(), 0, req.m_FileSize);
            frontend->FinalizeOutgoingPacket(packet);

            BuildData build_data;
            build_data.m_Name = path.stem().string();
            build_data.m_Filename = path.string();
            build_data.m_Packet = packet;
            build_db.emplace(std::make_pair(next_build_id, std::move(build_data)));

            next_build_id++;

            if(build_db.size() > kMaxBuilds)
            {
              auto oldest_id = 100000000;
              for(auto & elem : build_db)
              {
                oldest_id = std::min(oldest_id, elem.first);
              }

              auto & elem = build_db[oldest_id];
              frontend->FreeOutgoingPacket(elem.m_Packet);

              std::filesystem::remove(elem.m_Filename);
              build_db.erase(oldest_id);
            }

            auto response = frontend->CreateOutgoingPacket(StormSockets::StormSocketWebsocketDataType::Binary, true);
            response.WriteInt32((int)MessageType::kUploadSuccess);
            frontend->FinalizeOutgoingPacket(response);
            frontend->SendPacketToConnection(response, event.ConnectionId);
            frontend->FreeOutgoingPacket(response);

            printf("Added new build %s of size %d\n", path.string().c_str(), req.m_FileSize);
          }
          else if(type == MessageType::kDownloadList)
          {
            printf("Sending build list\n");

            auto response = frontend->CreateOutgoingPacket(StormSockets::StormSocketWebsocketDataType::Binary, true);
            response.WriteInt32(build_db.size());

            for(auto & elem : build_db)
            {
              DownloadList info;
              info.m_Id = elem.first;
              strncpy(info.m_Name, elem.second.m_Name.c_str(), sizeof(DownloadList::m_Name));
              info.m_Name[sizeof(DownloadList::m_Name) - 1] = 0;

              printf("  build %d: %s\n", elem.first, info.m_Name);

              response.WriteByteBlock(&info, 0, sizeof(DownloadList));
            }

            frontend->FinalizeOutgoingPacket(response);
            frontend->SendPacketToConnection(response, event.ConnectionId);
            frontend->FreeOutgoingPacket(response);
          }
          else if(type == MessageType::kDownload)
          {
            if (data_len < 4)
            {
              printf("Invalid server request\n");
              frontend->FreeIncomingPacket(reader);
              frontend->ForceDisconnect(event.ConnectionId);
              continue;
            }

            auto id = reader.ReadInt32();
            data_len -= 4;

            if(id == 0)
            {
              auto newest_id = 0;
              for(auto & elem : build_db)
              {
                newest_id = std::max(newest_id, elem.first);
              }

              id = newest_id;
            }

            printf("Sending build %d\n", id);

            auto itr = build_db.find(id);
            if(itr == build_db.end())
            {
              auto response = frontend->CreateOutgoingPacket(StormSockets::StormSocketWebsocketDataType::Binary, true);
              frontend->FinalizeOutgoingPacket(response);
              frontend->SendPacketToConnection(response, event.ConnectionId);
              frontend->FreeOutgoingPacket(response);
            }
            else
            {
              frontend->SendPacketToConnection(itr->second.m_Packet, event.ConnectionId);
            }
          }

          frontend->FreeIncomingPacket(reader);
        }

        break;
      case StormSockets::StormSocketEventType::Disconnected:
        printf("Client disconnected\n");
        frontend->FinalizeConnection(event.ConnectionId);
        break;
      }
    }
  }

  return 0;
}


