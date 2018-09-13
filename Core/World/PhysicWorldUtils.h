#pragma once
#include <memory>

class b2Body;
namespace core
{
    static const constexpr float physicWorldScale = 30.0f;

    float PixelToMeter(float pixel);
    float MeterToPixel(float meter);

    struct BodyDeleter
    {
        void operator()(b2Body* body);
    };
    using BodyPtr = std::unique_ptr<b2Body, BodyDeleter>;
} //end of core
