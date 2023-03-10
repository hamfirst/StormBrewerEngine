#pragma once

#include <filesystem>

using DocumentLoadCallback = Delegate<void, uint32_t, void *, std::size_t, time_t>;

class DocumentLoader
{
public:
  virtual void LoadDocument(czstr path, uint32_t file_hash, DocumentLoadCallback callback) = 0;
};

