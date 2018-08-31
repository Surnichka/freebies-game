#include "Msg.h"

namespace libs
{

bool Msg::HasValue(const std::string& name) const
{
    return (m_msgs.find(name) != m_msgs.end());
}

} //end of namespace libs
