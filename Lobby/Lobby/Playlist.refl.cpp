
#include <HurricaneDDS/DDSDatabaseConnection.h>
#include <HurricaneDDS/DDSResponderCall.h>

#include <StormData/StormDataJson.h>

#include "Playlist.refl.meta.h"

Playlist::Playlist(DDSObjectInterface & obj_interface) :
        m_Interface(obj_interface)
{

}

void Playlist::Initialize()
{
  FILE * fp = fopen("casual_playlists.txt", "rt");
  if (fp != nullptr)
  {
    fseek(fp, 0, SEEK_END);
    auto size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    auto buffer = std::make_unique<char[]>(size + 1);
    fread(buffer.get(), 1, size, fp);
    fclose(fp);

    buffer[size] = 0;

    StormReflParseJson(m_CasualPlaylist, buffer.get());
  }

  fp = fopen("competitive_playlists.txt", "rt");
  if (fp != nullptr)
  {
    fseek(fp, 0, SEEK_END);
    auto size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    auto buffer = std::make_unique<char[]>(size + 1);
    fread(buffer.get(), 1, size, fp);
    fclose(fp);

    buffer[size] = 0;

    StormReflParseJson(m_CompetitivePlaylist, buffer.get());
  }
}

