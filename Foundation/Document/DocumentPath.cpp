
#include "Foundation\Common.h"
#include "Foundation\Document\DocumentPath.h"

static bool ValidIdentifierCharacter(std::string::value_type c)
{
  return isalnum(c) > 0 || c == '_';
}

static bool ValidPathCharacter(std::string::value_type c)
{
  return ValidIdentifierCharacter(c) || c == '[' || c == ']' || c == '.' || c == '-';
}

DocumentPath::DocumentPath(const std::string & path)
{
  int token_start = 0;
  int path_size = (int)path.size();

  if (path_size == 0)
  {
    throw std::exception("invalid path (empty)");
  }

  bool in_index = false;
  bool completed_field = false;
  bool completed_index = false;

  for (int index = 0; index < path_size; index++)
  {
    if (ValidPathCharacter(path[index]) == false)
    {
      throw std::exception("invalid path (bad character)");
    }
    
    if (path[index] == '.')
    {
      if (in_index)
      {
        throw std::exception("invalid path (bad field index token)");
      }

      if (token_start != index)
      {
        if (completed_index)
        {
          throw std::exception("invalid path (bad field index token)");
        }

        PathElement elem;
        elem.m_Data = path.substr(token_start, index - -token_start);
        elem.m_Type = kFieldName;

        m_Path.push_back(elem);
      }
      else
      {
        if(completed_index == false || index == 0 || path[index - 1] == '.')
        {
          throw std::exception("invalid path (bad field index token)");
        }
      }

      completed_field = true;
      token_start = index + 1;
      continue;
    }

    if (path[index] == '[')
    {
      if (in_index == true || completed_field)
      {
        throw std::exception("invalid path (bad index start token)");
      }

      PathElement elem;
      elem.m_Data = path.substr(token_start, index - token_start);
      elem.m_Type = kFieldName;

      m_Path.push_back(elem);
      in_index = true;
      token_start = index + 1;
      continue;
    }

    if (path[index] == ']')
    {
      if (in_index == false || completed_field || index == token_start)
      {
        throw std::exception("invalid path (bad index end token)");
      }

      PathElement elem;
      elem.m_Data = path.substr(token_start, index - token_start);
      if (isdigit(elem.m_Data[0]) || elem.m_Data[0] == '-')
      {
        int elem_size = (int)elem.m_Data.size();
        
        for(int subindex = 1; subindex < elem_size; subindex++)
        {
          if (!isdigit(elem.m_Data[subindex]))
          {
            throw std::exception("invalid path (not a number)");
          }
        }

        elem.m_Type = kIntIndex;
      }
      else
      {
        elem.m_Type = kStringIndex;
      }

      m_Path.push_back(elem);
      in_index = false;
      token_start = index + 1;
      completed_index = true;
      continue;
    }

    completed_field = false;
  }

  if (completed_field || in_index)
  {
    throw std::exception("invalid path (bad field completion)");
  }

  if (token_start != path.size())
  {
    if (in_index == true)
    {
      throw std::exception("invalid path (bad index value)");
    }

    PathElement elem;
    elem.m_Data = path.substr(token_start, path.size() - token_start);
    elem.m_Type = kFieldName;

    m_Path.push_back(elem);
  }
}

int DocumentPath::GetSize() const
{
  return (int)m_Path.size();
}

const DocumentPath::PathElement & DocumentPath::operator[](int i) const
{
  return m_Path[i];
}
