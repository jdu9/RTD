#include "MainGameState.h"

MainGameState::MainGameState( sf::RenderWindow& window, StateManager& theStateManager )
    : GameState(window, theStateManager), mMap(Map(thor::random(20,45), thor::random(20,45))), mPlayer(mMap), mWave(mMap, mPlayer, mWindow), mTowerManager(mWindow, mPlayer, mWave, mMap)
{
    mWindow.clear( sf::Color::Black );

    mWindow.display();

    mpLabel_stats = sfg::Label::Create( "" );

    mpLabel_stats->Show(true);

    mStateManager.getGui().getDesktop().Add( mpLabel_stats );

    auto button = sfg::Button::Create("");

    mStateManager.getGui().getDesktop().Add( button );

    mPlayer.addGold(60);
    mPlayer.addLives(15);

    mStateManager.getGui().getDesktop().SetProperty( "*", "FontSize", 23 );

    if (!mMap.createMap())
        return;

    // set basic window properties
    //mWindow.setVerticalSyncEnabled(true);

    if (!generateMap())
        return;

    mWave.init();

    // mWave = std::unique_ptr<Wave>(new Wave(*mMap.get(), mPlayer));

    mGrass.setTexture(ResourceManager::grass);
    mGrass.setTextureRect(sf::IntRect(0, 0, (int) getMap().getWidth() * 50,  (int) getMap().getHeight() * 50));

    mPlayer.getView().setSize(mWindow.getSize().x, mWindow.getSize().y);
    mPlayer.getView().setCenter(getMap().getWidth() * 50.f / 2.f, getMap().getHeight() * 50.f / 2.f);

    shape_ptr ptr(new sf::RectangleShape(sf::Vector2f(100,100)));
    ptr->setPosition(sf::Vector2f(0, 0));
    ptr->setFillColor(sf::Color::Red);
    mShapes.push_back(std::move(ptr));

    mWave.next();

    mMap.updatePathGround();
}

MainGameState::~MainGameState()
{

}

void MainGameState::init( void* initializationData )
{
    const std::string* Difficulty = (std::string*) initializationData;
}

void MainGameState::exit()
{
    ResourceManager::music.stop();
}

void MainGameState::handleEvent(const sf::Event& event)
{
    mStateManager.getGui().getDesktop().HandleEvent( event );
    switch (event.type)
    {
        case sf::Event::Resized:
            mPlayer.getView().setSize(mWindow.getSize().x, mWindow.getSize().y);
            break;
        case sf::Event::Closed:
            mWindow.close();
            break;
        case sf::Event::KeyPressed:
        {
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        mStateManager.removeGameState("MainGameState");
                        mStateManager.addGameState("MainMenuState", std::unique_ptr<GameState>(new MainMenuState(mWindow, mStateManager)));
                        mStateManager.changeGameState("MainMenuState", 0);
                        mpLabel_stats->Show(false);
                        break;
                    case sf::Keyboard::F:
                        mFullscreen = !mFullscreen;
                        mWindow.create(sf::VideoMode(mMode.getDesktopMode().width, mMode.getDesktopMode().height), "RANDOM TD", (mFullscreen ? sf::Style::Fullscreen : sf::Style::Default), sf::ContextSettings(0,0,8,2,0));
                        mPlayer.getView().setSize(mWindow.getSize().x, mWindow.getSize().y);
                        break;
                    case sf::Keyboard::R:
                        mPlayer.getView().setSize((sf::Vector2f)mWindow.getSize());
                        mPlayer.getView().setRotation(0);
                        mPlayer.getView().setCenter(getMap().getWidth() * 50.f / 2.f, getMap().getHeight() * 50.f / 2.f);
                        break;
                    case sf::Keyboard::G:
                        mPlayer.addGold(15);
                        break;
                    case sf::Keyboard::Space:
                        mWave.go();
                        break;
                    default:
                        break;
                }
                sf::Vector2f worldPos = mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow)) - sf::Vector2f(25.f, 25.f);
                worldPos = sf::Vector2f((float) ((int) worldPos.x - ((int) worldPos.x % 50)), (float) ((int) worldPos.y - ((int) worldPos.y % 50)));
                mShapes[0]->setPosition(worldPos);
                break;
        }
        case sf::Event::MouseMoved:
        {
            sf::Vector2f worldPos = mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow)) - sf::Vector2f(25.f, 25.f);
            worldPos = sf::Vector2f((float) ((int) worldPos.x - ((int) worldPos.x % 50)), (float) ((int) worldPos.y - ((int) worldPos.y % 50)));
            mShapes[0]->setPosition(worldPos);
            break;
        }
        default:
            break;
    }
    if (event.type == sf::Event::MouseWheelMoved)
    {
        if (event.mouseWheel.delta > 0)
            mPlayer.setZoomIn(true);
        if (event.mouseWheel.delta < 0)
            mPlayer.setZoomOut(true);
    }

    if (event.type == sf::Event::MouseButtonPressed)
    {
        mTowerManager.addTower();
    mMap.updatePathGround();
    }
}

void MainGameState::restInput()
{
    if (sf::Mouse::getPosition(mWindow).x < 50)
        mPlayer.setLeft(true);
    if (sf::Mouse::getPosition(mWindow).x > (int) mWindow.getSize().x - 50)
        mPlayer.setRight(true);
    if (sf::Mouse::getPosition(mWindow).y < 50)
        mPlayer.setUp(true);
    if ((int)sf::Mouse::getPosition(mWindow).y > (int) mWindow.getSize().y - 50)
        mPlayer.setDown(true);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        mPlayer.setUp(true);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        mPlayer.setDown(true);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        mPlayer.setLeft(true);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        mPlayer.setRight(true);
}

