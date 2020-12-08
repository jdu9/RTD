#include "TowerManager.h"

TowerManager::TowerManager(sf::RenderWindow& window, Player& player, Wave& wave, Map& map)
: mWindow(window), mPlayer(player), mWave(wave), mMap(map)
{

}

void TowerManager::addTower()
{
    if (mPlayer.getGold() - 5 >= 0) {
        sf::Vector2f worldPos = mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow)) - sf::Vector2f(25.f, 25.f);
        worldPos = sf::Vector2f((float) ((int) worldPos.x - ((int) worldPos.x % 50)), (float) ((int) worldPos.y - ((int) worldPos.y % 50)));
        if (mMap.isPlaceableAt((sf::Vector2i)(worldPos / 50.f), sf::Vector2i(2, 2))) {
            std::unique_ptr<Tower> ptr(new CrossbowTower((sf::Vector2i)(worldPos / 50.f), sf::Vector2i(2,2), mWave));
            mMap.setWalkableAt(ptr->getPosition(), ptr->getSize(), false);
            if (mMap.checkPath()) {
                mMap.setPlaceableAt(ptr->getPosition(), ptr->getSize(), false);
                mTowers.push_back(std::move(ptr));
                mPlayer.addGold(-5);
//                if (!mWave.isActive())
//                    mMap.updatePathGround();
            } else {
                mMap.setWalkableAt(ptr->getPosition(), ptr->getSize(), true);
            }
        }
    }
}

void TowerManager::update()
{
    for (size_t i = 0; i < mTowers.size(); ++i) {
        mTowers[i]->updateTarget(mWave, sf::seconds(1.0f / 60.0f), mPlayer);
    }
}

void TowerManager::draw()
{
    for (size_t i = 0; i < mTowers.size(); ++i) {
        mWindow.draw(mTowers[i]->getSprite());
    }

    for (size_t i = 0; i < mTowers.size(); ++i) {
        mWindow.draw(mTowers[i]->getMoveable());
    }

    for (size_t i = 0; i < mTowers.size(); ++i) {
        mTowers[i]->drawProjectiles(mWindow);
    }
}

void TowerManager::reset()
{
    mTowers.clear();
}

void TowerManager::uncoverAllTowers()
{
    for ( size_t i = 0; i < mTowers.size(); ++i ) {
        if (mTowers[i]->isTransparent()) mTowers[i]->uncover();
    }
}
