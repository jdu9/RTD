#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics/Sprite.hpp>

#include "ResourceManager.h"
#include "MyHelperFunctions.h"
#include "Creep.h"

class Creep;

class Projectile
{
public:
    Projectile( Creep& t, float s, sf::Vector2f );
    void update();

    sf::Sprite getSprite();
    Creep& getTarget();

    bool collides();

private:
    Creep& mTarget;
    sf::Sprite mSprite;
    float mSpeed;
};

inline sf::Sprite Projectile::getSprite()
{
    return mSprite;
}

inline Creep& Projectile::getTarget()
{
    return mTarget;
}

#endif // PROJECTILE_H
