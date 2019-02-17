#pragma once

#include <StormRefl/StormRefl.h>

#include <string>
#include <vector>

static const int kDocumentServerVersion = 1;

enum STORM_REFL_ENUM class DocumentServerMessageType
{
  kUnknown,
  kNew,
  kOpen,
  kClose,
  kDelete,
  kChange,
  kSave,
  kUndo,
  kRedo,
  kShutdown,
};

enum STORM_REFL_ENUM class DocumentClientMessageType
{
  kUnknown,
  kNewFileError,
  kOpenFileError,
  kCheckoutError,
  kDocumentState,
  kDocumentClosed,
  kChange,
  kChangeOk,
  kChangeLinks,
};
