#ifndef ROCK_H
#define ROCK_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "ResourceManager.h"
#include "MapObject.h"

class Rock : public MapObject
{
    public:
        Rock( sf::Vector2i, sf::Vector2i );
};

class HorizontalRock : public Rock
{
    public:
        HorizontalRock( sf::Vector2i p );
};

class VerticalRock : public Rock
{
    public:
        VerticalRock( sf::Vector2i p );
};

#endif
