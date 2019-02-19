

#include <string>
#include <sstream>

#include <StormSockets/StormUrlUtil.h>

#include <hash/Hash.h>

#include <HurricaneDDS/DDSLog.h>

#include "SteamOpenIdValidatorPage.h"


SteamOpenIdValidatorPage::SteamOpenIdValidatorPage(const DDSWebsiteInterface & website_interface) :
  m_WebsiteInterface(website_interface)
{

}

void SteamOpenIdValidatorPage::HandleRequest(const std::string & method, const std::string & uri, const std::string & headers, const std::string & body)
{
  if (m_WebsiteInterface.NodeIsReady() == false)
  {
    m_WebsiteInterface.ForceDisconnect();
    return;
  }

  DDSLog::LogVerbose("Validating steam token response");
  if (crc32(method) != crc32("GET"))
  {
    m_WebsiteInterface.ForceDisconnect();
    return;
  }

  std::string path;
  std::map<std::string, std::string> args;

  if (StormSockets::DecodeURLRequest(uri.data(), path, args) == false)
  {
    m_WebsiteInterface.ForceDisconnect();
    return;
  }

  auto return_url_itr = args.find("src_url");
  if (return_url_itr == args.end())
  {
    m_WebsiteInterface.ForceDisconnect();
    return;
  }

  auto claimed_id_itr = args.find("openid.claimed_id");
  if (claimed_id_itr == args.end())
  {
    m_WebsiteInterface.ForceDisconnect();
    return;
  }

  if (claimed_id_itr->second.find("http://steamcommunity.com/openid/id/") != 0)
  {
    m_WebsiteInterface.ForceDisconnect();
    return;
  }

  if (StormReflParseJson(m_PlatformId, claimed_id_itr->second.data() + strlen("http://steamcommunity.com/openid/id/")) == false)
  {
    m_WebsiteInterface.ForceDisconnect();
    return;
  }

  m_ReturnUrl = return_url_itr->second;
  args.erase(return_url_itr);
  args["openid.mode"] = "check_authentication";

  const char * url_mode = "Content-Type: application/x-www-form-urlencoded\r\n";

  m_WebsiteInterface.CreateHttpRequest(m_ValidationRequest, DDSHttpRequest("https://steamcommunity.com/openid/login", StormSockets::EncodeURLArgs(args), url_mode),
    [this](bool success, std::string data, std::string headers) { HandleValidationResponse(success, data, headers); });
}

void SteamOpenIdValidatorPage::HandleValidationResponse(bool success, const std::string & data, const std::string & headers)
{
  if(success == false)
  {
    m_WebsiteInterface.ForceDisconnect();
    return;
  }

  std::stringstream ss;
  ss.str(data);
  std::string item;

  std::vector<std::string> elems;

  while (std::getline(ss, item)) 
  {
    elems.push_back(item);
  }

  if (elems.size() < 2)
  {
    m_WebsiteInterface.ForceDisconnect();
    return;
  }

  if (crc32(elems[0]) != crc32("ns:http://specs.openid.net/auth/2.0") ||
      crc32(elems[1]) != crc32("is_valid:true"))
  {
    m_WebsiteInterface.ForceDisconnect();
    return;
  }

  uint64_t token = m_WebsiteInterface.CreateToken(std::to_string(m_PlatformId), 0, 10);
  DDSLog::LogVerbose("Sending Token %llu\n", (unsigned long long)token);
  std::string resp_headers = "Location: " + m_ReturnUrl + "#" + std::to_string(token) + "\r\n";
  resp_headers += "Content-Length: 0\r\n";
  resp_headers += "Content-Type: text/html;charset=ISO-8859-1\r\n";
  m_WebsiteInterface.SendResponse(resp_headers.data(), "", 302, "Found");
  m_WebsiteInterface.ForceDisconnect();
}

