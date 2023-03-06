#pragma once

#include <StormRefl/StormRefl.h>

#include <string>
#include <vector>

static const int kDocumentServerVersion = 1;

enum class STORM_REFL_ENUM DocumentServerMessageType
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

enum class STORM_REFL_ENUM DocumentClientMessageType
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
