#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "ResourceManager.h"

class Checkpoint
{
public:
    Checkpoint(sf::Vector2i p, int number);

    void draw(sf::RenderWindow&);
    void drawText(sf::RenderWindow&);

    sf::Vector2i getPosition() const;
    sf::Vector2i getCenter() const;

    sf::Vector2i getSize() const;

private:
    sf::RectangleShape mShape;
    sf::Text mText;
    sf::Vector2i mPosition;

};

inline sf::Vector2i Checkpoint::getPosition() const
{
    return mPosition;
}

inline sf::Vector2i Checkpoint::getCenter() const
{
    return mPosition + sf::Vector2i(1,1);
}

inline sf::Vector2i Checkpoint::getSize() const
{
    return sf::Vector2i(3,3);
}

#endif // CHECKPOINT_H
