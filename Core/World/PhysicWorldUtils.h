#pragma once
#include <memory>

class b2Body;
namespace core
{
    const constexpr float physicWorldScale = 30.0f;

    float PixelToMeter(float pixel);
    float MeterToPixel(float meter);

    struct BodyDeleter
    {
        void operator()(b2Body* body);
    };
    using BodyPtr = std::unique_ptr<b2Body, BodyDeleter>;

namespace fixtureTypes
{
    const int32_t bodyBox = 0;
    const int32_t footSensor = 1;
    const int32_t headSensor = 2;
    const int32_t treeSensor = 3;
};

} //end of core
