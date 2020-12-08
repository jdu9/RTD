#include "Gui.h"

void Gui::mainMenu()
{
    box = sfg::Box::Create( sfg::Box::Orientation::VERTICAL );

    box->Show(true);

    box->SetRequisition(sf::Vector2f(375,0));

    box->SetSpacing( 5.f );

    getDesktop().SetProperty( "*", "FontSize", 13 );

    auto title = sfg::Label::Create("RANDOM TD");

    auto subBox = sfg::Box::Create( sfg::Box::Orientation::HORIZONTAL );

    auto randomButton = sfg::Button::Create("seed");

    randomButton->SetId("randomize");

    title->SetId("title");

    mpButtonStart = sfg::Button::Create("Play");
    mpEntry = sfg::Entry::Create("");
    mpButtonExit = sfg::Button::Create("Exit");

    box->Pack( title );
    box->Pack( mpButtonStart );
    box->Pack( subBox );

    subBox->Pack( randomButton );
    subBox->Pack( mpEntry );

    box->Pack( mpButtonExit );

    getDesktop().Add(box);

    getDesktop().SetProperty( "Box > Button", "Color", sf::Color(255,255,255) );
    getDesktop().SetProperty( "Box > Button", "BackgroundColor", sf::Color(100,100,100) );
    getDesktop().SetProperty( "Box > Button:PRELIGHT", "BackgroundColor", sf::Color(130,130,130) );
    getDesktop().SetProperty( "#title", "FontSize", 35.f );
    getDesktop().SetProperty( "#title", "Color", sf::Color::Red );
    getDesktop().SetProperty( "#randomize", "BackgroundColor", sf::Color(80,80,80) );
    mpEntry->SetMaximumLength(20);

    mWindow.resetGLStates();
}
