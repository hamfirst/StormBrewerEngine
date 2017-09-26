
#include "Foundation/Common.h"
#include "Foundation/Json/JsonArray.h"
#include "Foundation/Json/Json.h"

JsonArray::JsonArray()
{

}

JsonArray::~JsonArray()
{

}

JsonArray::JsonArray(const JsonArray & rhs)
{
  for (auto & elem : rhs.m_Array)
  {
    m_Array.emplace_back(std::make_unique<Json>(*elem.get()));
  }
}

JsonArray::JsonArray(JsonArray && rhs) :
  m_Array(std::move(rhs.m_Array))
{

}

JsonArray & JsonArray::operator = (const JsonArray & rhs)
{
  m_Array.clear();
  for (auto & elem : rhs.m_Array)
  {
    m_Array.emplace_back(std::make_unique<Json>(*elem.get()));
  }

  return *this;
}

JsonArray & JsonArray::operator = (JsonArray && rhs)
{
  m_Array = std::move(rhs.m_Array);
  return *this;
}
