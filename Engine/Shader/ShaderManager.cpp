
#include "Engine/EngineCommon.h"
#include "Engine/Shader/ShaderManager.h"
#include "Engine/Shader/DefaultShader.h"

ShaderManager g_ShaderManager;
PreMainCallList g_ShaderRegisterList;

void ShaderManager::Init()
{
  m_DefaultShader = MakeQuickShaderProgram(kDefaultVertexShader, kDefaultFragmentShader);
  g_ShaderRegisterList.CallAll();
}

void ShaderManager::Shutdown()
{
  m_DefaultShader.Destroy();
  m_Shaders.clear();
}

const ShaderProgram & ShaderManager::GetShader(uint32_t shader_name_hash)
{
  for (auto & elem : m_Shaders)
  {
    if (shader_name_hash == elem.m_ShaderNameHash)
    {
      return elem.m_Shader;
    }
  }

  return m_DefaultShader;
}

const ShaderProgram & ShaderManager::GetDefaultShader()
{
  return m_DefaultShader;
}

void ShaderManager::RegisterShader(ShaderProgram && shader_prgram, czstr shader_name)
{
  m_Shaders.push_back(ShaderInfo{ std::move(shader_prgram), crc32(shader_name) });
  m_ShaderNames.emplace_back(shader_name);
}

void ShaderManager::RegisterShader(czstr vertex_program, czstr fragment_program, czstr shader_name)
{
  RegisterShader(MakeQuickShaderProgram(vertex_program, fragment_program), shader_name);
}

const std::vector<std::string> & ShaderManager::GetShaderNames() const
{
  return m_ShaderNames;
}
