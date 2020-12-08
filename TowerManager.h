#ifndef TOWERMANAGER_H
#define TOWERMANAGER_H

#include "Player.h"
#include "Map.h"
#include "Wave.h"
#include "Tower.h"

class Tower;
class Wave;

class TowerManager
{
public:
    TowerManager(sf::RenderWindow& window, Player& player, Wave& wave, Map& map);

    void addTower();

    void update();

    void draw();

    void reset();

    void uncoverAllTowers();

private:
    std::vector<std::unique_ptr<Tower>> mTowers;

    sf::RenderWindow& mWindow;
    Player& mPlayer;
    Wave& mWave;
    Map& mMap;
};

#endif // TOWERMANAGER_H
