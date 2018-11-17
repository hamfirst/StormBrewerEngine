#pragma once

#include "Runtime/RuntimeCommon.h"

class PropertyFieldDatabase;

void RUNTIME_EXPORT RuntimeInit();
void RUNTIME_EXPORT RuntimeCleanup();

void RUNTIME_EXPORT RuntimeRegisterTypes(PropertyFieldDatabase & property_db);
