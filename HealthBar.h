#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <Thor/Animations.hpp>

#include "ResourceManager.h"

class HealthBar
{
    public:
        HealthBar();
        sf::RectangleShape getShape();
        void setPosition(sf::Vector2f);
        void setPercentage(float);

    private:
        sf::RectangleShape mShape;
};

inline sf::RectangleShape HealthBar::getShape()
{
    return mShape;
}

#endif // HEALTHBAR_H
