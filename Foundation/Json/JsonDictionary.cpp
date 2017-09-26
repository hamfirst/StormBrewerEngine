
#include "Foundation/Common.h"
#include "Foundation/Json/JsonDictionary.h"
#include "Foundation/Json/Json.h"

JsonDictionary::JsonDictionary()
{

}

JsonDictionary::~JsonDictionary()
{

}

JsonDictionary::JsonDictionary(const JsonDictionary & rhs)
{
  for (auto & elem : rhs.m_Dict)
  {
    m_Dict.emplace(std::make_pair(elem.first, JsonNameAndObject{ elem.second.m_Name, std::make_unique<Json>(*elem.second.m_Object.get()) }));
  }
}

JsonDictionary::JsonDictionary(JsonDictionary && rhs) :
  m_Dict(std::move(rhs.m_Dict))
{

}

JsonDictionary & JsonDictionary::operator = (const JsonDictionary & rhs)
{
  m_Dict.clear();
  for (auto & elem : rhs.m_Dict)
  {
    m_Dict.emplace(std::make_pair(elem.first, JsonNameAndObject{ elem.second.m_Name, std::make_unique<Json>(*elem.second.m_Object.get()) }));
  }

  return *this;
}

JsonDictionary & JsonDictionary::operator = (JsonDictionary && rhs)
{
  m_Dict = std::move(rhs.m_Dict);
  return *this;
}
