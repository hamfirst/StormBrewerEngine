#pragma once

#ifdef _MSC_VER

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef _SCL_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
#endif

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

#pragma warning(disable:4503)

#endif

#include <new>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

#include <cstdint>

#include <gsl/gsl.h>

#include <hash/Hash.h>
#include <hash/Hash64.h>

#include <StormData/StormDataTypes.h>

#include "Foundation/Math/Math.h"
#include "Foundation/Time/Time.h"
#include "Foundation/Optional/Optional.h"
#include "Foundation/Optional/NullOpt.h"
#include "Foundation/Variant/Variant.h"
#include "Foundation/Assert/Assert.h"
#include "Foundation/Random/Random.h"

#include "Foundation/Buffer/Buffer.h"
#include "Foundation/Delegate/Delegate.h"
#include "Foundation/Handle/Handle.h"

#include "Foundation/BasicTypes/BasicTypeFuncs.h"
#include "Foundation/BasicTypes/BasicTypes.refl.h"