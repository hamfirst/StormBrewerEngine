#pragma once

#include "ProjectSettings/ProjectPerspective.h"

#if PROJECT_PERSPECTIVE == PERSPECTIVE_TOPDOWN
#define USE_Z_ORDERING
#endif

#define USE_RENDER_TARGET
//#define USE_HDR

#ifndef _WEB
//#define USE_VERTEX_ARRAY
#define REQUIRE_VERTEX_ARRAY_IN_CONTEXT
#endif



