#pragma once
#include "Easing.h"
#include <chrono>

namespace math
{
    
///Get value between range [start, end] - by progress factor (t) - between 0.0 and 1.0
template<typename T>
T Lerp(T start, T end, double t)
{
    return (start + (t * (end-start)));
}

///Put in value as percent between range [inStart, inEnd] to range [outStart, outEnd],
/// also supporting easing functions
template<typename U>
inline U RangeMap(double in,
                  double inStart,
                  double inEnd,
                  U outStart,
                  U outEnd,
                  const ease::Function& easing = nullptr)
{

    auto t = in - inStart;
    t = t / (inEnd - inStart);
    t = (easing == nullptr) ? ease::linear(t) : easing(t);
    return Lerp(outStart, outEnd, t);
}

///Overload for range map starting with std::chrono::milliseconds
template<typename T>
inline T RangeMap(std::chrono::milliseconds in,
                  std::chrono::milliseconds inStart,
                  std::chrono::milliseconds inEnd,
                  T outStart,
                  T outEnd,
                  const ease::Function& easing = nullptr)
{
    auto inCount = in.count();
    auto inStartCount = inStart.count();
    auto inEndCount = inEnd.count();
    return RangeMap(inCount,
                    inStartCount,
                    inEndCount,
                    outStart,
                    outEnd,
                    easing);
}

///Overload for range map ending with std::chrono::milliseconds
template<typename T>
inline std::chrono::milliseconds RangeMap(T in,
                                          T inStart,
                                          T inEnd,
                                          std::chrono::milliseconds outStart,
                                          std::chrono::milliseconds outEnd,
                                          const ease::Function& easing = nullptr)
{
    auto outStartCount = outStart.count();
    auto outEndCount = outEnd.count();
    auto result = RangeMap(in,
                           inStart,
                           inEnd,
                           outStartCount,
                           outEndCount,
                           easing);

    return std::chrono::milliseconds(result);
}

} //end of math
