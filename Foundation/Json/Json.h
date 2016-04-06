

#include "External\json\json.hpp"

using Json = nlohmann::basic_json<
  std::map,
  std::vector,
  std::string,
  bool,
  int64_t,
  uint64_t,
  float,
  std::allocator>;

