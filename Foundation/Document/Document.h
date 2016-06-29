#pragma once


#include "Foundation\Json\Json.h"

struct DocumentModification;

class Document final
{
public:
  Document();
  Document(const std::string & json_data);
  Document(czstr json_data);

  void ApplyDocumentModification(const DocumentModification & mod, std::vector<DocumentModification> & reverse_operations);

  const Json & GetJsonData() const { return m_Root; }
private:
  Json m_Root;
};
