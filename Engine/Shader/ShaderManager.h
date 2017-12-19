#pragma once

#include "Foundation/CallList/CallList.h"

#include "Engine/Rendering/ShaderProgram.h"
#include "Engine/Rendering/VertexArray.h"

class ENGINE_EXPORT ShaderManager
{
public:

  ShaderProgram & GetShader(uint32_t shader_name_hash);
  ShaderProgram & GetDefaultWorldSpaceShader();
  ShaderProgram & GetDefaultScreenSpaceShader();

  void RegisterShader(ShaderProgram && shader_prgram, czstr shader_name);
  void RegisterShader(czstr vertex_program, czstr fragment_program, czstr shader_name);

  const std::vector<std::string> & GetShaderNames() const;

protected:

  friend bool EngineRenderInit();
  friend void EngineCleanup();

  void Init();
  void Shutdown();

private:

  ShaderProgram m_DefaultShader;

  struct ShaderInfo
  {
    ShaderProgram m_Shader;
    uint32_t m_ShaderNameHash;
  };

  std::vector<ShaderInfo> m_Shaders;
  std::vector<std::string> m_ShaderNames;
};

extern ENGINE_EXPORT ShaderManager g_ShaderManager;
extern ENGINE_EXPORT PreMainCallList g_ShaderRegisterList;
