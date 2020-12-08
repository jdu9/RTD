#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include "StateManager.h"
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Desktop.hpp>

class StateManager;

// interface for state
class GameState
{
public:
    GameState(sf::RenderWindow& window, StateManager& stateManager) : mWindow(window), mStateManager(stateManager)
    {}

    // virtual destructor
    virtual ~GameState() {}

    // initialize state
    virtual void init(void *initializationData) = 0;

    // update game state
    virtual void update() = 0;

    // draw game state
    virtual void draw() = 0;

    // shut the game state down
    virtual void exit() = 0;

    virtual void handleEvent(const sf::Event& event) {}

    virtual void restInput() {}

protected:
    sf::RenderWindow& mWindow;
    StateManager& mStateManager;
};

#endif // GAMESTATE_H
