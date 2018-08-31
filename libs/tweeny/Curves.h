#pragma once
#include "Details.hpp"

namespace libs
{
namespace tweeny
{
namespace curves
{

template<typename T>
inline T quadraticCurve(T p0, T p1, T p2, double t)
{
    auto point0 = lerp(p0, p1, t);
    auto point1 = lerp(p1, p2, t);
    return lerp(point0, point1, t);
}

template<typename T>
inline T cubicCurve(T p0, T p1, T p2, T p3, double t)
{
    auto point0 = quadraticCurve(p0, p1, p2, t);
    auto point1 = quadraticCurve(p1, p2, p3, t);
    return lerp(point0, point1, t);
}

} //end of curves
} //end of tweeny
} //end of libs
