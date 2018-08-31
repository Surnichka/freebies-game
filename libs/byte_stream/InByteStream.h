#ifndef IN_BYTE_STREAM_O
#define IN_BYTE_STREAM_O

#include <vector>
#include <map>
#include <unordered_map>
#include <list>
#include <set>
#include "TypeTools.h"

namespace libs
{

class iByteStream
{
public:
	using ByteBuffer = std::vector<uint8_t>;

	iByteStream();
	iByteStream(const ByteBuffer buffer);

	template<typename T>
    iByteStream& operator>>(T& var)
	{
        FromBuffer(var);
		return (*this);
	}

	void SetBuffer(const ByteBuffer& buffer);
    void Invalidate();

private:

	inline uint8_t* ConsumeInternalMemory(const size_t& size)
	{
		if(!(m_endIndex >= (size + m_endOfPayload)))
		{
			if(m_lastOperationSuccess == true)
			{
				m_lastOperationSuccess = false;
			}
			throw "Bad buffer data.";
		}
		uint8_t* memPtr = m_buffer.data() + m_endOfPayload;
		m_endOfPayload += size;

		return memPtr;
	}

	template<typename ReturnType, typename StoredType>
    inline void CastType(ReturnType* dest, uint8_t* src)
	{
		StoredType storedType = 0;
        type_tools::CopyToBuffer<sizeof(storedType)>(&storedType, src);
		*dest = static_cast<ReturnType>(storedType);
	}

    ////////////////////////////////////// ARRAY ////////////////////////////////////////////////////
    template<typename T> inline
	std::enable_if_t
	<
		type_tools::TypeInfo<T>::IsFundamental == true	&&
		type_tools::TypeInfo<T>::IsArray == true        &&
		std::is_same<T, std::vector<bool>>::value == false,
    void
	>
	FromBuffer(T& var)
	{
        uint8_t* memPtr = ConsumeInternalMemory(type_tools::arrayHeaderSize);
//        uint8_t headerMask = *memPtr; //used for determining if array needs type cast
        uint32_t elementsCount = 0;
        type_tools::CopyFromBuffer<sizeof(elementsCount)>(reinterpret_cast<uint8_t*>(&elementsCount), ++memPtr);

        //if some_array<T> -> T remote and T local matches
        uint32_t totalSize = sizeof(typename type_tools::ArrayInfo<T>::Type) * elementsCount;
        memPtr = ConsumeInternalMemory(totalSize);

        type_tools::ArrayInfo<T>::Resize(var, elementsCount);

        std::memcpy(reinterpret_cast<uint8_t*>(type_tools::ArrayInfo<T>::FrontMutable(var)), memPtr, totalSize);

        ClearStringZeroes(var);
	}

    template<typename T> inline
    std::enable_if_t
    <
        type_tools::TypeInfo<T>::IsFundamental == false &&
        type_tools::TypeInfo<T>::IsArray == true        &&
        std::is_same<T, std::vector<bool>>::value == false,
    void
    >
    FromBuffer(T& var)
    {
        uint8_t* memPtr = ConsumeInternalMemory(type_tools::arrayHeaderSize);
//        uint8_t headerMask = *memPtr; //used for determining if array needs type cast
        uint32_t elementsCount = 0;
        type_tools::CopyFromBuffer<sizeof(elementsCount)>(reinterpret_cast<uint8_t*>(&elementsCount), ++memPtr);
        memPtr += type_tools::arrayHeaderSize;

        type_tools::ArrayInfo<T>::Resize(var, elementsCount);

        typename type_tools::ArrayInfo<T>::Type* dstPtr = type_tools::ArrayInfo<T>::FrontMutable(var);
        const typename type_tools::ArrayInfo<T>::Type* endPtr = dstPtr + elementsCount;

        while(endPtr > dstPtr)
        {
            *this >> (*dstPtr);
            dstPtr++;
        }
    }

    inline void FromBuffer(std::vector<bool>& var)
    {
        ByteBuffer bytes;
        FromBuffer(bytes);

        var.resize(bytes.size());

        uint32_t idx = 0;
        for(auto item : bytes)
        {
            var[idx] = static_cast<bool>(item);
            ++idx;
        }
    }

    template<typename Key, typename Value>
    inline void FromBuffer(std::pair<Key, Value>& var)
    {
        (*this) >> var.first >> var.second;
    }

