#pragma once

#include "EngineCommon.h"

bool ENGINE_EXPORT EngineInit(bool egl_mode);
bool ENGINE_EXPORT EngineRenderInit();
void ENGINE_EXPORT EngineUpdate();
void ENGINE_EXPORT EngineCleanup();

bool ENGINE_EXPORT EngineWantsToQuit();
