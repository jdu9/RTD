#ifndef WAVE_H
#define WAVE_H

#include <vector>
#include <memory>
#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include <Thor/Animations.hpp>

#include "Creep.h"
#include "Map.h"
#include "Player.h"
#include "TowerManager.h"

class TowerManager;
class Map;

class Wave
{
    public:
        Wave(Map&, Player&, sf::RenderWindow&);

        // begin next wave
        void next();

        // update wave
        void update(TowerManager& towerManager);

        // draw all creeps
        void draw( sf::RenderWindow& window );

        void init();

        int getLevel() const;
        int getRemaining() const;
        size_t countOnMap() const;
        bool allDead() const;
        sf::Time getTime() const;

        bool isActive() const;

        Creep* getCreep( int i );

        template <class T>
        std::unique_ptr<Creep> make(float hp);

        void pushToQueue(std::string cn, int level);

        void create();

        void pushRandomCreepToQueue(int i);

        void go();

    private:

        int mLevel;
        int mRemaining;
        std::vector<std::unique_ptr<Creep>> mCreepsOnMap;
        std::vector<std::unique_ptr<Creep>> mCreepList;

        sf::Time mTimeToNextWave;
        sf::Time mTimeToNextCreep;

        bool mActive;

        thor::Animator<sf::Sprite, std::string> mAnimator;

        sf::Clock mFrameClock;

        Map& mMap;
        Player& mPlayer;
        sf::RenderWindow& mWindow;
};

inline int Wave::getLevel() const
{
    return mLevel;
}

inline int Wave::getRemaining() const
{
    return mRemaining;
}

inline size_t Wave::countOnMap() const
{
    return mCreepsOnMap.size();
}

inline sf::Time Wave::getTime() const
{
    return mTimeToNextWave;
}

inline bool Wave::isActive() const
{
    return mActive;
}

inline void Wave::go()
{
    if (!mActive)
        mTimeToNextWave = sf::seconds(0);
}


#endif
