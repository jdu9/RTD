#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow& window, StateManager& theStateManager)
    : GameState(window, theStateManager)
{
    box = sfg::Box::Create( sfg::Box::Orientation::VERTICAL );

    box->Show(true);

    box->SetRequisition(sf::Vector2f(375,0));

    box->SetSpacing( 5.f );

    entrybefore = "";

    mStateManager.getGui().getDesktop().SetProperty( "*", "FontSize", 13 );

    auto title = sfg::Label::Create("RANDOM TD");

    auto subBox = sfg::Box::Create( sfg::Box::Orientation::HORIZONTAL );

    auto randomButton = sfg::Button::Create("seed");

    randomButton->SetId("randomize");

    title->SetId("title");

    mpButtonStart = sfg::Button::Create("Play");
    mStateManager.seed = thor::random(0, std::numeric_limits<unsigned long>::max());
    mpEntry = sfg::Entry::Create(std::to_string(mStateManager.seed));
    mpButtonExit = sfg::Button::Create("Exit");

    box->Pack( title );
    box->Pack( mpButtonStart );
    box->Pack( subBox );

    subBox->Pack( randomButton );
    subBox->Pack( mpEntry );

    box->Pack( mpButtonExit );

    mpButtonStart->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &MainMenuState::startGame, this ) );
    mpButtonExit->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &MainMenuState::exit, this ) );
    mpEntry->GetSignal( sfg::Entry::OnTextChanged ).Connect( std::bind( &MainMenuState::abc, this ) );
    randomButton->GetSignal( sfg::Button::OnLeftClick ).Connect( std::bind( &MainMenuState::randomize, this ) );

    mStateManager.getGui().getDesktop().Add(box);

    mStateManager.getGui().getDesktop().SetProperty( "Box > Button", "Color", sf::Color(255,255,255) );
    mStateManager.getGui().getDesktop().SetProperty( "Box > Button", "BackgroundColor", sf::Color(100,100,100) );
    mStateManager.getGui().getDesktop().SetProperty( "Box > Button:PRELIGHT", "BackgroundColor", sf::Color(130,130,130) );
    mStateManager.getGui().getDesktop().SetProperty( "#title", "FontSize", 35.f );
    mStateManager.getGui().getDesktop().SetProperty( "#title", "Color", sf::Color::Red );
    mStateManager.getGui().getDesktop().SetProperty( "#randomize", "BackgroundColor", sf::Color(80,80,80) );
    mpEntry->SetMaximumLength(20);

    mWindow.resetGLStates();
}

MainMenuState::~MainMenuState()
{

}

void MainMenuState::init(void* initializationData)
{

}

void MainMenuState::exit()
{
    mStateManager.exit();
}

void MainMenuState::update()
{
    mStateManager.getGui().getDesktop().Update( sf::seconds(1.0f / 60.0f).asSeconds() );
    box->SetPosition(sf::Vector2f(mWindow.getSize().x / 2.0f - box->GetRequisition().x / 2.0f, mWindow.getSize().y / 2.0f - box->GetRequisition().y / 2.0f));
}

void MainMenuState::draw()
{
    mStateManager.getGui().getSfgui().Display( mWindow );
    mWindow.display();
}

void MainMenuState::handleEvent(const sf::Event& event)
{
    mStateManager.getGui().getDesktop().HandleEvent( event );
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    {
        mWindow.close();
    }
}

void MainMenuState::inputRest()
{

}

void MainMenuState::startGame()
{
    std::string text = (std::string)mpEntry->GetText();
    if (!text.empty() && myn::is_number(text))
    {
        std::stringstream(text) >> mStateManager.seed;

        if (mStateManager.seed < 18446744073709551615) {
            thor::setRandomSeed(mStateManager.seed);
            mStateManager.removeGameState("MainMenuState");
            mStateManager.addGameState("MainGameState", std::unique_ptr<GameState>(new MainGameState(mWindow, mStateManager)));
            mStateManager.changeGameState("MainGameState", 0);
            box->Show(false);
        }
    }
}

void MainMenuState::goToOptions()
{

}

void MainMenuState::abc()
{
    std::string text = (std::string)mpEntry->GetText();
    if (!text.empty())
    {
        if (myn::is_number(text))
        {
            entrybefore = text;
            std::stringstream(text) >> mStateManager.seed;
            if (!(mStateManager.seed < 18446744073709551615)) {
                mStateManager.seed = 18446744073709551614;
                mpEntry->SetText("18446744073709551614");
                mpEntry->SetCursorPosition(entrybefore.size());
            }
        } else {
            mpEntry->SetText(entrybefore);
            mpEntry->SetCursorPosition(entrybefore.size());
        }
    }
    else
    {
        entrybefore = "";
    }
}

void MainMenuState::randomize()
{
    mStateManager.seed = thor::random(0, std::numeric_limits<unsigned long>::max());
    mpEntry->SetText(std::to_string(mStateManager.seed));
}
