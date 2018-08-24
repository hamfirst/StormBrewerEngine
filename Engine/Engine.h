#pragma once

#include "EngineCommon.h"

bool ENGINE_EXPORT EngineInit(bool egl_mode, bool init_sdl_video);
bool ENGINE_EXPORT EngineRenderInit();
void ENGINE_EXPORT EngineUpdate();
void ENGINE_EXPORT EngineCleanup();

void ENGINE_EXPORT EngineQuit();
bool ENGINE_EXPORT EngineWantsToQuit();