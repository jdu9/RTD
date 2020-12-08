#include "HealthBar.h"

HealthBar::HealthBar()
{
    mShape.setSize(sf::Vector2f(50.f, 5.f));
    mShape.setFillColor(sf::Color::Green);
}

void HealthBar::setPosition(sf::Vector2f pos)
{
    mShape.setPosition(sf::Vector2f(pos.x - mShape.getSize().x / 2.f + 25.f, pos.y));
}

void HealthBar::setPercentage(float a)
{
    if (a >= 0.05f) {
        mShape.setSize(sf::Vector2f(a * 50.f, 5.f));
        mShape.setFillColor(sf::Color(255 - 255 * a, 255 * a, 0));
    }
}
