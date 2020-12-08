#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

#include "ResourceManager.h"

class MapObject
{
protected:
    MapObject( sf::Vector2i, sf::Vector2i );

    // Modifies both actual values and the interpreted ones
    void setPosition( sf::Vector2i );
    void setSize( sf::Vector2i );
    void move( sf::Vector2i );

public:
    sf::Vector2i getPosition() const;
    sf::Vector2i getSize() const;
    sf::Vector2f getSpritePosition() const;
    sf::Vector2f getSpriteSize() const;
    sf::Sprite getSprite() const;

protected:
    sf::Sprite mSprite;
    sf::Vector2i mPosition;
    sf::Vector2i mSize;
};

class AnimatedMapObject : public MapObject
{
protected:
    AnimatedMapObject( sf::Vector2i p, sf::Vector2i s );
    sf::Time restartClock();

protected:
    thor::Animator<sf::Sprite, std::string> mAnimator;

private:
    sf::Clock mFrameClock;
};

inline sf::Vector2i MapObject::getPosition() const
{
    return mPosition;
}

inline sf::Vector2i MapObject::getSize() const
{
    return mSize;
}

inline sf::Vector2f MapObject::getSpritePosition() const
{
    return mSprite.getPosition();
}

inline sf::Vector2f MapObject::getSpriteSize() const
{
    return sf::Vector2f(mSprite.getGlobalBounds().width, mSprite.getGlobalBounds().height);
}

inline sf::Sprite MapObject::getSprite() const {
    return mSprite;
}

inline sf::Time AnimatedMapObject::restartClock() {
    return mFrameClock.restart();
}

#endif
