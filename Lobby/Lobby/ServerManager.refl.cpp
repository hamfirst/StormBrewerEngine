
#include <regex>
#include <algorithm>

#include <HurricaneDDS/DDSDatabaseConnection.h>
#include <HurricaneDDS/DDSResponderCall.h>
#include <HurricaneDDS/DDSEncoding.h>
#include <HurricaneDDS/DDSLog.h>
#include <HurricaneDDS/DDSRandom.h>

#include <StormData/StormDataJson.h>

#include <StormBootstrap/StormBootstrap.h>

#include <mbedtls/sha256.h>
#include <sb/vector.h>

#include "Foundation/FileSystem/Path.h"

#include "ProjectSettings/ProjectName.h"
#include "ProjectSettings/ProjectZones.h"
#include "ProjectSettings/ProjectVersion.h"
#include "ProjectSettings/ProjectPorts.h"

#include "ServerManager.refl.meta.h"
#include "GooglePlatform.refl.meta.h"
#include "Game.refl.meta.h"
#include "GameServerConnection.refl.h"

#ifdef _LINUX
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#else
#include <Windows.h>
#endif

std::string ApplyTemplate(const std::string & templ, const std::unordered_map<std::string, std::string> & repl)
{
  std::string str;
  str.reserve(templ.size() * 2);

  bool in_template = false;
  bool prev_bracket = false;

  std::string template_name;
  for(auto & c : templ)
  {
    if(in_template)
    {
      if (c == '}')
      {
        if(prev_bracket)
        {
          auto itr = repl.find(template_name);
          assert(itr != repl.end());

          str += itr->second;

          in_template = false;
          prev_bracket = false;
          template_name.clear();
        }
        else
        {
          prev_bracket = true;
        }
      }
      else
      {
        template_name += c;
        prev_bracket = false;
      }
    }
    else
    {
      if(c == '{')
      {
        if(prev_bracket)
        {
          in_template = true;
        }
        else
        {
          prev_bracket = true;
        }
      }
      else
      {
        if(prev_bracket)
        {
          str +=  "{";
        }

        str += c;
      }
    }
  }

  return str;
}

ServerManager::ServerManager(DDSObjectInterface & iface) :
  m_Interface(iface)
{
  for(int zone = 0; zone < kNumProjectZones; ++zone)
  {
    m_RequestedServersInZone.emplace_back(0);
  }
}

ServerManager::~ServerManager()
{
#ifdef ENABLE_GOOGLE_CLOUD
  mbedtls_pk_free(&m_PKContext);
#endif

  while(m_DebugServers.size() > 0)
  {
    StopDebugServer(m_DebugServers.begin()->first);
  }
}

void ServerManager::Initialize()
{
#ifdef ENABLE_GOOGLE_CLOUD
  m_ProjectNameLowercase = kProjectName;
  std::transform(m_ProjectNameLowercase.begin(), m_ProjectNameLowercase.end(), m_ProjectNameLowercase.begin(), tolower);

  StormBootstrap bootstrap;
  bootstrap.LoadConfigFile("Config/gcp_settings.txt", [&](const std::string & data)
  {
    StormReflParseJson(m_Settings, data);
  });


  bootstrap.LoadConfigFile("Config/gcp_credentials.txt", [&](const std::string & data)
  {
    StormReflParseJson(m_CredentialsInfo, data);
  });

  std::string project_dir = "/";
  bootstrap.LoadConfigFile("project_dir.txt", [&](const std::string & data)
  {
    project_dir = data;
  });

  auto ReadTemplateAsString = [&](czstr file)
  {
    std::string result;
    bootstrap.LoadConfigFile(project_dir + "/Lobby/GCPTemplates/" + file + ".template", [&](const std::string & data)
    {
      assert(!data.empty());
      result = data;
    });

    return result;
  };

  m_CreateInstanceTemplate = ReadTemplateAsString("CreateInstance");

  mbedtls_pk_init(&m_PKContext);
  int ret = mbedtls_pk_parse_key(&m_PKContext,
      (uint8_t *)m_CredentialsInfo.private_key.data(), m_CredentialsInfo.private_key.length() + 1, nullptr, 0);

  if (ret < 0)
  {
    DDSLog::LogError("pk_parse_key -0x%x\n", -ret);
  }

  auto payload = GetCloudTokenAssertion();
  bootstrap.PostUrl(m_CredentialsInfo.token_uri, "Content-Type: application/x-www-form-urlencoded\r\n", payload, [&](const std::string & resp)
  {
    HandleCloudTokenResponse(true, resp, "");
  });

  bootstrap.Run();

  assert(!m_AuthorizationHeader.empty());

  for(int index = 0; index < kNumProjectZones; ++index)
  {
    auto zone = g_ProjectZones[index];
    RequestServerList(zone, "", bootstrap);
  }

  bootstrap.Run();
#endif
}