void MainGameState::update()
{
    mWave.update(mTowerManager);

    mPlayer.update();

    mStateManager.getGui().getDesktop().Update( sf::seconds(1.0f / 60.0f).asSeconds() );

    mTowerManager.update();
}

void MainGameState::draw()
{
    mWindow.clear(sf::Color(25,25,25));

    mWindow.setView(mPlayer.getView());

    mWindow.draw(mGrass);

//    Field test(sf::Vector2f(50.f,50.f), 50.f);
//
//    mWindow.draw(test.shape);

    for (size_t i = 0; i < mMap.getCheckpoints().size(); ++i) {
        mMap.getCheckpoints()[i].draw(mWindow);
    }

    for (size_t i = 0; i < mShapes.size(); ++i) {
        mWindow.draw(*mShapes[i]);
    }

    for (int i = 0; i < getMap().getHeight(); ++i) {
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(0, i * 50.f), sf::Color(255,255,255,10)),
            sf::Vertex(sf::Vector2f(getMap().getWidth() * 50.f, i * 50.f), sf::Color(255,255,255,45))
        };
        mWindow.draw(line, 2, sf::Lines);
    }

    for (int i = 0; i < getMap().getWidth(); ++i) {
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(i * 50.f, 0),  sf::Color(255,255,255,10)),
            sf::Vertex(sf::Vector2f(i * 50.f, getMap().getHeight() * 50.f), sf::Color(255,255,255,45))
        };
        mWindow.draw(line, 2, sf::Lines);
    }

    for (size_t i = 0; i < mGameObjects.size(); ++i) {
        mWindow.draw(mGameObjects[i]->getSprite());
    }

    mTowerManager.draw();

    mWave.draw(mWindow);

    for (size_t i = 0; i < getMap().getPath().size() && i != getMap().getPath().size() - 1; ++i) {
        sf::Vertex line[] =
        {
            sf::Vertex((sf::Vector2f)getMap().getPath()[i] * 50.f + sf::Vector2f(25.f,25.f), sf::Color(255,0,0,150)),
            sf::Vertex((sf::Vector2f)getMap().getPath()[i+1] * 50.f + sf::Vector2f(25.f,25.f), sf::Color(0,0,255,150))
        };

        mWindow.draw(line, 2, sf::Lines);
    }

    setLabels();

    mStateManager.getGui().getSfgui().Display( mWindow );

    mWindow.display();
}


bool MainGameState::generateMap()
{
    std::vector<sf::Vector2i> path;

    for (int i = 0, rand = thor::random(2,6); i < rand;)
    {
        Checkpoint cp = Checkpoint(sf::Vector2i(thor::random(0, (int) getMap().getWidth() - 3),thor::random(0, (int) getMap().getHeight() - 3)), i);

        if (i == rand - 1)
            cp = Checkpoint(sf::Vector2i(thor::random(0, (int) getMap().getWidth() - 3),thor::random(0, (int) getMap().getHeight() - 3)), -1);

        if (getMap().isPlaceableAt(cp.getPosition(), cp.getSize())) {
            getMap().setPlaceableAt(cp.getPosition(), cp.getSize(), false);
            getMap().getCheckpoints().push_back(cp);
            ++i;
        }
    }

    int maximum = (int) ( mMap.getWidth() * mMap.getHeight() / 8.0f / thor::random(3.5f,10.0f) + 0.5f );

    for (int i = 0, c = 0; i < maximum; ++c)
    {
        if (c > 2500)
            return false;

        std::unique_ptr<Rock> rock;

        if (thor::random(0,1))
            rock = std::unique_ptr<Rock>(new VerticalRock(sf::Vector2i(thor::random(0, (int) getMap().getWidth() - 2),thor::random(0, (int) getMap().getHeight() - 4))));
        else
            rock = std::unique_ptr<Rock>(new HorizontalRock(sf::Vector2i(thor::random(0, (int) getMap().getWidth() - 4),thor::random(0, (int) getMap().getHeight() - 2))));

        if (getMap().isPlaceableAt(rock->getPosition(), rock->getSize()))
        {
            getMap().setWalkableAt(rock->getPosition(), rock->getSize(), false);
            getMap().setPlaceableAt(rock->getPosition(), rock->getSize(), false);

            if (getMap().checkPath()) {
                mGameObjects.push_back(std::move(rock));
                ++i;
            } else {
                getMap().setWalkableAt(rock->getPosition(), rock->getSize(), true);
                getMap().setPlaceableAt(rock->getPosition(), rock->getSize(), true);
            }
        }
    }
    return true;
}

void MainGameState::setLabels()
{
        mpLabel_stats->SetText("Seed: "    + std::to_string( mStateManager.seed ) +
                               "\nLevel: " + std::to_string(mWave.getLevel()) +
                               "\nLives: " + std::to_string(mPlayer.getLives()) +
                               "\nGold: "  + std::to_string(mPlayer.getGold()) +
                               "\nTime till next wave: " + std::to_string( (int)( mWave.getTime().asSeconds() + 0.5f ) ) );

}


bool MainGameState::isWaveActive() const
{
    return mWave.isActive();
}

