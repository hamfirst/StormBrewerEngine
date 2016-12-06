#pragma once

using DocumentLoadRequest = Handle;
using DocumentLoadCallback = Delegate<void, uint64_t, DocumentLoadRequest, Optional<Buffer> &>;

class DocumentLoader
{
public:
  virtual DocumentLoadRequest LoadDocument(czstr path, uint64_t file_hash, DocumentLoadCallback callback) = 0;
};

