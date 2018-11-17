#include "GameShared/GameSharedCommon.h"
#include "Game/GameNetworkSettings.h"

#ifdef NET_USE_WEBRTC
#ifdef _MSC_VER
#ifdef _DEBUG

#pragma comment(lib, "../x64/Debug/StormWebrtc.lib")
#pragma comment(lib, "../x64/Debug/StormWebrtcClientAPI.lib")
#pragma comment(lib, "../x64/Debug/StormWebrtcServerAPI.lib")
#pragma comment(lib, "../x64/Debug/StormNetBindingsWebrtc.lib")
#pragma comment(lib, "../x64/Debug/usrsctplib.lib")
#pragma comment(lib, "../x64/Debug/mbedtls.lib")
#pragma comment(lib, "../x64/Debug/asio.lib")

#else

#pragma comment(lib, "../x64/Release/StormWebrtc.lib")
#pragma comment(lib, "../x64/Release/StormWebrtcClientAPI.lib")
#pragma comment(lib, "../x64/Release/StormWebrtcServerAPI.lib")
#pragma comment(lib, "../x64/Release/StormNetBindingsWebrtc.lib")
#pragma comment(lib, "../x64/Release/usrsctplib.lib")
#pragma comment(lib, "../x64/Release/mbedtls.lib")
#pragma comment(lib, "../x64/Release/asio.lib")

#endif
#endif
#endif


