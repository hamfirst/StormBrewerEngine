#pragma once

#include <chrono>

using DocumentLoadCallback = Delegate<void, uint64_t, Optional<Buffer> &&, std::chrono::system_clock::time_point>;

class DocumentLoader
{
public:
  virtual void LoadDocument(czstr path, uint64_t file_hash, DocumentLoadCallback callback) = 0;
};

