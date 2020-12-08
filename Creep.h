#ifndef CREEP_H
#define CREEP_H

#include <vector>
#include <memory>
#include <math.h>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "MyHelperFunctions.h"
#include "ResourceManager.h"
#include "HealthBar.h"
#include "Player.h"

#include <SFML/Graphics.hpp>
#include <Thor/Animations.hpp>

class Creep
{
public:
    Creep(float s, int h, bool f, sf::Vector2f startPos, sf::RenderWindow& window, Player& player);

    void setPosition(sf::Vector2f);
    void setSize(sf::Vector2f s);
    void incrementPathPosition();
    void setSpeed(float);

    void move(const std::vector<sf::Vector2i>&);

    sf::Vector2f getPosition() const;
    int getPathPosition() const;
    float getSpeed() const;
    sf::Sprite getSprite();
    sf::Sprite& getSpriteRef();
    bool isFlying() const;
    bool isAlive() const;
    bool attack(int);
    void kill();
    void draw();

    HealthBar mHpbar;

    virtual Creep* clone() const = 0;

protected:
    void setFlying(bool);
    int mHitpoints;
    const int mHitpoints_default;
    sf::Vector2f mPosition;
    sf::Sprite mSprite;
    thor::Animator<sf::Sprite, std::string> mAnimator;

private:
    sf::Vector2f mSize;
    int mPathPosition;
    float mSpeed;

    bool mFlying;
    bool mAlive;

    // testing

    sf::Clock mFrameClock;

    sf::RenderWindow& mWindow;
    Player& mPlayer;
};

class Grunt : public Creep
{
    public:
        Grunt(int, sf::Vector2f startPos, sf::RenderWindow& window, Player& player);
        Creep* clone() const { return new Grunt(*this); }
};

class Bat : public Creep
{
    public:
        Bat(int, sf::Vector2f startPos, sf::RenderWindow& window, Player& player);
        Creep* clone() const { return new Bat(*this); }
};

inline void Creep::incrementPathPosition()
{
    ++mPathPosition;
}

inline void Creep::setSpeed(float a)
{
    mSpeed = a;
}

inline sf::Vector2f Creep::getPosition() const
{
    return mPosition;
}

inline int Creep::getPathPosition() const
{
    return mPathPosition;
}

inline float Creep::getSpeed() const
{
    return mSpeed;
}

inline sf::Sprite Creep::getSprite()
{
    return mSprite;
}

inline sf::Sprite& Creep::getSpriteRef()
{
    return mSprite;
}

inline bool Creep::isFlying() const
{
    return mFlying;
}

inline void Creep::setFlying(bool a)
{
    mFlying = a;
}

inline bool Creep::isAlive() const
{
    return mAlive;
}

#endif
