#include "OutByteStream.h"

namespace libs
{

oByteStream::oByteStream()
: m_buffer(256)
, m_endOfPayload(0)
, m_endIndex(m_buffer.size())
, m_frontIndex(0)
{

}

oByteStream::ByteBuffer oByteStream::GetBuffer() const
{
	return m_buffer;
}



}//end of libs
