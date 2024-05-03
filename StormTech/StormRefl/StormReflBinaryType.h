#pragma once

enum class StormReflBinaryType
{
	kBool,

	kInt8,
	kInt16,
	kInt32,
	kInt64,
	kUInt8,
	kUInt16,
	kUInt32,
	kUInt64,

	kFloat32,
	kFloat64,

	kEnum,
	kString,
	kArray,
	kDictionary,

	kStruct
};
