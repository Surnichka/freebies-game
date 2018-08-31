#ifndef TYPE_TOOLS_H
#define TYPE_TOOLS_H

#include <array>
#include <vector>
#include <string>
#include <cstring>
#include <type_traits>

namespace libs
{
namespace type_tools
{

constexpr uint8_t typeSizeMask	  = (3 << 0);//0000 0011
constexpr uint8_t integralMask	  = (1 << 2);//0000 0100
constexpr uint8_t signedMask	  = (1 << 3);//0000 1000
constexpr uint8_t arrayMask		  = (1 << 4);//0001 0000
constexpr uint8_t fundamentalMask = (1 << 7);//1000 0000

constexpr uint8_t typeSizeMask_1	 = (0 << 0);//0000 0000
constexpr uint8_t typeSizeMask_2	 = (1 << 0);//0000 0001
constexpr uint8_t typeSizeMask_4	 = (1 << 1);//0000 0010
constexpr uint8_t typeSizeMask_8	 = (3 << 0);//0000 0011

constexpr uint8_t nonintegralMask	= 0;
constexpr uint8_t unsignedMask		= 0;
constexpr uint8_t nonarrayMask		= 0;

constexpr uint32_t headerSize			= 1;
constexpr uint32_t arrayHeaderSize	= 5;

template<uint32_t size>
inline void CopyToBuffer(void* dst, const uint8_t* src) noexcept;

template<>
inline void CopyToBuffer<1>(void* dst, const uint8_t* src) noexcept
{
	*(reinterpret_cast<uint8_t*>(dst)) = *src;
}

template<>
inline void CopyToBuffer<2>(void* dst, const uint8_t* src) noexcept
{
	uint8_t* dstPtr = static_cast<uint8_t*>(dst);
	*dstPtr++ = *src++;
	*dstPtr = *src;
}

template<>
inline void CopyToBuffer<4>(void* dst, const uint8_t* src) noexcept
{
	uint8_t* dstPtr = static_cast<uint8_t*>(dst);
	*dstPtr++ = *src++;
	*dstPtr++ = *src++;
	*dstPtr++ = *src++;
	*dstPtr = *src;
}

template<>
inline void CopyToBuffer<8>(void* dst, const uint8_t* src) noexcept
{
	uint8_t* dstPtr = static_cast<uint8_t*>(dst);
	*dstPtr++ = *src++;
	*dstPtr++ = *src++;
	*dstPtr++ = *src++;
	*dstPtr++ = *src++;
	*dstPtr++ = *src++;
	*dstPtr++ = *src++;
	*dstPtr++ = *src++;
	*dstPtr = *src;
}

/////////////////////////////////////////////////////////////////////////////////

template<uint32_t size>
inline void CopyFromBuffer(void* dst, const uint8_t* src) noexcept;

template<>
inline void CopyFromBuffer<1>(void* dst, const uint8_t* src) noexcept
{
	*(reinterpret_cast<uint8_t*>(dst)) = *src;
}

template<>
inline void CopyFromBuffer<2>(void* dst, const uint8_t* src) noexcept
{
	uint16_t tmp;
	std::memcpy(&tmp, src, sizeof(tmp));
	*(reinterpret_cast<uint16_t*>(dst)) = tmp;
}

template<>
inline void CopyFromBuffer<4>(void* dst, const uint8_t* src) noexcept
{
	uint32_t tmp;
	std::memcpy(&tmp, src, sizeof(tmp));
	*(reinterpret_cast<uint32_t*>(dst)) = tmp;
}

template<>
inline void CopyFromBuffer<8>(void* dst, const uint8_t* src) noexcept
{
	uint64_t tmp;
	std::memcpy(&tmp, src, sizeof(tmp));
	*(reinterpret_cast<uint64_t*>(dst)) = tmp;
}

/////////////////////////////////////////////////////////////////////////////////

constexpr uint8_t MarkTypeSize(uint32_t size)
{
	return  (1 == size) ? typeSizeMask_1 :
			(2 == size) ? typeSizeMask_2 :
			(4 == size) ? typeSizeMask_4 :
			(8 == size) ? typeSizeMask_8 : 0;
}

template<typename T>
struct ArrayInfo
{
	using ArrayType = std::false_type;
	using Type = T;
	static constexpr bool isArray = false;
    static void Resize(ArrayType&, uint32_t) noexcept {}
	static uint32_t GetSize(const ArrayType&) noexcept {}
	static uint32_t GetSerializedSize(const ArrayType&) noexcept {}
	static const Type* FrotConst(const ArrayType&) noexcept {}
	static Type* FrontMutable(ArrayType&) noexcept {}
};

template<typename T, uint32_t N>
struct ArrayInfo<T[N]>
{
	using ArrayType = T[N];
	using Type = T;
	static constexpr bool isArray = true;

	static void Resize(ArrayType&, uint32_t) noexcept {}
	static constexpr uint32_t GetSize(const ArrayType&)
	{
		return N;
	}

	static constexpr uint32_t GetSerializedSize(const ArrayType&)
	{
		return (sizeof(Type) * N) + arrayHeaderSize;
	}

	static const Type* FrontConst(const ArrayType& at) noexcept
	{
		return &(at[0]);
	}

