

#include <HurricaneDDS/DDSDatabaseConnection.h>
#include <HurricaneDDS/DDSResponderCall.h>
#include <HurricaneDDS/DDSEncoding.h>
#include <HurricaneDDS/DDSLog.h>

#include <StormData/StormDataJson.h>

#include <StormBootstrap/StormBootstrap.h>

#include <mbedtls/sha256.h>

#include "ProjectSettings/ProjectZones.h"

#include "ServerManager.refl.meta.h"
#include "GooglePlatform.refl.meta.h"

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
          if(itr != repl.end())
          {
            str += itr->second;
          }

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

}

ServerManager::~ServerManager()
{
  mbedtls_pk_free(&m_PKContext);
}

void ServerManager::Initialize()
{
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

  bootstrap.LoadConfigFile(project_dir + "/ProjectSettings/ProjectName.txt", [&](const std::string & data)
  {
    m_ProjectName = data;
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

  auto payload = GetTokenAssertion();
  bootstrap.PostUrl(m_CredentialsInfo.token_uri, "Content-Type: application/x-www-form-urlencoded\r\n", payload, [&](const std::string & resp)
  {
    HandleTokenResponse(true, resp, "");
  });

  bootstrap.Run();

  assert(!m_AuthorizationHeader.empty());

  for(int index = 0; index < g_NumProjectZones; ++index)
  {
    auto zone = g_ProjectZones[index];
    auto url = "https://www.googleapis.com/compute/v1/projects/" + m_Settings.project_id + "/zones/" + zone[index] + "/instances";

    bootstrap.RequestUrl(url.c_str(), m_AuthorizationHeader, [&](const std::string & resp)
    {
      // Do something with this?

      // Request a second page if necessary
    });
  }
}

void ServerManager::RequestNewToken()
{
  auto payload = GetTokenAssertion();

  DDSHttpRequest request(m_CredentialsInfo.token_uri, payload, "Content-Type: application/x-www-form-urlencoded\r\n");
  m_Interface.CreateHttpRequest(request, m_Interface.GetLocalKey(), &ServerManager::HandleTokenResponse);
}

void ServerManager::HandleTokenResponse(bool success, std::string body, std::string headers)
{
  GoogleTokenResponse response;
  StormReflParseJson(response, body.data());

  if(response.access_token.empty())
  {
    DDSLog::LogInfo("Got invalid token");
    m_AuthorizationHeader.clear();

    m_Interface.CreateTimer(std::chrono::seconds(10), m_Interface.GetLocalKey(), &ServerManager::RequestNewToken);
  }
  else
  {
    DDSLog::LogInfo("Got token response");
    m_AuthorizationHeader =
        std::string("Authorization: ") + response.token_type + " " + response.access_token + "\r\n" +
        "Content-Type: application/json\r\n";

    m_Interface.CreateTimer(std::chrono::seconds(response.expires_in - 100), m_Interface.GetLocalKey(), &ServerManager::RequestNewToken);
  }
}

void ServerManager::CreateServerInstance(const std::string & zone)
{
  std::string url = "https://www.googleapis.com/compute/v1/projects/" + m_Settings.project_id + "/zones/" + zone + "/instances";

}

std::string ServerManager::GetTokenAssertion()
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