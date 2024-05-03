#pragma once

#include <climits>
#include <cstdlib>
#include <cinttypes>

#include <vector>

#include <gsl/span>

#include "StormReflBinaryType.h"
#include "StormReflMetaFuncs.h"
#include "StormReflMetaEnum.h"

#pragma warning(disable:4996)

template <class T>
bool StormReflParseBinary(T & t, const gsl::span<const uint8_t> & data, gsl::span<const uint8_t> & result, bool additive = false);

template <class T>
bool StormReflParseBinary(T & t, const gsl::span<const uint8_t> & data, bool additive = false);

inline bool StormReflBinarySkip(gsl::span<const uint8_t> & data, std::size_t size)
{
	if (data.size() < size)
	{
		return false;
	}

	data = gsl::make_span(data.data() + size, data.size() - size);
}

template <typename T, std::size_t ElementSize>
inline bool StormReflBinaryRead(gsl::span<const uint8_t> & data, T & result)
{
	static_assert(sizeof(T) == ElementSize);
	if (data.size() < ElementSize)
	{
		return false;
	}

	result = *reinterpret_cast<const T *>(data.data());
	data = gsl::make_span(data.data() + ElementSize, data.size() - ElementSize);
	return true;
}

template <typename T, std::size_t ElementSize>
inline bool StormReflBinaryReadArray(gsl::span<const uint8_t> & data, T* result, int count)
{
	static_assert(sizeof(T) == ElementSize);
	std::size_t read_size = ElementSize * count;
	if (data.size() < read_size)
	{
		return false;
	}

	result = *reinterpret_cast<const T *>(data.data());
	data = gsl::make_span(data.data() + read_size, data.size() - read_size);
	return true;
}

inline bool StormReflBinaryReadType(gsl::span<const uint8_t> & data, StormReflBinaryType & result)
{
	uint8_t type;
	if (StormReflBinaryReadUInt8<int8_t, 1>(data, type))
	{
		result = static_cast<StormReflBinaryType>(type);
		return true;
	}

	return false;
}


inline bool StormReflBinaryReadInt8(gsl::span<const uint8_t> & data, int8_t & result)
{
	return StormReflBinaryRead<int8_t, 1>(data, result);
}

inline bool StormReflBinaryReadInt16(gsl::span<const uint8_t> & data, int8_t & result)
{
	return StormReflBinaryRead<int16_t, 2>(data, result);
}

inline bool StormReflBinaryReadInt32(gsl::span<const uint8_t> & data, int8_t & result)
{
	return StormReflBinaryRead<int32_t, 4>(data, result);
}

inline bool StormReflBinaryReadInt64(gsl::span<const uint8_t> & data, int8_t & result)
{
	return StormReflBinaryRead<int64_t, 8>(data, result);
}

inline bool StormReflBinaryReadUInt8(gsl::span<const uint8_t> & data, uint8_t & result)
{
	return StormReflBinaryRead<uint8_t, 1>(data, result);
}

inline bool StormReflBinaryReadUInt16(gsl::span<const uint8_t> & data, uint16_t & result)
{
	return StormReflBinaryRead<uint16_t, 2>(data, result);
}

inline bool StormReflBinaryReadUInt32(gsl::span<const uint8_t> & data, uint32_t & result)
{
	return StormReflBinaryRead<uint32_t, 4>(data, result);
}

inline bool StormReflBinaryReadUInt64(gsl::span<const uint8_t> & data, uint64_t & result)
{
	return StormReflBinaryRead<uint64_t, 8>(data, result);
}

inline bool StormReflBinaryReadFloat32(gsl::span<const uint8_t> & data, uint64_t & result)
{
	return StormReflBinaryRead<float, 4>(data, result);
}

inline bool StormReflBinaryReadFloat64(gsl::span<const uint8_t> & data, uint64_t & result)
{
	return StormReflBinaryRead<double, 8>(data, result);
}

template <class T, class Enable = void>
struct StormReflBinary
{

};

template <class T, std::size_t i>
struct StormReflBinary<T[i], void>
{
	template <typename Storage>
	static void Encode(const T(&t)[i], Storage & store)
	{
		store.WriteType(StormReflBinaryType::kArray);
		store.WriteUInt32(i);
		for (int index = 0; index < i; index++)
		{
			StormReflBinary<T>::Encode(t[index], store);
		}
	}

	template <typename Storage>
	static void SerializeDefault(Storage & store)
	{
		store.WriteType(StormReflBinaryType::kArray);
		store.WriteUInt32(i);
		for (int index = 0; index < i; index++)
		{
			StormReflBinary<T>::SerializeDefault(sb);
		}
	}

