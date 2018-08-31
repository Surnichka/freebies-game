#include "Easing.h"

namespace libs
{
namespace tweeny
{
namespace ease
{

double inSine( double t ) {
    return sin( 1.5707963 * t );
}

double outSine( double t ) {
    return 1 + sin( 1.5707963 * (--t) );
}

double inOutSine( double t ) {
    return 0.5 * (1 + sin( 3.1415926 * (t - 0.5) ) );
}

double inQuad( double t ) {
    return t * t;
}

double outQuad( double t ) {
    return t * (2 - t);
}

double inOutQuad( double t ) {
    return t < 0.5 ? 2 * t * t : t * (4 - 2 * t) - 1;
}

double inCubic( double t ) {
    return t * t * t;
}

double outCubic( double t ) {
    return 1 + (--t) * t * t;
}

double inOutCubic( double t ) {
    return t < 0.5 ? 4 * t * t * t : 1 + (--t) * (2 * (--t)) * (2 * t);
}

double inQuart( double t ) {
    t *= t;
    return t * t;
}

double outQuart( double t ) {
    t = (--t) * t;
    return 1 - t * t;
}

double inOutQuart( double t ) {
    if( t < 0.5 ) {
        t *= t;
        return 8 * t * t;
    } else {
        t = (--t) * t;
        return 1 - 8 * t * t;
    }
}

double inQuint( double t ) {
    double t2 = t * t;
    return t * t2 * t2;
}

double outQuint( double t ) {
    double t2 = (--t) * t;
    return 1 + t * t2 * t2;
}

double inOutQuint( double t ) {
    double t2;
    if( t < 0.5 ) {
        t2 = t * t;
        return 16 * t * t2 * t2;
    } else {
        t2 = (--t) * t;
        return 1 + 16 * t * t2 * t2;
    }
}

double inExpo( double t ) {
    return (pow( 2, 8 * t ) - 1) / 255;
}

double outExpo( double t ) {
    return 1 - pow( 2, -8 * t );
}

double inOutExpo( double t ) {
    if( t < 0.5 ) {
        return (pow( 2, 16 * t ) - 1) / 510;
    } else {
        return 1 - 0.5 * pow( 2, -16 * (t - 0.5) );
    }
}

double inCirc( double t ) {
    return 1 - sqrt( 1 - t );
}

double outCirc( double t ) {
    return sqrt( t );
}

double inOutCirc( double t ) {
    if( t < 0.5 ) {
        return (1 - sqrt( 1 - 2 * t )) * 0.5;
    } else {
        return (1 + sqrt( 2 * t - 1 )) * 0.5;
    }
}

double inBack( double t ) {
    return t * t * (2.70158 * t - 1.70158);
}

double outBack( double t ) {
    return 1 + (--t) * t * (2.70158 * t + 1.70158);
}

double inOutBack( double t ) {
    if( t < 0.5 ) {
        return t * t * (7 * t - 2.5) * 2;
    } else {
        return 1 + (--t) * t * 2 * (7 * t + 2.5);
    }
}

double inElastic( double t ) {
    double t2 = t * t;
    return t2 * t2 * sin( t * M_PI * 4.5 );
}

double outElastic( double t ) {
    double t2 = (t - 1) * (t - 1);
    return 1 - t2 * t2 * cos( t * M_PI * 4.5 );
}

double inOutElastic( double t ) {
    double t2;
    if( t < 0.45 ) {
        t2 = t * t;
        return 8 * t2 * t2 * sin( t * M_PI * 9 );
    } else if( t < 0.55 ) {
        return 0.5 + 0.75 * sin( t * M_PI * 4 );
    } else {
        t2 = (t - 1) * (t - 1);
        return 1 - 8 * t2 * t2 * sin( t * M_PI * 9 );
    }
}

double inBounce( double t ) {
    return pow( 2, 6 * (t - 1) ) * abs( sin( t * M_PI * 3.5 ) );
}

double outBounce( double t ) {
    return 1 - pow( 2, -6 * t ) * abs( cos( t * M_PI * 3.5 ) );
}

double inOutBounce( double t ) {
    if( t < 0.5 ) {
        return 8 * pow( 2, 8 * (t - 1) ) * abs( sin( t * M_PI * 7 ) );
    } else {
        return 1 - 8 * pow( 2, -8 * t ) * abs( sin( t * M_PI * 7 ) );
    }
}

double linear(double t)
{
    return t;
}

} //end of ease
} //end of tweeny
} //end of libs
