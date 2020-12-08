#ifndef TOWER_H
#define TOWER_H

#include "MapObject.h"

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <Thor/Math.hpp>

#include "Projectile.h"
#include "MyHelperFunctions.h"
#include "Player.h"
#include "Wave.h"

class Wave;
class Projectile;

class Tower : public AnimatedMapObject
{
protected:
    Tower( sf::Vector2i, sf::Vector2i, float, Wave& wave );

public:
    void setPosition( sf::Vector2i p );
    void updateTarget( Wave& w, const sf::Time& deltaTime, Player& );
    void shoot( const sf::Time& deltaTime );

    sf::Sprite getMoveable() const;
    Projectile* getProjectile( int );

    void drawProjectiles( sf::RenderWindow& );

    void uncover();
    bool isTransparent() const;

protected:
    float getCooldown() const;
    sf::Sprite mMoveable;
    std::vector<std::unique_ptr<Projectile>> mProjectiles;
    Creep* mpTarget;
    Wave& mWave;

private:
    sf::Time mTime;
    float mCooldown;
    bool mTransparent;
};

class CrossbowTower : public Tower
{
    public:
        CrossbowTower( sf::Vector2i, sf::Vector2i, Wave& wave );
};

inline sf::Sprite Tower::getMoveable() const
{
    return mMoveable;
}

inline float Tower::getCooldown() const
{
    return mCooldown;
}

inline bool Tower::isTransparent() const
{
    return mTransparent;
}

#endif
