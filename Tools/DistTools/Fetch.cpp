

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <iostream>
#include <filesystem>
#include <thread>
#include <chrono>

#include <miniz-cpp/zip_file.hpp>

#include "StormSockets/StormSocketBackend.h"
#include "StormSockets/StormSocketClientFrontendWebsocket.h"

#include "StormRefl/StormReflJsonStd.h"

#include "DistFetcher.h"

#include "Packets.h"
#include "Settings.refl.meta.h"


int main(int argc, char ** argv)
{
  bool download_list = true;
  int build_id = 0;

  if(argc >= 2)
  {
    build_id = atoi(argv[1]);
    download_list = false;
  }

  std::unique_ptr<DistFetcher> dist_fetcher;
  if(download_list)
  {
    dist_fetcher = std::make_unique<DistFetcher>();
  }
  else
  {
    dist_fetcher = std::make_unique<DistFetcher>(build_id);
  }

  if(dist_fetcher->GetResult().has_value() == false)
  {
    printf("Connecting to server...\n");
  }

  dist_fetcher->Sync();
  auto result = dist_fetcher->GetResult().value();

  if(result == DistFetcherResult::kDone)
  {
    if(download_list)
    {
      auto list = dist_fetcher->GetBuildInfo().value();
      if(list.size() == 0)
      {
        printf("No builds\n");
      }
      else
      {
        const char * plat = "UNK";
        for(auto & elem : list)
        {
          switch(elem.m_Platform)
          {
          case DistPlatform::kWindows:
            plat = "WIN";
            break;
          case DistPlatform::kLinux:
            plat = "LNX";
            break;
          case DistPlatform::kMac:
            plat = "MAC";
            break;
          }

          printf("  %d. %s %s %s\n", elem.m_BuildId, plat, elem.m_Date.c_str(), elem.m_Name.c_str());
        }
      }

      return 0;
    }
    else
    {
      auto build_data = dist_fetcher->GetDownloadData().value();
      if(build_data.second == 0)
      {
        printf("Build not found\n");
        return -1;
      }

      printf("Got compressed build of size %zd\n", build_data.second);
      printf("Decompressing build...\n");
      auto buffer = std::vector<uint8_t>();

      buffer.resize(build_data.second);
      memcpy(buffer.data(), build_data.first, build_data.second);

      miniz_cpp::zip_file file(buffer);
      file.printdir();

      for(auto & info : file.infolist())
      {
        std::filesystem::path dest_path(info.filename);
        dest_path = "." / dest_path;
        auto parent_path = dest_path.parent_path();

        std::vector<std::filesystem::path> paths;
        while(parent_path != ".")
        {
          paths.emplace_back(parent_path);
          parent_path = parent_path.parent_path();
        }

        for(int index = (int)paths.size() - 1; index >= 0; --index)
        {
          std::filesystem::create_directory(paths[index]);
        }

        file.extract(info, ".");

        int perms;
        sscanf(info.comment.c_str(), "%04o", &perms);

        std::filesystem::permissions(info.filename, (std::filesystem::perms)perms);
      }

      return 0;
    }
  }
  else
  {
    switch (result)
    {
    case DistFetcherResult::kProjectDirNotFound:
      printf("project_dir.txt not found and PROJECT_DIR environment variable not set\n");
      break;
    case DistFetcherResult::kProjectSettingsNotFound:
      printf("Could not open project credentials file\n");
      break;
    case DistFetcherResult::kProjectSettingsInvalid:
      printf("Could not parse credentials file\n");
      break;
    case DistFetcherResult::kConnectionFailed:
      printf("Connection failed\n");
      break;
    case DistFetcherResult::kDisconnected:
      printf("Disconnected before upload complete\n");
      break;
    case DistFetcherResult::kDownloadListFailed:
      printf("Download list failed\n");
      break;
    case DistFetcherResult::kInvalidBuildId:
      printf("Invalid build id\n");
      break;
    }

    return -1;
  }
}