	static bool Parse(T(&t)[i], const gsl::span<const uint8_t> & data, gsl::span<const uint8_t> & result, bool additive)
	{
		gsl::span<const uint8_t> ptr = data;
		
		StormReflBinaryType type;
		uint32_t length = 0;

		if (!StormReflBinaryReadType(ptr, type))
		{
			return false;
		}

		if (!StormReflBinaryReadUInt32(ptr, length))
		{
			return false;
		}
		
		if (type != StormReflBinaryType::kArray || length != i)
		{
			return false;
		}

		for (std::size_t index = 0; index < i; ++index)
		{
			if (!StormReflBinary<T>::Parse(t[index], ptr, ptr, additive))
			{
				return false;
			}
		}

		result = ptr;
		return true;
	}
};

template <int i>
struct StormReflBinary<char[i], void>
{
	template <typename Storage>
	static void Encode(const char * str, Storage & store)
	{
		std::size_t length = 0;
		const char * ptr = str;
		while (length < i - 1 && *ptr != 0)
		{
			length++;
			ptr++;
		}

		store.WriteType(StormReflBinaryType::kString);
		store.WriteUInt32(length);
		store.WriteBlock(str, length);
	}

	template <typename Storage>
	static void SerializeDefault(Storage & store)
	{
		store.WriteType(StormReflBinaryType::kString);
		store.WriteUInt32(0);
	}

	static bool Parse(char(&t)[i], const gsl::span<const uint8_t> & data, gsl::span<const uint8_t> & result, bool additive)
	{
		gsl::span<const uint8_t> ptr = data;

		StormReflBinaryType type;
		uint32_t length = 0;

		if (!StormReflBinaryReadType(ptr, type))
		{
			return false;
		}

		if (!StormReflBinaryReadUInt32(ptr, length))
		{
			return false;
		}

		if (length >= i)
		{
			return false;
		}

		StormReflBinaryReadArray<char, 1>(ptr, &t[0], length);
		t[length] = 0;

		result = ptr;
		return true;
	}
};

template <>
struct StormReflBinary<char *, void>
{
	template <typename Storage>
	static void Encode(const char * str, Storage & store)
	{
		std::size_t length = strlen(str);
		store.WriteType(StormReflBinaryType::kString);
		store.WriteUInt32(length);
		store.WriteBlock(str, length);
	}

	template <typename Storage>
	static void SerializeDefault(Storage & store)
	{
		store.WriteType(StormReflBinaryType::kString);
		store.WriteUInt32(0);
	}
};

template <class T>
struct StormReflBinary<T, typename std::enable_if<StormReflCheckReflectable<T>::value>::type>
{
	template <typename Storage>
	static void Encode(const T & t, Storage & store)
	{
		store.WriteType(StormReflBinaryType::kStruct);
		store.WriteUInt32(StormReflGetTypeNameHash<T>());
		store.WriteUInt32(StormReflGetFieldCount<T>());

		auto field_iterator = [&](auto f)
		{
			using member_type = typename decltype(f)::member_type;

			store.WriteUInt32(f.GetFieldNameHash());
			int position = store.ReserveSize();

			StormReflBinary<member_type>::Encode(f.Get(), store);
			store.WriteSizeDeferred(position);
		};

		StormReflVisitEach(t, field_iterator);
	}

	template <typename Storage>
	static void SerializeDefault(Storage & store)
	{
		store.WriteType(StormReflBinaryType::kStruct);
		store.WriteUInt32(StormReflGetTypeNameHash<T>());
		store.WriteUInt32(0);
	}