void ServerManager::Update()
{
  CheckForTimedOutServers();
  CheckForAssignableGames();
  CheckForNewServersNeeded();
}

void ServerManager::CreateServerInstance(int zone_index)
{
  DDSLog::LogInfo("Creating server in zone %d", zone_index);
  if(zone_index == -1)
  {
    CreateDebugServer();
    return;
  }
#ifdef ENABLE_GOOGLE_CLOUD
  else
  {
    CreateCloudServerInstance(zone_index);
  }
#else
  CreateDebugServer();
#endif
}

void ServerManager::StopServerInstance(const std::string & zone, const std::string & resource_id)
{
  if(zone == "Debug")
  {
    StopDebugServer(strtoul(resource_id.c_str(), nullptr, 10));
    return;
  }
#ifdef ENABLE_GOOGLE_CLOUD
  else
  {
    StopCloudServerInstance(zone, resource_id);
  }
#else

  DDSLog::LogInfo("Destroying server in zone %s-%s", zone.c_str(), resource_id.c_str());
  StopDebugServer(strtoul(resource_id.c_str(), nullptr, 10));
#endif
}

void ServerManager::StopServerInstance(int zone_index, const std::string & resource_id)
{
  if(zone_index == -1)
  {
    StopServerInstance("Debug", resource_id);
  }
  else
  {
    StopServerInstance(g_ProjectZones[zone_index], resource_id);
  }
}

#ifdef ENABLE_GOOGLE_CLOUD
void ServerManager::RequestServerList(const std::string & zone, const std::string & page_token, StormBootstrap & bootstrap)
{
  auto url = "https://www.googleapis.com/compute/v1/projects/" + m_Settings.project_id + "/zones/" + zone + "/instances";

  if(!page_token.empty())
  {
    url += "?pageToken=" + page_token;
  }

  bootstrap.RequestUrl(url.c_str(), m_AuthorizationHeader, [this, bootstrap_ptr = &bootstrap, zone](const std::string & resp_data)
  {
    HandleServerListResponse(resp_data, zone, *bootstrap_ptr);
  });
}

void ServerManager::HandleServerListResponse(const std::string & response_data, const std::string & zone, StormBootstrap & bootstrap)
{
  GoogleInstanceList response;
  StormReflParseJson(response, response_data);

  for(auto & elem : response.items)
  {
    std::regex name_regex(m_ProjectNameLowercase + "-v" + std::to_string(kProjectVersion) + "-[0-9]*");
    if (std::regex_match(elem.name, name_regex))
    {
      PendingServer pending;
      pending.m_ResourceId = elem.id;
      pending.m_StartTime = time(nullptr);

      auto zone_pos = elem.zone.rfind('/');
      std::string zone;
      if(zone_pos != std::string::npos)
      {
        zone = elem.zone.data() + zone_pos + 1;
      }

      for(int index = 0; index < kNumProjectZones; ++index)
      {
        if(zone == g_ProjectZones[index])
        {
          pending.m_ZoneIndex = index;
          break;
        }
      }

      if(pending.m_ZoneIndex == -1)
      {
        if(!zone.empty())
        {
          // Blow up this server
          std::string url = "https://www.googleapis.com/compute/v1/projects/" + m_Settings.project_id + "/zones/" + zone + "/instances/" + pending.m_ResourceId;

          DDSHttpRequest request(url, "", m_AuthorizationHeader.c_str());
          request.SetMethod("DELETE");
          m_Interface.CreateHttpRequest(request, m_Interface.GetLocalKey(), &ServerManager::HandleStopServerResponse);
        }
      }
      else
      {
        m_PendingServers.emplace_back(std::move(pending));
      }
    }
  }

  if(!response.nextPageToken.empty())
  {
    RequestServerList(zone, response.nextPageToken, bootstrap);
  }
}

void ServerManager::RequestNewCloudToken()
{
  auto payload = GetCloudTokenAssertion();

  DDSHttpRequest request(m_CredentialsInfo.token_uri, payload, "Content-Type: application/x-www-form-urlencoded\r\n");
  m_Interface.CreateHttpRequest(request, m_Interface.GetLocalKey(), &ServerManager::HandleCloudTokenResponse);
}

