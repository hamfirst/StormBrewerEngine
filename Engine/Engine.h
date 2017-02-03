#pragma once


bool EngineInit(bool egl_mode);
bool EngineRenderInit();
void EngineUpdate();
void EngineCleanup();

bool EngineWantsToQuit();
