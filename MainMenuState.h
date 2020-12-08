#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include <SFGUI/SFGUI.hpp>

#include <SFML/Graphics.hpp>

#include "GameState.h"
#include "MainGameState.h"
#include "StateManager.h"

class MainMenuState : public GameState
{
public:
    MainMenuState(sf::RenderWindow&, StateManager& theStateManager);

    virtual ~MainMenuState();

    virtual void init(void* initializationData);

    virtual void exit();

    virtual void update();

    virtual void draw();

    virtual void handleEvent(const sf::Event& event);

    virtual void inputRest();

    void startGame();

    void goToOptions();
    void abc();
    void randomize();

private:
    sfg::Box::Ptr box;

    // buttons:
    sfg::Button::Ptr mpButtonStart;
    sfg::Button::Ptr mpButtonExit;
    sfg::Entry::Ptr mpEntry;

    std::string entrybefore;

};

#endif // MAINMENUSTATE_H
