
#pragma once

#include <boost/preprocessor/variadic/size.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/stringize.hpp>

#define REFLECTION_CHANGE_NOTIFIER
#ifdef REFLECTION_CHANGE_NOTIFIER

class DocumentPath;

struct ReflectionParentInfo
{
  ReflectionParentInfo * m_ParentInfo = nullptr;
  Hash m_ParentType = 0;
  uint16_t m_ParentIndex = 0;
  uint16_t m_Modified = 0;
  void(*m_ChangeListener)(const DocumentPath & path, const std::string & json_data) = nullptr;
};

#define REFLECTION_CHANGE_NOTIFIER_INFO \
  ReflectionParentInfo m_ReflectionInfo;



#else

#define REFLECTION_CHANGE_NOTIFIER_INFO

#endif