void ServerManager::HandleCloudTokenResponse(bool success, std::string body, std::string headers)
{
  GoogleTokenResponse response;
  StormReflParseJson(response, body.data());

  if(response.access_token.empty())
  {
    DDSLog::LogInfo("Got invalid token");
    m_AuthorizationHeader.clear();

    m_Interface.CreateTimer(std::chrono::seconds(10), m_Interface.GetLocalKey(), &ServerManager::RequestNewCloudToken);
  }
  else
  {
    DDSLog::LogInfo("Got token response");
    m_AuthorizationHeader =
        std::string("Authorization: ") + response.token_type + " " + response.access_token + "\r\n" +
        "Content-Type: application/json\r\n";

    m_Interface.CreateTimer(std::chrono::seconds(response.expires_in - 100), m_Interface.GetLocalKey(), &ServerManager::RequestNewCloudToken);
  }
}

void ServerManager::CreateCloudServerInstance(int zone_index)
{
  std::string url = "https://www.googleapis.com/compute/v1/projects/" + m_Settings.project_id + "/zones/" + g_ProjectZones[zone_index] + "/instances";

  std::string instance_name = m_ProjectNameLowercase + "-v" + std::to_string(kProjectVersion) + "-" + std::to_string(DDSGetRandomNumber());

  std::unordered_map<std::string, std::string> params;
  params["project_id"] = m_Settings.project_id;
  params["project_id_lc"] = m_ProjectNameLowercase;
  params["project_version"] = std::to_string(kProjectVersion);
  params["machine_type"] = m_Settings.instance_type;
  params["tags"] = m_Settings.instance_tags;
  params["instance_name"] = instance_name;
  params["service_email"] = m_Settings.service_email;
  params["zone"] = g_ProjectZones[zone_index];

  auto request_body = ApplyTemplate(m_CreateInstanceTemplate, params);

  DDSHttpRequest request(url, request_body, m_AuthorizationHeader);
  m_Interface.CreateHttpRequest(request, m_Interface.GetLocalKey(), &ServerManager::HandleCreateServerResponse, zone_index);
}

void ServerManager::HandleCreateServerResponse(int zone_index, bool success, std::string body, std::string headers)
{
  GoogleInstanceCreateResponse response;
  StormReflParseJson(response, body);

  m_RequestedServersInZone[zone_index]--;
  assert(m_RequestedServersInZone[zone_index] >= 0);

  if(response.id.empty())
  {
    DDSLog::LogInfo("Failed to create server: %s", body.c_str());
    return;
  }

  PendingServer pending;
  pending.m_ResourceId = response.id;
  pending.m_StartTime = time(nullptr);
  pending.m_ZoneIndex = zone_index;

  m_PendingServers.emplace_back(std::move(pending));
}

void ServerManager::StopCloudServerInstance(const std::string & zone, const std::string & resource_id)
{
  std::string url = "https://www.googleapis.com/compute/v1/projects/" + m_Settings.project_id + "/zones/" + zone + "/instances/" + resource_id;

  DDSHttpRequest request(url, "", m_AuthorizationHeader.c_str());
  request.SetMethod("DELETE");
  m_Interface.CreateHttpRequest(request, m_Interface.GetLocalKey(), &ServerManager::HandleStopServerResponse);

  for(auto itr = m_PendingServers.begin(), end = m_PendingServers.end(); itr != end; ++itr)
  {
    if(itr->m_ResourceId == resource_id)
    {
      m_PendingServers.erase(itr);
      break;
    }
  }

  for(auto itr = m_ActiveServers.begin(), end = m_ActiveServers.end(); itr != end; ++itr)
  {
    if(itr->m_ResourceId == resource_id)
    {
      m_ActiveServers.erase(itr);
      break;
    }
  }
}

void ServerManager::HandleStopServerResponse(bool success, std::string body, std::string headers)
{

}

#endif

void ServerManager::AssignGameServer(DDSKey game_id, int zone)
{
  DDSLog::LogInfo("Requesting server game assignment in zone %d", zone);

  GameRequest request;
  request.m_GameId = game_id;
  request.m_Zone = zone;
  m_GameRequests.emplace_back(request);
}

