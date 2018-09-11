#pragma once
#include "IAnimation.h"
#include <string>
#include <vector>

namespace core
{

class FrameAnimation : public IAnimation
{
public:
    explicit FrameAnimation(const std::string& holder, const std::vector<std::string>& textureIds);
    void Start(std::chrono::milliseconds duration) override;
    void Stop() override;
    void Update(Entity& entity) override;
private:
    std::string m_resouceHolderId;
    std::vector<std::string> m_textureIds;
};

} //end of core
