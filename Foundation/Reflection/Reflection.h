
#pragma once

#include <boost/preprocessor/variadic/size.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/stringize.hpp>

#define REFLECTION_PARENT
#ifdef REFLECTION_PARENT

struct ReflectionParentInfo
{
  void * m_Parent;
  uint32_t m_ParentType;
  uint32_t m_ParentFieldIndex;
  uint32_t m_ParentArrayIndex;
};

#define REFLECTION_PARENT_INFO \
  ReflectionParentInfo m_ReflectionInfo;

#else

#define REFLECTION_PARENT_INFO

#endif