void ServerManager::HandleServerConnected(DDSKey game_server_key, const GameServerInfo & server_info, int num_active_games)
{
  ActiveServer active_server;

  if(server_info.m_ServerZone == "Debug")
  {
    if(server_info.m_ExternalIp == "127.0.0.1")
    {
      active_server.m_ZoneIndex = -1;
    }
    else
    {
      StopServerInstance(server_info.m_ServerZone, server_info.m_ServerResourceId);
      return;
    }
  }
  else
  {
    for(int zone = 0; zone < kNumProjectZones; ++zone)
    {
      if(g_ProjectZones[zone] == server_info.m_ServerZone)
      {
        active_server.m_ZoneIndex = zone;
        break;
      }
    }

    if(active_server.m_ZoneIndex == -1)
    {
      StopServerInstance(server_info.m_ServerZone, server_info.m_ServerResourceId);
      return;
    }
  }

  active_server.m_ConnectionKey = game_server_key;
  active_server.m_RemoteIp = server_info.m_ExternalIp;
  active_server.m_RemotePort = server_info.m_ExternalPort;
  active_server.m_Name = server_info.m_ServerName;
  active_server.m_ResourceId = server_info.m_ServerResourceId;
  active_server.m_ActiveGames = num_active_games;

  m_ActiveServers.emplace_back(std::move(active_server));

  for(auto itr = m_PendingServers.begin(), end = m_PendingServers.end(); itr != end; ++itr)
  {
    if(itr->m_ResourceId == server_info.m_ServerResourceId)
    {
      m_PendingServers.erase(itr);
      break;
    }
  }

}

void ServerManager::HandleServerDisconnected(DDSKey game_server_key)
{
  for(auto itr = m_ActiveServers.begin(), end = m_ActiveServers.end(); itr != end; ++itr)
  {
    if(itr->m_ConnectionKey == game_server_key)
    {
      m_ActiveServers.erase(itr);
      break;
    }
  }
}

void ServerManager::HandleGameEnded(DDSKey game_server_key)
{
  for(auto itr = m_ActiveServers.begin(), end = m_ActiveServers.end(); itr != end; ++itr)
  {
    if(itr->m_ConnectionKey == game_server_key)
    {
      itr->m_ActiveGames--;
      assert(itr->m_ActiveGames >= 0);

      if(itr->m_ActiveGames == 0)
      {
        StopServerInstance(itr->m_ZoneIndex, itr->m_ResourceId);
      }
      break;
    }
  }
}

void ServerManager::CheckForTimedOutServers()
{
  static const int kServerTimeout = 60;

  auto timeout_time = time(nullptr) - kServerTimeout;
  auto itr = std::remove_if(m_PendingServers.begin(), m_PendingServers.end(), [&](const PendingServer & server)
  {
    if(server.m_StartTime < timeout_time)
    {
      StopServerInstance(server.m_ZoneIndex, server.m_ResourceId);
      return true;
    }

    return false;
  });

  m_PendingServers.erase(itr, m_PendingServers.end());
}

void ServerManager::CheckForAssignableGames()
{
  auto index = 0;
  while(index < (int)m_GameRequests.size())
  {
    bool assigned_server = false;

    auto & request = m_GameRequests[index];
    for (auto & server : m_ActiveServers)
    {
      if ((server.m_ZoneIndex == -1 || server.m_ZoneIndex == request.m_Zone) && server.m_ActiveGames < kMaxGamesPerServer)
      {
        server.m_ActiveGames++;
        m_GameRequests.erase(m_GameRequests.begin() + index);

        m_Interface.Call(&Game::AssignGameServer, request.m_GameId, server.m_ConnectionKey, server.m_RemoteIp, server.m_RemotePort);
        assigned_server = true;
        break;
      }
    }

    if(assigned_server == false)
    {
      ++index;
    }
  }
}

void ServerManager::CheckForNewServersNeeded()
{
  if(m_GameRequests.size() == 0)
  {
    return;
  }

#ifdef ENABLE_GOOGLE_CLOUD

  int games_in_zone[kNumProjectZones] = {};
  for(auto & elem : m_GameRequests)
  {
    games_in_zone[elem.m_Zone]++;
  }

  int pending_servers_in_zone[kNumProjectZones] = {};
  for(auto & elem : m_PendingServers)
  {
    if(elem.m_ZoneIndex != -1)
    {
      pending_servers_in_zone[elem.m_Zone]++;
    }
  }

  int servers_needed_in_zone[kNumProjectZones] = {};
  for(int index = 0; index < kNumProjectZones; ++index)
  {
    servers_needed_in_zone = (games_in_zone + (kMaxGamesPerServer - 1)) / kMaxGamesPerServer;
  }

  for(int index = 0; index < kNumProjectZones; ++index)
  {
    while(servers_needed_in_zone[index] > m_RequestedServersInZone[index] + pending_servers_in_zone)
    {
      CreateServerInstance(index);
    }
  }

#else

  int servers_needed = (m_GameRequests.size() + (kMaxGamesPerServer - 1)) / kMaxGamesPerServer;
  while(servers_needed > m_PendingServers.size())
  {
    CreateDebugServer();
  }

#endif


}

