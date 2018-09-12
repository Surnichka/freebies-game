#pragma once
#include "Material.h"
#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <Box2D/Dynamics/b2Body.h>

class b2World;
namespace core
{

class PhysicWorld
{
public:
    void Init();
    void Update();

    b2Body* CreateBox(const sf::FloatRect& box, b2BodyType bodyType);
    void RemoveFromWorld(b2Body* body);

    std::unique_ptr<b2World>& GetB2World();
private:
    std::unique_ptr<b2World> m_world;
};

} //end of core
