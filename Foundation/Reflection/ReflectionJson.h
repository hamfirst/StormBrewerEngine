
#include "Foundation\Common.h"

#include <json\json.hpp>


template <typename T, typename std::enable_if<
  std::is_arithmetic<T>::value ||
  std::is_same<T, r_string>::value
>::type * = 0>
void decode_json(T & value, nlohmann::json & j)
{
  value = j;
}

template <typename T, typename std::enable_if<
  std::is_class<T>::value && T::is_reflectable
>::type * = nullptr>
void decode_json(T & value, nlohmann::json & j)
{
  member_json_decoder_visitor decoder(j);
  visit_each(value, decoder);
}

template <typename T, typename std::enable_if<
  std::is_class<T>::value && T::is_enum
>::type * = 0>
void decode_json(T & value, nlohmann::json & j)
{
  value = T::_from_string(j.get<std::string>().data());
}

template <class T>
void decode_json(r_list<T> & value, nlohmann::json & j)
{
  value.clear();
  value.reserve(j.size());
  for (auto t : j)
  {
    T new_val;
    decode_json(new_val, t);

    value.push_back(new_val);
  }
}

template <class T>
void decode_json(r_dictionary<T> & value, nlohmann::json & j)
{
  value.clear();
  value.reserve(j.size());
  for (nlohmann::json::iterator it = j.begin(); it != j.end(); it++)
  {
    T new_val;
    decode_json(new_val, it.value());

    value[it.value().get<r_hash>()] = new_val;
  }
}

struct member_json_decoder_visitor
{
  member_json_decoder_visitor(nlohmann::json & value)
    : m_Value(value)
  {

  }

  template <class FieldData, class MemType>
  void operator()(FieldData f)
  {
    decode_json(f.get(), m_Value[f.name()]);
  }

public:
  nlohmann::json & m_Value;
};

template <typename T, typename std::enable_if<
  std::is_arithmetic<T>::value ||
  std::is_same<T, r_string>::value
>::type * = 0>
nlohmann::json encode_json(const T & value)
{
  return value;
}

template <typename T, typename std::enable_if<
  std::is_class<T>::value && T::is_reflectable
>::type * = nullptr>
nlohmann::json encode_json(const T & value)
{
  nlohmann::json j_value;
  member_json_encoder_visitor encoder(j_value);

  visit_each(value, encoder);
  return j_value;
}

template <typename T, typename std::enable_if<
  std::is_class<T>::value && T::is_enum
>::type * = 0>
nlohmann::json encode_json(const T & value)
{
  return value._to_string();
}

template <class T>
nlohmann::json encode_json(const r_list<T> & value)
{
  nlohmann::json j_value;
  for (auto t : value)
  {
    j_value.push_back(encode_json(t));
  }

  return j_value;
}

template <class T>
nlohmann::json encode_json(const r_dictionary<T> & value)
{
  nlohmann::json j_value;
  for (std::pair<r_hash, T> t : value)
  {
    j_value[t.first] = t.second;
  }

  return j_value;
}

struct member_json_encoder_visitor
{
  member_json_encoder_visitor(nlohmann::json & value)
    : m_Value(value)
  {
  
  }

  template <class FieldData, class MemType>
  void operator()(FieldData f)
  {
    m_Value[f.name()] = encode_json(f.get());
  }

public:
  nlohmann::json & m_Value;
};

