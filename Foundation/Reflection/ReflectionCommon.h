#pragma once

#include "Foundation\Reflection\Reflection.h"
#include "Foundation\Reflection\ReflectionNumber.h"
#include "Foundation\Reflection\ReflectionString.h"
#include "Foundation\Reflection\ReflectionEnum.h"
#include "Foundation\Reflection\ReflectionStruct.h"
#include "Foundation\Reflection\ReflectionList.h"
#include "Foundation\Reflection\ReflectionMap.h"

using RFile = RString;
using RHash = uint32_t;

using RByte = RNumber<char>;
using RShort = RNumber<short>;
using RInt = RNumber<int>;
using RLong = RNumber<long long>;
using RUByte = RNumber<unsigned char>;
using RUShort = RNumber<unsigned short>;
using RUInt = RNumber<unsigned int>;
using RULong = RNumber<unsigned long long>;
using RFloat = RNumber<float>;

template <class T>
using RList = RArrayList<T>;

template <class T>
using RHashMap = ReflectionMap<RHash, T>;

