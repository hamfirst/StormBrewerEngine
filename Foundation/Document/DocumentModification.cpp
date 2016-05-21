
#include "Foundation\Document\DocumentModification.h"
#include "Foundation\Json\Json.h"

std::string DocumentModification::Encode() const
{
  Json json = Json::object();
  json["Path"] = m_Path.Encode();
  json["Data"] = m_Data;
  json["Type"] = (int)m_Type;
  json["Index"] = m_Index;
  return json.dump();
}

void DocumentModification::Decode(const std::string & json_data)
{
  Json json = Json::parse(json_data);
  m_Path = DocumentPath(json["Path"].get<std::string>());
  m_Data = json["Data"].get<std::string>();
  m_Type = (DocumentModificationType)json["Type"].get<int>();
  m_Index = json["Index"].get<uint32_t>();
}
