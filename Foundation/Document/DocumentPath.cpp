
#include "Foundation\Common.h"
#include "DocumentPath.h"

static bool ValidIdentifierCharacter(std::string::value_type c)
{
  return isalnum(c) > 0;
}

static bool ValidPathCharacter(std::string::value_type c)
{
  return ValidIdentifierCharacter(c) || c == '[' || c == ']' || c == '.';
}

DocumentPath::DocumentPath(const std::string & path)
{
  int token_start = 0;
  int path_size = (int)path.size();

  bool in_index = false;

  for (int index = 0; index < path_size; index++)
  {
    if (ValidPathCharacter(path[index]) == false)
    {
      throw std::exception("invalid path (bad character)");
    }
    
    if (path[index] == '.')
    {
      if (token_start != index)
      {
        PathElement elem;
        elem.m_Data = path.substr(token_start, index);
        elem.m_Type = kFieldName;

        m_Path.push_back(elem);
      }
      else
      {
        if(index == 0 || path[index - 1] == '.')
        {
          throw std::exception("invalid path (bad field index token)");
        }
      }

      token_start = index + 1;
      continue;
    }

    if (path[index] == '[')
    {
      if (in_index == true)
      {
        throw std::exception("invalid path (bad index start token)");
      }

      PathElement elem;
      elem.m_Data = path.substr(token_start, index);
      elem.m_Type = kFieldName;

      m_Path.push_back(elem);
      in_index = true;
      continue;
    }

    if (path[index] == ']')
    {
      if (in_index == false)
      {
        throw std::exception("invalid path (bad index end token)");
      }

      PathElement elem;
      elem.m_Data = path.substr(token_start, index);
      elem.m_Type = kIndex;

      m_Path.push_back(elem);
    }
  }

  if (token_start != path.size())
  {
    if (in_index == true)
    {
      throw std::exception("invalid path (bad index value)");
    }

    PathElement elem;
    elem.m_Data = path.substr(token_start, path.size());
    elem.m_Type = kFieldName;

    m_Path.push_back(elem);
  }
}

int DocumentPath::GetSize()
{
  return (int)m_Path.size();
}

DocumentPath::PathElement & DocumentPath::operator[](int i)
{
  return m_Path[i];
}
