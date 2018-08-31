#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <experimental/optional>
#include <memory>

namespace libs
{
    
struct TextureWrapper
{
    using Ptr = std::shared_ptr<TextureWrapper>;
    std::unique_ptr<sf::Texture> texture;
}; 

} // end of libs
