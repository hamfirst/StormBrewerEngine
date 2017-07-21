#pragma once

#ifdef EMSCRIPTEN

#include "StormWebrtcClientWeb.h"
using StormWebrtcClient = StormWebrtcClientWeb;

#else
#include "StormWebrtcClientNative.h"
using StormWebrtcClient = StormWebrtcClientNative;

#endif

