#pragma once

#include <vector>
#include <memory>

class Json;

class JsonArray
{
public:
  JsonArray();
  JsonArray(const JsonArray & rhs);
  JsonArray(JsonArray && rhs);

  ~JsonArray();

  JsonArray & operator = (const JsonArray & rhs);
  JsonArray & operator = (JsonArray && rhs);

  decltype(auto) begin()
  {
    return m_Array.begin();
  }

  decltype(auto) begin() const
  {
    return m_Array.begin();
  }

  decltype(auto) end()
  {
    return m_Array.end();
  }

  decltype(auto) end() const
  {
    return m_Array.end();
  }

  decltype(auto) operator[](std::size_t index)
  {
    return m_Array[index];
  }

  decltype(auto) operator[](std::size_t index) const
  {
    return m_Array[index];
  }

  template <typename ... Args>
  decltype(auto) emplace_back(Args && ... args)
  {
    return m_Array.emplace_back(std::forward<Args>(args)...);
  }

  decltype(auto) size() const
  {
    return m_Array.size();
  }
private:
  std::vector<std::unique_ptr<Json>> m_Array;
};


