#pragma once
#include "Easing.h"
#include <vector>
#include <chrono>

namespace libs
{
namespace tweeny
{

///Get value between range [start, end] - by progress factor (t) - between 0.0 and 1.0
template<typename T>
T lerp(T start, T end, double t)
{
    return (start + (t * (end-start)));
}

///Put in value as percent between range [inStart, inEnd] to range [outStart, outEnd],
/// also supporting easing functions
template<typename U>
inline U rangeMap(double in,
                  double inStart,
                  double inEnd,
                  U outStart,
                  U outEnd,
                  const ease::Function& easing = nullptr)
{

    auto t = in - inStart;
    t = t / (inEnd - inStart);
    t = (easing == nullptr) ? ease::linear(t) : easing(t);
    return lerp(outStart, outEnd, t);
}

///Overload for range map starting with std::chrono::milliseconds
template<typename T>
inline T rangeMap(std::chrono::milliseconds in,
                  std::chrono::milliseconds inStart,
                  std::chrono::milliseconds inEnd,
                  T outStart,
                  T outEnd,
                  const ease::Function& easing = nullptr)
{
    auto inCount = in.count();
    auto inStartCount = inStart.count();
    auto inEndCount = inEnd.count();
    return rangeMap(inCount,
                    inStartCount,
                    inEndCount,
                    outStart,
                    outEnd,
                    easing);
}

///Overload for range map ending with std::chrono::milliseconds
template<typename T>
inline std::chrono::milliseconds rangeMap(T in,
                                          T inStart,
                                          T inEnd,
                                          std::chrono::milliseconds outStart,
                                          std::chrono::milliseconds outEnd,
                                          const ease::Function& easing = nullptr)
{
    auto outStartCount = outStart.count();
    auto outEndCount = outEnd.count();
    auto result = rangeMap(in,
                           inStart,
                           inEnd,
                           outStartCount,
                           outEndCount,
                           easing);

    return std::chrono::milliseconds(result);
}

namespace details
{

template<typename T>
struct CorePoint
{
    CorePoint() = default;
    CorePoint(T p) : point(p)
    {}

    T point;
    std::chrono::milliseconds duration = std::chrono::milliseconds(0);
    tweeny::ease::Function easing;
};

} //end of details
} //end of tweeny
} //end of libs
