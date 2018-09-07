#pragma once

namespace math
{
    static const constexpr float pixelToMeter = 1.0f / 30.0f;
    static const constexpr float meterToPixel = 30.0f;

    inline float PixelToMeter(float pixel)
    {
        return pixel * pixelToMeter;
    }

    inline float MeterToPixel(float meter)
    {
        return meter * meterToPixel;
    }
}