void ServerManager::CheckForExtraneousServers()
{
  for(int index = 0; index < m_ActiveServers.size(); index++)
  {
    auto & server = m_ActiveServers[index];
    if(server.m_ActiveGames == 0)
    {
      StopServerInstance(server.m_ZoneIndex, server.m_ResourceId);
      m_ActiveServers.erase(m_ActiveServers.begin() + index);
      index--;
    }
  }
}

#ifdef ENABLE_GOOGLE_CLOUD
std::string ServerManager::GetCloudTokenAssertion()
{
  auto now = time(nullptr);

  GoogleAssertionHeader assertion_header;
  assertion_header.alg = "RS256";
  assertion_header.kid = m_CredentialsInfo.private_key_id;
  assertion_header.typ = "JWT";
  auto header_str = UrlSafeBase64Encode(StormReflEncodeJson(assertion_header));

  GoogleAssertionPayload assertion_payload;
  assertion_payload.iss = m_CredentialsInfo.client_email;
  assertion_payload.scope = "https://www.googleapis.com/auth/cloud-platform";
  assertion_payload.aud = m_CredentialsInfo.token_uri;
  assertion_payload.iat = now;
  assertion_payload.exp = now + 3600;
  auto payload_str = UrlSafeBase64Encode(StormReflEncodeJson(assertion_payload));

  auto encoded_str = header_str + "." + payload_str;

  uint8_t hash[32];
  int ret = mbedtls_sha256_ret((const unsigned char *)encoded_str.data(), encoded_str.length(), hash, 0);
  if (ret < 0)
  {
    DDSLog::LogError("mbedtls_sha256_ret -0x%x\n", -ret);
  }

  uint8_t signature[512];
  size_t signature_length = sizeof(signature);

  ret = mbedtls_pk_sign(&m_PKContext, MBEDTLS_MD_SHA256, hash, sizeof(hash), signature, &signature_length, nullptr, nullptr);
  if (ret < 0)
  {
    DDSLog::LogError("mbedtls_pk_sign -0x%x\n", -ret);
  }

  encoded_str += "." + UrlSafeBase64Encode(signature, signature_length);
  auto payload = "grant_type=" + UrlEncode("urn:ietf:params:oauth:grant-type:jwt-bearer") + "&assertion=" + encoded_str;

  return payload;
}
#endif

void ServerManager::CreateDebugServer()
{
  DDSLog::LogInfo("Starting debug server");
  auto server_id = m_ServerIdAllocator.Allocate();

  PendingServer pending;
  pending.m_ResourceId = std::to_string(server_id);
  pending.m_StartTime = time(nullptr);
  pending.m_ZoneIndex = -1;
  m_PendingServers.emplace_back(pending);

  static std::string command[] =
  {
    "--external_ip=127.0.0.1",
    "--external_port=" + std::to_string(DEFAULT_GAME_PORT + server_id),
    "--id=" + pending.m_ResourceId,
    "--name=DebugServer",
    "--zone=Debug"
  };

  static const int kNumCommandArgs = sizeof(command) / sizeof(command[0]);

#ifdef _LINUX
  auto pid = fork();

  if(pid == 0)
  {
    char * args[kNumCommandArgs + 2];

    args[0] = (char *)"./ServerExe";
    for(int index = 0; index < kNumCommandArgs; ++index)
    {
      args[index + 1] = command[index].data();
    }

    args[kNumCommandArgs + 1] = nullptr;
    execv("ServerExe", &args[0]);
  }
  else
  {
    m_DebugServers.emplace(std::make_pair(server_id, pid));
  }
#else

  std::string command_line;
  for (int index = 0; index < kNumCommandArgs; ++index)
  {
    command_line += command[index];
    command_line += " ";
  }

  STARTUPINFOA startup_info = { sizeof(STARTUPINFOA) };
  PROCESS_INFORMATION proc_info;
  if (CreateProcessA("ServerExe", command_line.data(), nullptr, nullptr, false, CREATE_NEW_CONSOLE, nullptr, nullptr, &startup_info, &proc_info))
  {
    m_DebugServers.emplace(std::make_pair(server_id, proc_info.hProcess));
  }
#endif

}

void ServerManager::StopDebugServer(std::size_t server_id)
{
  auto itr = m_DebugServers.find(server_id);
  if (itr == m_DebugServers.end())
  {
    return;
  }

  DDSLog::LogInfo("Stopping debug server");
#ifdef _LINUX

  kill(itr->second, SIGTERM);

#else

  TerminateProcess(itr->second, 0);

#endif

  m_DebugServers.erase(itr);
}
