#ifndef MAINGAMESTATE_H
#define MAINGAMESTATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <typeinfo>

#include <Thor/Animations.hpp>
#include <Thor/Math.hpp>
#include <Thor/Input.hpp>
#include <Thor/Input/EventSystem.hpp>

#include <SFGUI/SFGUI.hpp>

#include "ResourceManager.h"
#include "Rock.h"
#include "Creep.h"
#include "Tower.h"
#include "Wave.h"
#include "Player.h"
#include "MyHelperFunctions.h"
#include "Wave.h"
#include "Map.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "TowerManager.h"

class Tower;
class MapObject;

typedef std::unique_ptr<sf::Shape> shape_ptr;
typedef std::unique_ptr<MapObject> go_ptr;
typedef std::unique_ptr<Tower> tower_ptr;

class MainGameState : public GameState
{
public:
    MainGameState(sf::RenderWindow& window, StateManager& theStateManager);
    ~MainGameState();

    // initializes state
    virtual void init(void* intializationData);

    // shuts the game state down
    virtual void exit();

    // updates game state
    virtual void update();

    virtual void handleEvent(const sf::Event& event);

    virtual void restInput();

    virtual void draw();

    Map& getMap();
    Player& getPlayer();

    void uncoverAllTowers();

    bool isWaveActive() const;

private:
    void processEvents();
    void placeTower();

    bool generateMap();

    void setLabels();

private:
    Map mMap;

    bool mFullscreen;
    sf::VideoMode mMode;

    TowerManager mTowerManager;

    sf::Sprite mGrass;
    std::vector<shape_ptr> mShapes;
    std::vector<go_ptr> mGameObjects;

    Wave mWave;

    Player mPlayer;

    sfg::Label::Ptr mpLabel_stats;
};

inline Map& MainGameState::getMap()
{
    return mMap;
}

inline Player& MainGameState::getPlayer()
{
    return mPlayer;
}

#endif
