#pragma once

#include "json\json.hpp"

enum class DocumentModificationType
{
  kSet,
  kDelete,
};

class Document
{

private:
  nlohmann::json m_Root;
};