    template<typename Key, typename Value>
    inline void FromBuffer(std::map<Key, Value>& var)
    {
        uint32_t size = 0;
        (*this) >> size;

        var.clear();

        for(uint32_t i = 0; i < size; ++i)
        {
            std::pair<Key, Value> p;
            (*this) >> p;

            var.emplace(std::move(p));
        }
    }

    template<typename Key, typename Value>
    inline void FromBuffer(std::unordered_map<Key, Value>& var)
    {
        uint32_t size = 0;
        (*this) >> size;

        var.clear();

        for (uint32_t i = 0; i < size; ++i)
        {
            std::pair<Key, Value> p;
            (*this) >> p;

            var.emplace(std::move(p));
        }
    }

    template<typename T>
    inline void FromBuffer(std::list<T>& var)
    {
        uint32_t size = 0;
        (*this) >> size;

        var.clear();

        for (uint32_t i = 0; i < size; ++i)
        {
            T element;
            (*this) >> element;

            var.emplace_back(std::move(element));
        }
    }

    template<typename T>
    inline void FromBuffer(std::set<T>& var)
    {
        uint32_t size = 0;
        (*this) >> size;
        var.clear();

        for (uint32_t i = 0; i < size; ++i)
        {
            T element;
            (*this) >> element;

            var.emplace(std::move(element));
        }
    }

    template<typename T>
    void ClearStringZeroes(T&) {}

    void ClearStringZeroes(std::string& var)
    {
        while((var.empty() == false) && (var.back() == 0))
        {
            var.pop_back();
        }
    }

    ////////////////////////////////////// FUNDAMENTAL /////////////////////////////////////////////
    template<typename T> inline
    std::enable_if_t
    <
        type_tools::TypeInfo<T>::IsFundamental == true &&
        type_tools::TypeInfo<T>::IsArray == false,
    void
    >
    FromBuffer(T& var)
    {
        uint8_t* memPtr = ConsumeInternalMemory(type_tools::headerSize);
        uint8_t headerData = *memPtr;

		memPtr = ConsumeInternalMemory(type_tools::header_parser::Parser::TypeSize(headerData));
		if(type_tools::header_parser::TypeMatcher<T>::IsCastNeeded(headerData))
		{
			type_tools::CopyFromBuffer<sizeof(var)>(&var, memPtr);
		}
		else
        {
			using namespace type_tools;
			switch(headerData)
			{
			case(fundamentalMask | integralMask | signedMask | typeSizeMask_1):
			{
				CastType<T, int8_t>(&var, memPtr);
			}
			break;
			case(fundamentalMask | integralMask | signedMask | typeSizeMask_2):
			{
				CastType<T, int16_t>(&var, memPtr);
			}
			break;
			case(fundamentalMask | integralMask | signedMask | typeSizeMask_4):
			{
				CastType<T, int32_t>(&var, memPtr);
			}
			break;
			case(fundamentalMask | integralMask | signedMask | typeSizeMask_8):
			{
				CastType<T, int64_t>(&var, memPtr);
			}
			break;
			case(fundamentalMask | integralMask | unsignedMask | typeSizeMask_1):
			{
				CastType<T, uint8_t>(&var, memPtr);
			}
			break;
			case(fundamentalMask | integralMask | unsignedMask | typeSizeMask_2):
			{
				CastType<T, uint16_t>(&var, memPtr);
			}
			break;
			case(fundamentalMask | integralMask | unsignedMask | typeSizeMask_4):
			{
				CastType<T, uint32_t>(&var, memPtr);
			}
			break;
			case(fundamentalMask | integralMask | unsignedMask | typeSizeMask_8):
			{
				CastType<T, uint64_t>(&var, memPtr);
			}
			break;
			case(fundamentalMask | nonintegralMask | signedMask | typeSizeMask_4):
			{
				CastType<T, float>(&var, memPtr);
			}
			break;
			case(fundamentalMask | nonintegralMask | signedMask | typeSizeMask_8):
			{
				CastType<T, double>(&var, memPtr);
			}
			break;
			default:
			throw "Wrong cases or sth gone wrong.";
			break;
			}
            return;
		}
    }

	ByteBuffer	m_buffer;
	size_t		m_endOfPayload;
	size_t		m_endIndex;
	size_t		m_frontIndex;
	bool		m_lastOperationSuccess;
};

}//end of libs

#endif
