#pragma once

namespace core
{

struct Material
{
    float density;
    float friction;
    float restitution;

    static const Material Default;
    static const Material Metal;
    static const Material Stone;
    static const Material Wood;
    static const Material Glass;
    static const Material Rubber;
    static const Material Ice;
    static const Material Pumice;
    static const Material Polystyrene;
    static const Material Fabroc;
    static const Material Sponge;
    static const Material Air;
    static const Material Helium;
};



} //end of core
