#pragma once
#include <functional>
#include <math.h>

namespace libs
{
namespace tweeny
{
namespace ease
{

using Function = std::function<double(double)>;
double linear(double t);
double inSine( double t );
double outSine( double t );
double inOutSine( double t );
double inQuad( double t );
double outQuad( double t );
double inOutQuad( double t );
double inCubic( double t );
double outCubic( double t );
double inOutCubic( double t );
double inQuart( double t );
double outQuart( double t );
double inOutQuart( double t );
double inQuint( double t );
double outQuint( double t );
double inOutQuint( double t );
double inExpo( double t );
double outExpo( double t );
double inOutExpo( double t );
double inCirc( double t );
double outCirc( double t );
double inOutCirc( double t );
double inBack( double t );
double outBack( double t );
double inOutBack( double t );
double inElastic( double t );
double outElastic( double t );
double inOutElastic( double t );
double inBounce( double t );
double outBounce( double t );
double inOutBounce( double t );

} //end of ease
} //end of tweeny
} //end of libs
