#pragma once
#include "Material.h"
#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <Box2D/Dynamics/b2Body.h>

class b2World;
namespace core
{

class PWorld
{
public:
    void Init();

    void Update();
    b2Body* CreatePolygonBody(const sf::FloatRect& box, b2BodyType bodyType,
                                core::Material material = core::Material::Air);

    void DeleteFromWorld(b2Body* body);
private:
    std::unique_ptr<b2World> m_world;
};

} //end of core
