#include "InByteStream.h"

namespace libs
{

iByteStream::iByteStream()
: m_buffer(0)
, m_endOfPayload(0)
, m_endIndex(m_buffer.size())
, m_frontIndex(0)
, m_lastOperationSuccess(false)
{

}

iByteStream::iByteStream(const iByteStream::ByteBuffer buffer)
: m_buffer(std::move(buffer))
, m_endOfPayload(0)
, m_endIndex(m_buffer.size())
, m_frontIndex(0)
, m_lastOperationSuccess(false)
{

}

void iByteStream::SetBuffer(const iByteStream::ByteBuffer& buffer)
{
	m_buffer = buffer;
	m_endOfPayload = 0;
	m_endIndex = m_buffer.size();
	m_frontIndex = 0;
    m_lastOperationSuccess = false;
}

void iByteStream::Invalidate()
{
    m_lastOperationSuccess = false;
}


}//end of libs