	static bool Parse(T & t, const gsl::span<const uint8_t> & data, gsl::span<const uint8_t> & result, bool additive)
	{
		gsl::span<const uint8_t> ptr = data;

		StormReflBinaryType type;
		uint32_t name_hash = 0;
		uint32_t length = 0;

		if (!StormReflBinaryReadType(ptr, type))
		{
			return false;
		}

		if (!StormReflBinaryReadUInt32(ptr, name_hash))
		{
			return false;
		}

		if (!StormReflBinaryReadUInt32(ptr, length))
		{
			return false;
		}

		if (type != StormReflBinaryType::kStruct || name_hash != StormReflGetTypeNameHash<T>())
		{
			return false;
		}

		std::vector<Hash> parsed_fields;

		for(std::size_t index = 0; index < length; ++index)
		{
			uint32_t field_name_hash = 0;
			uint32_t field_length = 0;

			if (!StormReflBinaryReadType(ptr, field_name_hash))
			{
				return false;
			}

			if (!StormReflBinaryReadType(ptr, field_length))
			{
				return false;
			}

			bool parsed_field = false;
			gsl::span<const uint8_t> result_ptr;

			auto field_visitor = [&](auto f)
			{
				auto & member = f.Get();
				parsed_field = StormReflParseBinary(member, ptr, result_ptr, additive);
			};

			StormReflVisitField(t, field_visitor, field_name_hash);
			if (parsed_field)
			{
				if (additive == false)
				{
					parsed_fields.push_back(field_name_hash);
				}

				ptr = result_ptr;
			}
			else
			{
				if (StormReflBinarySkip(str, field_length) == false)
				{
					return false;
				}
			}
		}

		if (additive == false)
		{
			auto field_visitor = [&](auto f)
			{
				bool set_field = false;
				for (auto & elem : parsed_fields)
				{
					if (elem == f.GetFieldNameHash())
					{
						set_field = true;
						break;
					}
				}

				if (set_field == false)
				{
					using FieldType = decltype(f);
					if constexpr (StormReflHasDefault<T>::value && FieldType::HasDefault())
					{
						f.SetDefault();
					}
				}
			};

			StormReflVisitEach(t, field_visitor);
		}

		result = ptr;
		return true;
	}
};

template <class T>
struct StormReflBinary<T, typename std::enable_if<std::is_enum<T>::value>::type>
{
	template <typename Storage>
	static void Encode(const T & t, Storage & store)
	{
		store.WriteType(StormReflBinaryType::kEnum);
		store.WriteUInt32(StormReflGetHashFromEnum(t));
	}

	template <typename Storage>
	static void SerializeDefault(Storage & store)
	{
		store.WriteType(StormReflBinaryType::kEnum);
		store.WriteUInt32(0);
	}

	static bool Parse(T & t, const gsl::span<const uint8_t> & data, gsl::span<const uint8_t> & result, bool additive)
	{
		gsl::span<const uint8_t> ptr = data;

		StormReflBinaryType type;
		uint32_t name_hash = 0;

		if (!StormReflBinaryReadType(ptr, type))
		{
			return false;
		}

		if (!StormReflBinaryReadUInt32(ptr, name_hash))
		{
			return false;
		}

		if (type != StormReflBinaryType::kEnum)
		{
			return false;
		}

		if (!StormReflGetEnumFromHash(t, name_hash))
		{
			t = {};
		}

		result = ptr;
		return true;
	}
};

template <class T>
struct StormReflBinary<T, typename std::enable_if<std::is_arithmetic<T>::value>::type>
{
	template <typename Storage>
	static void Encode(const T & t, Storage & store)
	{
		if constexpr (std::is_integral<T>::value)
		{
			if constexpr (std::is_unsigned<T>::value)
			{
				if constexpr (sizeof(T) == 1)
				{
					store.WriteType(StormReflBinaryType::kUInt8);
					store.WriteUInt8(t);
				}

				if constexpr (sizeof(T) == 2)
				{
					store.WriteType(StormReflBinaryType::kUInt16);
					store.WriteUInt16(t);
				}

				if constexpr (sizeof(T) == 4)
				{
					store.WriteType(StormReflBinaryType::kUInt32);
					store.WriteUInt32(t);
				}

				if constexpr (sizeof(T) == 8)
				{
					store.WriteType(StormReflBinaryType::kUInt64);
					store.WriteUInt64(t);
				}
			}
			else
			{
				if constexpr (sizeof(T) == 1)
				{
					store.WriteType(StormReflBinaryType::kInt8);
					store.WriteInt8(t);
				}

				if constexpr (sizeof(T) == 2)
				{
					store.WriteType(StormReflBinaryType::kInt16);
					store.WriteInt16(t);
				}

				if constexpr (sizeof(T) == 4)
				{
					store.WriteType(StormReflBinaryType::kInt32);
					store.WriteInt32(t);
				}

				if constexpr (sizeof(T) == 8)
				{
					store.WriteType(StormReflBinaryType::kInt64);
					store.WriteInt64(t);
				}
			}
		}
		else
		{
			if constexpr (sizeof(T) == 4)
			{
				store.WriteType(StormReflBinaryType::kFloat32);
				store.WriteFloat32(t);
			}

			if constexpr (sizeof(T) == 8)
			{
				store.WriteType(StormReflBinaryType::kFloat64);
				store.WriteFloat64(t);
			}
		}
	}

