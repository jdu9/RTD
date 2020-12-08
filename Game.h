#ifndef GAME_H
#define GAME_H

#include "StateManager.h"
#include "MainGameState.h"
#include "MainMenuState.h"

#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Game
{
public:
    Game();
    ~Game() {}

    void run();

    void exit()
    {
        mExit = true;
    }

    sf::RenderWindow& getWindow()
    {
        return mWindow;
    }

private:
    bool mExit;

    sf::RenderWindow mWindow;

    StateManager mStateManager;

    sf::View mView;
};

#endif
