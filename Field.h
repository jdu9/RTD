#ifndef FIELD_H
#define FIELD_H

#include <SFML/Graphics.hpp>

class Field
{
public:
    Field(sf::Vector2f center, float radius);

    sf::CircleShape mShape;
};

#endif // FIELD_H
