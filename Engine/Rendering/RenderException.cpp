
#include "Engine/EngineCommon.h"
#include "Engine/Rendering/RenderException.h"

#include "gl3w/gl3w.h"

RenderException::RenderException(int error)
  : m_Error(error)
{
  printf("Got render error: %d\n", error);

  switch (error)
  {
  case GL_INVALID_OPERATION:
    printf("GL_INVALID_OPERATION\n");
    break;
  case GL_INVALID_ENUM:
    printf("GL_INVALID_ENUM\n");
    break;
  case GL_INVALID_VALUE:
    printf("GL_INVALID_VALUE\n");
    break;
  }
}

void ReportRenderError(const char * file, int line, int error)
{
  FILE * fp = fopen("exception.log", "wt");
  fprintf(fp, "Render exception: %s:%d - %d", file, line, error);
}
