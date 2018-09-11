#pragma once
#include "IAnimation.h"
#include <string>
#include <vector>

namespace core
{

class AnimationSequence : public IAnimation
{
public:
    explicit AnimationSequence(const std::string& holder, const std::vector<std::string>& textureIds);
    void Start(std::chrono::milliseconds duration) override;
    void Stop() override;
    bool Update(Entity& entity) override;
private:
    std::string m_resouceHolderId;
    std::vector<std::string> m_textureIds;
};

} //end of core
