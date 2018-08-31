#ifndef OUT_BYTE_STREAM_H
#define OUT_BYTE_STREAM_H

#include <vector>
#include <map>
#include <unordered_map>
#include <list>
#include <set>
#include "TypeTools.h"

namespace libs
{

class oByteStream
{
public:
	using ByteBuffer = std::vector<uint8_t>;
	oByteStream();

	oByteStream(const oByteStream&) = delete;
	oByteStream& operator=(const oByteStream&) = delete;

	template<typename T>
    oByteStream& operator<<(const T& var)
	{
		ToBuffer(var);
		return (*this);
	}

	ByteBuffer GetBuffer() const;

private:
	inline uint8_t* GetInternalMemory(const size_t& size)
	{
		if(size > (m_endIndex - m_endOfPayload))
		{
			size_t missingSize = size - (m_endIndex - m_endOfPayload);
			m_buffer.resize(m_buffer.size() * 2 + missingSize);
			m_endIndex = m_buffer.size();
		}
		uint8_t* memPtr = m_buffer.data() + m_endOfPayload;
		m_endOfPayload += size;

		return memPtr;
	}

	template<typename T> inline
	void FundamentalToBytes(const T* var, uint8_t* dst, uint8_t headerMask)
	{
		const uint8_t* src = reinterpret_cast<const uint8_t*>(var);
		*dst++ = headerMask;
		type_tools::CopyToBuffer<sizeof(T)>(dst, src);
	}

    inline void ArrayHeaderToBytes(uint8_t* dst, const uint8_t mask, const uint32_t elementsCount)
    {
        *dst = mask;
        type_tools::CopyToBuffer<sizeof(elementsCount)>(++dst, reinterpret_cast<const uint8_t*>(&elementsCount));
    }

	template<typename T> inline
	void ArrayToBytes(const T* var, uint8_t* dst, const uint32_t elementsCount)
	{
        ArrayHeaderToBytes(dst, type_tools::TypeInfo<T>::value, elementsCount);
        dst += (type_tools::arrayHeaderSize);

		const uint8_t* src = reinterpret_cast<const uint8_t*>(var);
		const size_t totalSize = elementsCount * sizeof(T);

		memcpy(dst, src, totalSize);
    }

	template<typename T> inline
	std::enable_if_t
	<
        type_tools::TypeInfo<T>::IsFundamental	== true &&
        type_tools::TypeInfo<T>::IsArray		== true &&
        std::is_same<T, std::vector<bool>>::value == false,
	void
	>
	ToBuffer(const T& var)
    {
        uint8_t* memPtr = GetInternalMemory(type_tools::ArrayInfo<T>::GetSerializedSize(var));
		const uint32_t elementsCount = type_tools::ArrayInfo<T>::GetSize(var);

		ArrayToBytes((type_tools::ArrayInfo<T>::FrontConst(var)), memPtr, elementsCount);
	}

    template<typename T> inline
    std::enable_if_t
    <
        type_tools::TypeInfo<T>::IsFundamental	== false &&
        type_tools::TypeInfo<T>::IsArray		== true  &&
        std::is_same<T, std::vector<bool>>::value == false,
    void
    >
    ToBuffer(const T& var)
    {
        uint8_t* memPtr = GetInternalMemory(type_tools::arrayHeaderSize);
        const uint32_t elementsCount = type_tools::ArrayInfo<T>::GetSize(var);

        ArrayHeaderToBytes(memPtr, type_tools::TypeInfo<T>::value, elementsCount);
        memPtr += (type_tools::arrayHeaderSize);

        const typename type_tools::ArrayInfo<T>::Type* srcPtr = type_tools::ArrayInfo<T>::FrontConst(var);
        const typename type_tools::ArrayInfo<T>::Type* srcEndPtr = srcPtr + elementsCount;

        while(srcEndPtr > srcPtr)
        {
            (*this) << (*srcPtr);
            srcPtr++;
        }
    }

    inline void ToBuffer(const std::vector<bool>& var)
    {
        uint8_t* memptr = GetInternalMemory(type_tools::arrayHeaderSize);

        ArrayHeaderToBytes(memptr, type_tools::TypeInfo<std::vector<bool>>::value, static_cast<uint32_t>(var.size()));
        ByteBuffer bytes(var.size());

        uint32_t idx = 0;
        for(auto bit : var)
        {
            bytes[idx] = static_cast<uint8_t>(bit);
            ++idx;
        }

    }

    template<typename Key, typename Value>
    inline void ToBuffer(const std::pair<Key, Value>& var)
    {
        (*this) << var.first << var.second;
    }

    template<typename Key, typename Value>
    inline void ToBuffer(const std::map<Key, Value>& var)
    {
        uint32_t size = var.size();
        (*this) << size;

        for(const auto& pair : var)
        {
            (*this) << pair;
        }
    }

    template<typename Key, typename Value>
    inline void ToBuffer(const std::unordered_map<Key, Value>& var)
    {
        uint32_t size = var.size();
        (*this) << size;

        for(const auto& item : var)
        {
            (*this) << item;
        }
    }

    template<typename T>
    inline void ToBuffer(const std::list<T>& var)
    {
        uint32_t size = var.size();
        (*this) << size;

        for(const auto& item : var)
        {
            (*this) << item;
        }
    }

    template<typename T>
    inline void ToBuffer(const std::set<T>& var)
    {
        uint32_t size = var.size();
        (*this) << size;

        for(const auto& item : var)
        {
            (*this) << item;
        }
    }

	template<typename T> inline
	std::enable_if_t
	<
		type_tools::TypeInfo<T>::IsFundamental	== true &&
		type_tools::TypeInfo<T>::IsArray		== false,
	void
	>
	ToBuffer(const T& var)
	{
		constexpr uint8_t mask = type_tools::TypeInfo<T>::value;
		uint8_t* memPtr = GetInternalMemory(type_tools::TypeInfo<T>::SerializedSize);
		FundamentalToBytes(&var, memPtr, mask);
	}

	ByteBuffer	m_buffer;
	size_t		m_endOfPayload;
	size_t		m_endIndex;
	size_t		m_frontIndex;

};

}//end of libs

#endif
