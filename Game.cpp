#include "Game.h"

Game::Game() : mExit(false), mWindow(sf::VideoMode(sf::VideoMode::getDesktopMode().width,sf::VideoMode::getDesktopMode().height), "RANDOM TD", sf::Style::Default, sf::ContextSettings(0,0,8,2,0)), mView(sf::FloatRect(0,0,800,600))
{
    if (!ResourceManager::init())
        return;

    // add game states to state manager
    //mStateManager.addGameState("MainMenuState", new MainMenuState(mWindow, mStateManager));
    //mStateManager.addGameState("MainGameState", std::unique_ptr<GameState>(new MainGameState(mWindow, mStateManager)));
    mStateManager.addGameState("MainMenuState", std::unique_ptr<GameState>(new MainMenuState(mWindow, mStateManager)));
    //mStateManager.addGameState("GameOverState", new GameOverState(mWindow, mStateManager));

    // set top game state
    mStateManager.changeGameState("MainMenuState", 0);

    mWindow.setFramerateLimit(0);

    mWindow.setView(mView);
}

void Game::run()
{
    sf::Clock clock;
    mWindow.setVisible(true);
    mWindow.setActive(true);

    const sf::Time deltaTime = sf::seconds(1.0f / 60.0f);

    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen() && !mExit)
    {
        // process window events
        sf::Event event;
        while (mWindow.pollEvent(event))
        {
            mStateManager.handleEvent(event);
            if (event.type == sf::Event::Closed)
            {
                exit();
            }
        }

        if (!mStateManager.isActive())
        {
            exit();
        }

        mStateManager.restInput();

        // update game state
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate >= deltaTime)
        {
            timeSinceLastUpdate = timeSinceLastUpdate - deltaTime;
            mStateManager.update();
        }

        // clear window
        mWindow.clear(sf::Color::Black);

        // render game state
        mStateManager.draw();

        // display window
        mWindow.display();
    }
}
