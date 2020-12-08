#include "StateManager.h"

void StateManager::addGameState(const std::string name, std::unique_ptr<GameState> gameState)
{
    mStates[name] = std::move(gameState);
}

void StateManager::removeGameState(const std::string name)
{
    mStates[name].release();
}

void StateManager::changeGameState(const std::string name, void* initializationData = NULL)
{
    mCurrentGameState = mStates[name].get();
}

void StateManager::update()
{
    mCurrentGameState->update();
}

void StateManager::draw()
{
    mCurrentGameState->draw();
}

void StateManager::handleEvent(const sf::Event& event)
{
    mCurrentGameState->handleEvent(event);
}

void StateManager::restInput()
{
    mCurrentGameState->restInput();
}
