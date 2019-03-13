

#include <HurricaneDDS/DDSDatabaseConnection.h>
#include <HurricaneDDS/DDSResponderCall.h>

#include <StormData/StormDataJson.h>

#include "ServerManager.refl.meta.h"

#include <string_view>

#include <stdio.h>

ServerManager::ServerManager(DDSObjectInterface & iface) :
  m_Interface(iface)
{
  FILE * fp = fopen("gcp.json", "rb");
  if(fp != nullptr)
  {
    fseek(fp, SEEK_END, 0);
    auto len = ftell(fp);
    fseek(fp, SEEK_SET, 0);

    auto buffer = std::make_unique<char[]>(len);
    fread(buffer.get(), len, 1, fp);

    StormReflParseJson(m_CredentialsInfo, std::string_view(buffer.get(), len));
  }
}



void ServerManager::RequestNewToken()
{

}
