#pragma once

namespace math
{
    static const constexpr float physicWorldScale = 30.0f;

    inline float PixelToMeter(float pixel)
    {
        return pixel * (1.0f / physicWorldScale);
    }

    inline float MeterToPixel(float meter)
    {
        return meter * physicWorldScale;
    }
}
