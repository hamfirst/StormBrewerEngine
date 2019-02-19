#pragma once

#include <HurricaneDDS/DDSWebsiteInterface.h>

class SteamOpenIdValidatorPage
{
public:

  SteamOpenIdValidatorPage(const DDSWebsiteInterface & website_interface);
  void HandleRequest(const std::string & method, const std::string & uri, const std::string & headers, const std::string & body);

  void HandleValidationResponse(bool success, const std::string & data, const std::string & headers);

private:

  DDSWebsiteInterface m_WebsiteInterface;
  std::string m_ReturnUrl;

  uint64_t m_PlatformId;
  DDSDeferredCallback m_ValidationRequest;
};
