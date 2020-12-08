#include "Field.h"

Field::Field(sf::Vector2f center, float radius)
: mShape(radius)
{
    mShape.setOrigin(radius, radius);
    mShape.setPosition(center);
    mShape.setFillColor(sf::Color(0,0,255,75));
    mShape.setOutlineThickness(1.f);
    mShape.setOutlineColor(sf::Color(250, 150, 100));
}
