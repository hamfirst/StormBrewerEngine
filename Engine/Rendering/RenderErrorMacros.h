#pragma once

#include <gl3w/gl3w.h>

#include "Engine/Rendering/RenderException.h"

#define CHECK_GL_LOAD_ERROR m_LoadError = glGetError(); if(m_LoadError != GL_NO_ERROR) return;
#define CHECK_GL_RENDER_ERROR { int glerror = glGetError(); if(glerror != GL_NO_ERROR) ReportRenderError(__FILE__, __LINE__, glerror); }

