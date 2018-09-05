#pragma once

namespace math
{
    static const constexpr float pixelToMeter = 30.0f;
    static const constexpr float meterToPixel = 1.0f / pixelToMeter;

    inline float PixelToMeter(float pixel)
    {
        return pixel * pixelToMeter;
    }

    inline float MeterToPixel(float meter)
    {
        return meter * meterToPixel;
    }
}
