#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <string>
#include <map>
#include <memory>
#include <SFML/Window.hpp>
#include "GameState.h"
#include "Gui.h"

class GameState;

class StateManager
{
public:
    StateManager() {}

    ~StateManager() {}

    // add a game state
    void addGameState(const std::string name, std::unique_ptr<GameState> gameState);

    void removeGameState(const std::string name);

    // change game state
    void changeGameState(const std::string name, void* initializationData);

    // update game state
    void update() ;

    // draw current game state
    void draw();

    void handleEvent(const sf::Event& event);

    void restInput();

    bool isActive()
    {
        return active;
    }

    void exit()
    {
        active = false;
    }

    Gui& getGui()
    {
        return mGui;
    }

    unsigned long seed;

private:
    std::map<std::string, std::unique_ptr<GameState>> mStates;
    GameState* mCurrentGameState;

    Gui mGui;

    bool active;
};

#endif // STATEMANAGER_H
