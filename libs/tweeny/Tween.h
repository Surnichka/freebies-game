#pragma once
#include <vector>
#include <cstdint>
#include <algorithm>
#include "Details.hpp"
#include "Curves.h"
#include <experimental/optional>

using namespace std::chrono_literals;

namespace libs
{

template<typename T>
class Tween
{
public:
    using OnStepFunc = std::function<void(Tween<T>& self)>;

    Tween<T>& addPoint(T point)
    {
        if(m_currentPoint == std::experimental::nullopt)
        {
            m_currentPoint = point;
        }

        m_corePoints.emplace_back( tweeny::details::CorePoint<T>(point) );
        return *this;
    }

    Tween<T>& during(std::chrono::milliseconds duration)
    {
        auto secondCP = std::next(m_corePoints.begin(), 1);
        if(secondCP == m_corePoints.end())
        {
            return *this;
        }

        m_duration += duration;
        m_elapsed = m_duration;

        auto iter = std::find_if(secondCP, m_corePoints.end(),
                                 [](const auto& cp)
        {
            return cp.duration == std::chrono::milliseconds(0);
        });

        if(iter == m_corePoints.end())
        {
            m_corePoints.back().duration += duration;
            return *this;
        }

        auto notSetCount = std::distance(iter, m_corePoints.end());
        auto averageDuration = (duration / notSetCount);
        for(auto it = iter; it != m_corePoints.end(); ++it)
        {
            it->duration = averageDuration;
        }
        return *this;
    }

    Tween<T>& via(const tweeny::ease::Function& easing)
    {
        m_corePoints.back().easing = easing;
        return *this;
    }

    Tween<T>& onStep(const OnStepFunc& onStep)
    {
        m_onStep = onStep;
    }

    T stepBy(std::chrono::milliseconds dt)
    {
        if(m_elapsed != m_duration)
        {
            m_currentPoint = seekTo(m_elapsed + dt);

            if(nullptr != m_onStep)
            {
                m_onStep(*this);
            }
        }
        return peek();
    }

    T seekTo(std::chrono::milliseconds timePoint)
    {
        m_elapsed = timePoint;
        m_elapsed = std::min(m_duration, m_elapsed);
        m_elapsed = std::max(std::chrono::milliseconds::zero(), m_elapsed);

        m_currentPoint = interpolateTo(m_elapsed);
        return peek();
    }

    std::chrono::milliseconds getProgress() const
    {
        return m_elapsed;
    }

    std::chrono::milliseconds getDuration() const
    {
        return m_duration;
    }

    bool hasValue() const
    {
        return m_currentPoint != std::experimental::nullopt;
    }

    T peek() const
    {
        if(std::experimental::nullopt == m_currentPoint)
        {
            throw std::runtime_error("Trying to peek value in Tween that is not constructed yet!");
        }
        else
        {
            return m_currentPoint.value();
        }
    }

    bool isForward() const
    {
        return m_goForward;
    }

    void goForward(bool shouldGoForward)
    {
        m_goForward = shouldGoForward;
        interpolateTo(m_elapsed);
    }

    void clear()
    {
        m_corePoints.clear();
        m_onStep = nullptr;
        m_duration = 0ms;
        m_elapsed = 0ms;
        m_currentPoint = std::experimental::nullopt;
        m_goForward = true;
    }

    bool empty() const
    {
        return m_corePoints.empty();
    }

    void start()
    {
        m_elapsed = 0ms;
    }

private:
    T interpolateTo(std::chrono::milliseconds timePoint)
    {
        if(false == m_goForward)
        {
            timePoint = m_duration - timePoint;
        }
        std::chrono::milliseconds pastTime = 0ms;
        size_t curIdx = 0;
        for(size_t i = 1; i < m_corePoints.size() - 1; i++)
        {
            const auto& cp = m_corePoints[i];
            auto nextPastTime = cp.duration;
            if(timePoint >= pastTime && timePoint <= (pastTime + nextPastTime))
            {
                break;
            }
            pastTime += nextPastTime;
            curIdx++;
        }

        size_t nextIdx = std::min(curIdx + 1, m_corePoints.size() - 1);

        ///Find if any user set easing from curIdx ahead.
        tweeny::ease::Function easingFunction = [&]()->std::function<double(double)>
        {
            auto hasEasingComp = [](const auto& cp) { return cp.easing != nullptr; };
            auto easeEndIt = std::find_if(m_corePoints.begin() + nextIdx, m_corePoints.end(), hasEasingComp);
            auto easeBeginIt = std::find_if(m_corePoints.begin(), easeEndIt, hasEasingComp);

            if(easeEndIt == m_corePoints.end())
            {
                return tweeny::ease::linear;
            }
            else
            {
                return easeEndIt->easing;
            }
        }();

        auto elapsed = timePoint - pastTime;
        auto currentPoint = tweeny::rangeMap(elapsed,
                                          0ms,
                                          m_corePoints.at(nextIdx).duration,
                                          m_corePoints.at(curIdx).point,
                                          m_corePoints.at(nextIdx).point,
                                          easingFunction);
        return currentPoint;
    }

private:
    bool m_goForward = true;
    std::experimental::optional<T> m_currentPoint;
    std::chrono::milliseconds m_duration = 0ms;
    std::chrono::milliseconds m_elapsed = 0ms;

    OnStepFunc m_onStep;
    std::vector<tweeny::details::CorePoint<T>> m_corePoints;
};

} //end of libs
