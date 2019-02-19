
#include "CoordinatorState.h"
#include "DataTypes.h"
#include "ProjectSettings.h"

#include <HurricaneDDS/DDSDatabaseConnection.h>
#include <HurricaneDDS/DDSDatabaseBootstrap.h>

std::unique_ptr<DDSCoordinatorState> CreateCoordinatorState(bool reset_db, const char * database_host_addr, int database_port)
{
  StormSockets::StormSocketInitSettings backend_settings;
  backend_settings.NumIOThreads = 1;
  backend_settings.NumSendThreads = 1;

  DDSDatabaseSettings database_settings;
  database_settings.DatabaseHostName = database_host_addr;
  database_settings.DatabasePort = database_port;
  database_settings.DatabaseName = kDatabaseName;
  database_settings.NumThreads = 1;

  StormSockets::StormSocketClientFrontendHttpSettings http_client_settings;

  if (reset_db)
  {
    std::vector<DDSDatabaseBoostrapCollectionInfo> additional_collections;

    DDSDatabaseBoostrapCollectionInfo gifts_collection;
    gifts_collection.m_CollectionName = "Gifts";

    additional_collections.emplace_back(gifts_collection);

    DDSDatabaseBoostrapFull(DataObjectList{}, database_settings);
    DDSDatabaseConnection connection(database_settings);

    BuiltInChannelDatabaseObject channel_data;
    channel_data.m_ChannelNameLower = "general";
    channel_data.m_ChannelInfo.m_ChannelName = "General";
    channel_data.m_ChannelInfo.m_Motd = "Welcome To Uniball!\nhttp://www.uniballhq.com";
    channel_data.m_ChannelInfo.m_RequiredAdminLevel = 0;
    connection.QueryDatabaseInsert(Channel::GetChannelKeyFromName("General"), "BuiltInChannel", StormReflEncodeJson(channel_data));

    channel_data.m_ChannelNameLower = "admin";
    channel_data.m_ChannelInfo.m_ChannelName = "Admin";
    channel_data.m_ChannelInfo.m_Motd = "Hey it's the admin channel";
    channel_data.m_ChannelInfo.m_RequiredAdminLevel = 1;
    connection.QueryDatabaseInsert(Channel::GetChannelKeyFromName("Admin"), "BuiltInChannel", StormReflEncodeJson(channel_data));

    channel_data.m_ChannelNameLower = "support";
    channel_data.m_ChannelInfo.m_ChannelName = "Support";
    channel_data.m_ChannelInfo.m_Motd = "Please ask your question and let one of our support staff get back to you";
    channel_data.m_ChannelInfo.m_RequiredAdminLevel = 0;
    connection.QueryDatabaseInsert(Channel::GetChannelKeyFromName("Support"), "BuiltInChannel", StormReflEncodeJson(channel_data));

    channel_data.m_ChannelNameLower = "vet";
    channel_data.m_ChannelInfo.m_ChannelName = "Vet";
    channel_data.m_ChannelInfo.m_Motd = "&b&lBR&pchat &rVETERANS!! &p- No steam noobs\n&rOLD SCHOOL - OLD WAYS\n\nAny old uniballer is welcome.&n&nContact &oshink&p, &oq8&p, &ofero&p for invites / app until autojoins and channel invites are implemented.";
    channel_data.m_ChannelInfo.m_RequiredAdminLevel = 0;
    connection.QueryDatabaseInsert(Channel::GetChannelKeyFromName("Vet"), "BuiltInChannel", StormReflEncodeJson(channel_data));

    channel_data.m_ChannelNameLower = "newbies";
    channel_data.m_ChannelInfo.m_ChannelName = "Newbies";
    channel_data.m_ChannelInfo.m_Motd = "&b&lWelcome New Players!!\n\n&rThis is the place to meet other new players and learn!";
    channel_data.m_ChannelInfo.m_RequiredAdminLevel = 0;
    connection.QueryDatabaseInsert(Channel::GetChannelKeyFromName("Newbies"), "BuiltInChannel", StormReflEncodeJson(channel_data));

    channel_data.m_ChannelNameLower = "europe";
    channel_data.m_ChannelInfo.m_ChannelName = "Europe";
    channel_data.m_ChannelInfo.m_Motd = ":gr::fi::ge::is::gb::no::dk::ch::mt::pl::lv::at::lu::nl::hr::rs::sk::si::ru::cz::fr::ro::md::be::de::am::az::lt::bg::hu::ie::it::pt::by::tr::al::me::mk::es::ua::ba::se::kz::ee::il::cy:";
    channel_data.m_ChannelInfo.m_RequiredAdminLevel = 0;
    connection.QueryDatabaseInsert(Channel::GetChannelKeyFromName("Europe"), "BuiltInChannel", StormReflEncodeJson(channel_data));

    channel_data.m_ChannelNameLower = "hock";
    channel_data.m_ChannelInfo.m_ChannelName = "Hock";
    channel_data.m_ChannelInfo.m_Motd = "The Hock Channel";
    channel_data.m_ChannelInfo.m_RequiredAdminLevel = 0;
    connection.QueryDatabaseInsert(Channel::GetChannelKeyFromName("Hock"), "BuiltInChannel", StormReflEncodeJson(channel_data));

    channel_data.m_ChannelNameLower = "ladder";
    channel_data.m_ChannelInfo.m_ChannelName = "Ladder";
    channel_data.m_ChannelInfo.m_Motd = "The Ladder Channel";
    channel_data.m_ChannelInfo.m_RequiredAdminLevel = 0;
    connection.QueryDatabaseInsert(Channel::GetChannelKeyFromName("Ladder"), "BuiltInChannel", StormReflEncodeJson(channel_data));

    UserDatabaseObject default_admin;
    default_admin.m_AdminLevel = 9;
    default_admin.m_Title = 0;
    default_admin.m_TitleList.EmplaceBack("UB Developer");
    default_admin.m_UserName = "NickW";
    default_admin.m_UserNameLower = "nickw";
    default_admin.m_PlatformId = 76561197970016586ULL;
    default_admin.m_IconNames.EmplaceBack("Custom Icon");
    default_admin.m_IconURLs.EmplaceBack("img/icons/1.png");
    connection.QueryDatabaseInsert(User::GetUserIdForPlatformId(76561197970016586), "User", StormReflEncodeJson(default_admin));

    default_admin.m_TitleList[0] = "UB Founder";
    default_admin.m_UserName = "StormBrewers";
    default_admin.m_UserNameLower = "stormbrewers";
    default_admin.m_PlatformId = 76561198232963580ULL;
    connection.QueryDatabaseInsert(User::GetUserIdForPlatformId(76561198232963580), "User", StormReflEncodeJson(default_admin));

    FILE * fp = fopen("veterans.txt", "rt");
    if (fp != nullptr)
    {
      fseek(fp, 0, SEEK_END);
      auto size = ftell(fp);
      fseek(fp, 0, SEEK_SET);

      auto buffer = std::make_unique<char[]>(size + 1);
      fread(buffer.get(), 1, size, fp);
      fclose(fp);

      buffer[size] = 0;

      std::vector<std::string> veterans;
      StormReflParseJson(veterans, buffer.get());

      for (auto str : veterans)
      {
        DDSKey user_id;
        StormReflParseJson(user_id, str.data());

        UserRewards gifts;
        gifts.m_Icons.emplace_back(std::make_pair("Veteran Player", "img/icons/1.png"));
        gifts.m_Icons.emplace_back(std::make_pair("BR Chat", "img/icons/br.png"));

        gifts.m_Titles.emplace_back("Veteran Player");
        gifts.m_Titles.emplace_back("Beta Tester");
        gifts.m_Titles.emplace_back("Cool Person");

        gifts.m_AutoJoins.emplace_back("Vet");

        connection.QueryDatabaseInsert(User::GetUserIdForPlatformId(user_id), "Gifts", StormReflEncodeJson(gifts));
      }
    }
  }


  StormSockets::StormSocketServerFrontendWebsocketSettings coordinator_settings;
  coordinator_settings.ListenSettings.Port = 9001;
  StormSockets::StormSocketServerFrontendWebsocketSettings lb_settings;
  lb_settings.ListenSettings.Port = 9002;

  auto coordinator = 
    std::make_unique<DDSCoordinatorState>(DataObjectList{}, SharedObjectList{}, backend_settings, coordinator_settings, http_client_settings, database_settings);

  coordinator->InitializeLoadBalancerServer(lb_settings, 0);
  return std::move(coordinator);
}

