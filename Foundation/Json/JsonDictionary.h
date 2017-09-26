#pragma once

#include <unordered_map>
#include <memory>

class Json;

struct JsonNameAndObject
{
  std::string m_Name;
  std::unique_ptr<Json> m_Object;
};


class JsonDictionary
{
public:
  JsonDictionary();
  JsonDictionary(const JsonDictionary & rhs);
  JsonDictionary(JsonDictionary && rhs);

  ~JsonDictionary();

  JsonDictionary & operator = (const JsonDictionary & rhs);
  JsonDictionary & operator = (JsonDictionary && rhs);

  using iterator = std::unordered_map<uint32_t, JsonNameAndObject>::iterator;

  decltype(auto) begin()
  {
    return m_Dict.begin();
  }

  decltype(auto) begin() const
  {
    return m_Dict.begin();
  }

  decltype(auto) end()
  {
    return m_Dict.end();
  }

  decltype(auto) end() const
  {
    return m_Dict.end();
  }

  decltype(auto) find(uint32_t key)
  {
    return m_Dict.find(key);
  }

  decltype(auto) find(uint32_t key) const
  {
    return m_Dict.find(key);
  }

  template <typename Pair>
  decltype(auto) emplace(Pair && p)
  {
    return m_Dict.emplace(std::forward<Pair>(p));
  }

  template <typename Itr>
  void erase(Itr && itr)
  {
    m_Dict.erase(std::forward<Itr>(itr));
  }

  void clear()
  {
    m_Dict.clear();
  }

private:

  std::unordered_map<uint32_t, JsonNameAndObject> m_Dict;
};


