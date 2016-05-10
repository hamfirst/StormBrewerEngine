
#pragma once

#include <boost/preprocessor/variadic/size.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/stringize.hpp>

#define REFLECTION_PARENT
#ifdef REFLECTION_PARENT

class DocumentPath;

struct ReflectionParentInfo
{
  ReflectionParentInfo * m_ParentInfo = nullptr;
  uint32_t m_ParentType = 0;
  uint32_t m_ParentIndex = 0;
  void(*m_ChangeListener)(const DocumentPath & path, const std::string & json_data) = nullptr;
};

#define REFLECTION_PARENT_INFO \
  ReflectionParentInfo m_ReflectionInfo;



#else

#define REFLECTION_PARENT_INFO

#endif
