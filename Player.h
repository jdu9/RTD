#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics/View.hpp>

#include "Map.h"

class Player
{
public:

    Player(Map& map) : mLives(0), mGold(0), mMap(map) {}

    sf::View getView() const;

    void addGold( int a );
    void addLives( int a );

    int getLives() const;
    int getGold() const;

    sf::View& getView();

    void update();

    void setUp(bool);
    void setDown(bool);
    void setLeft(bool);
    void setRight(bool);
    void setZoomIn(bool);
    void setZoomOut(bool);

private:

    // camera
    bool mLeft, mRight, mUp, mDown;
    bool mZoomIn, mZoomOut;

    int mLives;
    int mGold;
    // int diamond;

    sf::View mView;
    Map& mMap;
};

inline sf::View Player::getView() const
{
    return mView;
}

inline void Player::addGold( int a )
{
    mGold += a;
    if (mGold < 0)
        mGold -= a;
}

inline void Player::addLives( int a )
{
    mLives += a;
}

inline int Player::getLives() const
{
    return mLives;
}

inline int Player::getGold() const
{
    return mGold;
}

inline sf::View& Player::getView()
{
    return mView;
}

inline void Player::setUp(bool a)
{
    mUp = a;
}
inline void Player::setDown(bool a)
{
    mDown = a;
}
inline void Player::setLeft(bool a)
{
    mLeft = a;
}
inline void Player::setRight(bool a)
{
    mRight = a;
}
inline void Player::setZoomIn(bool a)
{
    mZoomIn = a;
}
inline void Player::setZoomOut(bool a)
{
    mZoomOut = a;
}

#endif
