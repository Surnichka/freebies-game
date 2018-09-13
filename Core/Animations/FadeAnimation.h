#pragma once
#include "IAnimation.h"

namespace core
{

class FadeBy : public IAnimation
{
public:
    using uPtr = std::unique_ptr<FadeBy>;

    static uPtr Create (int32_t fadeBy);

    void Start(std::chrono::milliseconds duration, bool loop = false) override;
    void Stop() override;
    bool Update(Entity& entity) override;
private:
//    int32_t m_beginFade = 0;
    int32_t m_fadeBy = 0;
};

} //end of core
