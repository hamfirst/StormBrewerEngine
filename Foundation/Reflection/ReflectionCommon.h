#pragma once

#include "Foundation\Reflection\Reflection.h"
#include "Foundation\Reflection\ReflectionNumber.h"
#include "Foundation\Reflection\ReflectionString.h"
#include "Foundation\Reflection\ReflectionEnum.h"
#include "Foundation\Reflection\ReflectionStruct.h"
#include "Foundation\Reflection\ReflectionPolymorphic.h"
#include "Foundation\Reflection\ReflectionList.h"
#include "Foundation\Reflection\ReflectionMap.h"

using RFile = RString;
using RHash = uint32_t;

using RByte = RNumber<int8_t>;
using RShort = RNumber<int16_t>;
using RInt = RNumber<int32_t>;
using RLong = RNumber<int64_t>;
using RUByte = RNumber<uint8_t>;
using RUShort = RNumber<uint16_t>;
using RUInt = RNumber<uint32_t>;
using RULong = RNumber<uint64_t>;
using RFloat = RNumber<float>;

template <class T>
using RList = RArrayList<T>;

template <class T>
using RHashMap = ReflectionMap<RHash, T>;

