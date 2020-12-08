#ifndef MOB_H
#define MOB_H

#include <vector>
#include <memory>
#include <math.h>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "MyHelperFunctions.h"
#include "ResourceManager.h"
#include "HealthBar.h"

#include <SFML/Graphics.hpp>
#include <Thor/Animation.hpp>

class Mob
{
    public:
                                                Mob(sf::Vector2f pos, float s, int h);

        void                                    setPosition(sf::Vector2f);
        void                                    setSize(sf::Vector2f s);
        void                                    incrementPathPosition();
        void                                    setSpeed(float);

        sf::Vector2f                            move(const std::vector<sf::Vector2i>&);

        sf::Vector2f                            getPosition() const;
        int                                     getPathPosition() const;
        float                                   getSpeed() const;
        sf::Sprite                              getSprite();
        sf::Sprite&                             getSpriteRef();
        bool                                    isFlying() const;
        bool                                    isAlive() const;
        bool                                    attack(int);
        void                                    kill();

        HealthBar                               hpbar;

    protected:
        void                                    setFlying(bool);
        int                                     hitpoints;
        const int                               hitpoints_default;
        sf::Vector2f                            position;

    private:
        sf::Vector2f                            size;
        int                                     pathPosition;
        float                                   speed,
                                                diagonalspeed;
        sf::Sprite                              sprite;

        bool                                    flying;
        bool                                    alive;

        // testing

        sf::Clock                               frameClock;

        thor::Animator<sf::Sprite, std::string> animator;
};

class Grunt : public Mob
{
    public:
        Grunt(sf::Vector2f, int);
};

inline void Mob::incrementPathPosition()
{
    ++pathPosition;
}

inline void Mob::setSpeed(float a)
{
    speed = a;
    diagonalspeed = std::sqrt(std::pow(speed, 2.0f) / 2.0f);
}

inline sf::Vector2f Mob::getPosition() const
{
    return position;
}

inline int Mob::getPathPosition() const
{
    return pathPosition;
}

inline float Mob::getSpeed() const
{
    return speed;
}

inline sf::Sprite Mob::getSprite()
{
    return sprite;
}

inline sf::Sprite& Mob::getSpriteRef()
{
    return sprite;
}

inline bool Mob::isFlying() const
{
    return flying;
}

inline void Mob::setFlying(bool a)
{
    flying = a;
}

inline bool Mob::isAlive() const
{
    return alive;
}

#endif
