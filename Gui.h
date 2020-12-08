#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics/RenderWindow.hpp>

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Desktop.hpp>
#include <SFGUI/Box.hpp>
#include <SFGUI/Button.hpp>
#include <SFGUI/Entry.hpp>
#include <SFGUI/Label.hpp>

class Gui
{
public:
    Gui() {}

    void mainMenu();
    void inGame();

    sfg::SFGUI& getSfgui();
    sfg::Desktop& getDesktop();

private:
    void reset();

    sfg::SFGUI mSfgui;
    sfg::Desktop mDesktop;

    sf::RenderWindow mWindow;

private:
    // MainMenu

    sfg::Box::Ptr box;

    // buttons:
    sfg::Button::Ptr mpButtonStart;
    sfg::Button::Ptr mpButtonExit;
    sfg::Entry::Ptr mpEntry;


    // InGame



};

inline sfg::SFGUI& Gui::getSfgui()
{
    return mSfgui;
}

inline sfg::Desktop& Gui::getDesktop()
{
    return mDesktop;
}


#endif // GUI_H
