#pragma once

#include <gl3w/gl3w.h>

#include "Engine/Rendering/RenderException.h"

#define CHECK_RENDER_ERRORS

#if defined(_WEB) || !defined(CHECK_RENDER_ERRORS)
#define CHECK_GL_LOAD_ERROR
#define CHECK_GL_RENDER_ERROR
#else
#define CHECK_GL_LOAD_ERROR { int glerror = glGetError(); if(glerror != GL_NO_ERROR) ReportRenderError(__FILE__, __LINE__, glerror); } //printf("%s: %d\n", __FILE__, __LINE__);
#define CHECK_GL_RENDER_ERROR { int glerror = glGetError(); if(glerror != GL_NO_ERROR) ReportRenderError(__FILE__, __LINE__, glerror); } //printf("%s: %d\n", __FILE__, __LINE__);
#endif