	static Type* FrontMutable(ArrayType& at)
	{
		return &(at[0]);
	}
};

template<typename T, uint32_t N>
struct ArrayInfo<std::array<T, N>>
{
	using ArrayType = std::array<T, N>;
	using Type = T;
	static constexpr bool isArray = true;

	static void Resize(ArrayType&, uint32_t) noexcept {}
	static constexpr uint32_t GetSize(const ArrayType&) noexcept
	{
		return N;
	}

	static constexpr uint32_t GetSerializedSize(const ArrayType&)
	{
		return (sizeof(Type) * N) + arrayHeaderSize;
	}

	static const Type* FrontConst(const ArrayType& at) noexcept
	{
		return &(at[0]);
	}

	static Type* FrontMutable(ArrayType& at)
	{
		return &(at[0]);
	}
};

template<typename T>
struct ArrayInfo<std::basic_string<T>>
{
	using ArrayType = std::basic_string<T>;
	using Type = T;
	static constexpr bool isArray = true;

	static void Resize(ArrayType& at, uint32_t sz)
	{
		at.resize(sz);
	}

	static uint32_t GetSize(const ArrayType& at)
	{
		return at.size();
	}

	static uint32_t GetSerializedSize(const ArrayType& at)
	{
		return (at.size() * sizeof(Type)) + arrayHeaderSize;
	}

	static const Type* FrontConst(const ArrayType& at) noexcept
	{
		return at.data();
	}

	static Type* FrontMutable(ArrayType& at)
	{
		if(at.empty())
		{
			return nullptr;
		}
        return &(at[0]);
	}
};

template<typename T>
struct ArrayInfo<std::vector<T>>
{
	using ArrayType = std::vector<T>;
	using Type = T;
	static constexpr bool isArray = true;

	static void Resize(ArrayType& at, uint32_t sz)
	{
		at.resize(sz);
	}

	static uint32_t GetSize(const ArrayType& at)
	{
		return at.size();
	}

	static uint32_t GetSerializedSize(const ArrayType& at)
	{
		return (at.size() * sizeof(Type)) + arrayHeaderSize;
	}

	static const Type* FrontConst(const ArrayType& at) noexcept
	{
		return at.data();
	}

	static Type* FrontMutable(ArrayType& at)
	{
		return at.data();
	}
};

template<>
struct ArrayInfo<const char*>
{
	using ArrayType = const char*;
	using Type = char;
	static constexpr bool isArray = true;

	static void Resize(ArrayType&, uint32_t) noexcept {}

	static uint32_t GetSize(const ArrayType& at)
	{
		return std::strlen(at);
	}

	static uint32_t GetSerializedSize(const ArrayType& at)
	{
		return (std::strlen(at) * sizeof(Type)) + arrayHeaderSize;
	}

	static const Type* FrontConst(const ArrayType& at) noexcept
	{
		return at;
	}
};

template<typename T>
struct RawInfo
{
    using Type = typename ArrayInfo<T>::Type;

    static constexpr bool IsArray = ArrayInfo<T>::isArray;
};

template<typename T>
struct TypeInfo
{
    using Type = typename RawInfo<T>::Type;

	static constexpr bool IsFundamental		= std::is_fundamental<Type>::value;
	static constexpr bool IsIntegral		= std::is_integral<Type>::value;
	static constexpr bool IsSigned			= std::is_signed<Type>::value;
    static constexpr bool IsArray			= RawInfo<T>::IsArray;
	static constexpr uint8_t TypeSize		= IsFundamental ? sizeof(Type) : 0;
	static constexpr uint8_t SerializedSize	= IsFundamental ? (TypeSize + headerSize) : 0;

	static constexpr uint8_t value =
	(IsFundamental	? fundamentalMask : 0) |
	(IsIntegral		? integralMask :	0) |
	(IsSigned		? signedMask :		0) |
    (IsArray		? arrayMask :		0) |
    (MarkTypeSize(TypeSize));
};


namespace header_parser
{

struct Parser
{
    inline static constexpr bool IsFundamental(const uint8_t& headerData) { return (headerData & fundamentalMask) == fundamentalMask; }
    inline static constexpr bool IsIntegral(const uint8_t& headerData) { return (headerData & integralMask) == integralMask; }
    inline static constexpr bool IsSigned(const uint8_t& headerData) { return (headerData & signedMask) == signedMask; }
    inline static constexpr bool IsArray(const uint8_t& headerData) { return (headerData & arrayMask) == arrayMask; }
	inline static constexpr uint32_t TypeSize(const uint8_t& headerData) { return (1 << (headerData & typeSizeMask)); }
};

template<typename T>
struct TypeMatcher
{
    using Type = TypeInfo<T>;
    using RemoteType = Parser;

    inline static constexpr bool IsCastNeeded(const uint8_t& header)
    {
        return (Type::IsFundamental && RemoteType::IsFundamental(header)&&
                Type::IsIntegral    && RemoteType::IsIntegral(header) &&
                Type::IsSigned      && RemoteType::IsSigned(header) &&
			   (Type::TypeSize      == RemoteType::TypeSize(header))) == false;
    }

};

} //end of header_parser
} //end of type_tools
} //end of libs

#endif