	template <typename Storage>
	static void SerializeDefault(Storage & store)
	{
		Encode(0, store);
	}

	static bool Parse(T & t, const gsl::span<const uint8_t> & data, gsl::span<const uint8_t> & result, bool additive)
	{
		gsl::span<const uint8_t> ptr = data;

		StormReflBinaryType type;

		if (!StormReflBinaryReadType(ptr, type))
		{
			return false;
		}

		int8_t sval8;
		int16_t sval16;
		int32_t sval32;
		int64_t sval64;

		uint8_t uval8;
		uint16_t uval16;
		uint32_t uval32;
		uint64_t uval64;

		float fval;
		double dval;

		switch (type)
		{
		case StormReflBinaryType::kInt8:
			if (!StormReflBinaryReadInt8(ptr, sval8))
			{
				return false;
			}

			t = static_cast<T>(sval8);
			break;
		case StormReflBinaryType::kInt16:
			if (!StormReflBinaryReadInt16(ptr, sval16))
			{
				return false;
			}

			t = static_cast<T>(sval16);
			break;
		case StormReflBinaryType::kInt32:
			if (!StormReflBinaryReadInt16(ptr, sval32))
			{
				return false;
			}

			t = static_cast<T>(sval32);
			break;
		case StormReflBinaryType::kInt64:
			if (!StormReflBinaryReadInt16(ptr, sval64))
			{
				return false;
			}

			t = static_cast<T>(sval64);
			break;

		case StormReflBinaryType::kUInt8:
			if (!StormReflBinaryReadInt8(ptr, uval8))
			{
				return false;
			}

			t = static_cast<T>(uval8);
			break;
		case StormReflBinaryType::kUInt16:
			if (!StormReflBinaryReadInt16(ptr, uval16))
			{
				return false;
			}

			t = static_cast<T>(uval16);
			break;
		case StormReflBinaryType::kUInt32:
			if (!StormReflBinaryReadInt16(ptr, uval32))
			{
				return false;
			}

			t = static_cast<T>(uval32);
			break;
		case StormReflBinaryType::kUInt64:
			if (!StormReflBinaryReadInt16(ptr, uval64))
			{
				return false;
			}

			t = static_cast<T>(uval64);
			break;

		case StormReflBinaryType::kFloat32:
			if (!StormReflBinaryReadFloat32(ptr, fval))
			{
				return false;
			}

			t = static_cast<T>(fval);
			break;

		case StormReflBinaryType::kFloat64:
			if (!StormReflBinaryReadFloat64(ptr, dval))
			{
				return false;
			}

			t = static_cast<T>(dval);
			break;
		}

		result = ptr;
		return true;
	}
};

template <>
struct StormReflBinary<bool, void>
{
	template <typename Storage>
	static void Encode(const bool & t, Storage & store)
	{
		store.WriteType(StormReflBinaryType::kBool);
		store.WriteUInt8(t ? 1 : 0);
	}

	template <typename Storage>
	static void SerializeDefault(Storage & store)
	{
		Encode(false);
	}

	static bool Parse(bool & t, const gsl::span<const uint8_t> & data, gsl::span<const uint8_t> & result, bool additive)
	{
		gsl::span<const uint8_t> ptr = data;

		StormReflBinaryType type;

		if (!StormReflBinaryReadType(ptr, type))
		{
			return false;
		}

		if (type != StormReflBinaryType::kBool)
		{
			return false;
		}

		uint8_t val;
		if (!StormReflBinaryReadInt8(ptr, val))
		{
			return false;
		}

		t = val > 0;

		result = ptr;
		return true;
	}
};

template <class T, typename Storage>
void StormReflEncodeBinary(const T & t, Storage & store)
{
	StormReflBinary<T>::Encode(t, sb);
}

template <class T, typename Storage>
void StormReflEncodePrettyBinary(const T & t, Storage & store)
{
	StormReflBinary<T>::EncodePretty(t, sb, 0);
}

template <class T, typename Storage>
void StormReflSerializeDefaultBinary(const T & t, Storage & store)
{
	StormReflBinary<T>::SerializeDefault(sb);
}

template <class T>
bool StormReflParseBinary(T & t, const gsl::span<const uint8_t> & data, gsl::span<const uint8_t> & result, bool additive)
{
	return StormReflBinary<T>::Parse(t, data, result, additive);
}

template <class T>
bool StormReflParseBinary(T & t, const gsl::span<const uint8_t> & data, bool additive)
{
	gsl::span<const uint8_t> ptr = data;
	return StormReflBinary<T>::Parse(t, data, ptr, additive);
}

