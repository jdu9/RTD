#include "Wave.h"

Wave::Wave(Map& m, Player& p, sf::RenderWindow& window)
: mLevel (0), mMap(m), mPlayer(p), mWindow(window)
{
    std::vector<sf::IntRect> rects_crossbow;

    for (int i = 1; i < 15; ++i)
        rects_crossbow.push_back(sf::IntRect (2 + i * 56, 2, 54, 57));

    thor::FrameAnimation walk;

    for (size_t i = 0; i < rects_crossbow.size(); ++i)
        walk.addFrame(1.f, rects_crossbow[i]);

    mAnimator.addAnimation("walk", walk, sf::seconds(1.f));

    mTimeToNextWave = sf::seconds(15.0f);
}

void Wave::init()
{
    for (int i = 1; i < 6; ++i) {
        pushRandomCreepToQueue(i);
    }
}

void Wave::next()
{
    ++mLevel;

    mActive = false;

    sf::operator+=(mTimeToNextWave, sf::seconds(8.0f));
    mTimeToNextCreep = sf::seconds(0.0f);
    mRemaining = 7 + mLevel;
}

void Wave::update(TowerManager& towerManager)
{
    if (mActive) {
        sf::operator-=(mTimeToNextCreep, sf::seconds(1.0f/60.0f));
        if (mRemaining == 0 && allDead()) {
            mCreepList.erase(mCreepList.begin());
            next();
            pushRandomCreepToQueue(mLevel);
            mPlayer.addGold(mLevel * 5);
            towerManager.uncoverAllTowers();
            mMap.updatePathGround();
        } else {
            if (mRemaining != 0 && mTimeToNextCreep.asSeconds() <= 0.0f) {
                if (mRemaining == 7 + mLevel)
                    towerManager.uncoverAllTowers();
                create();
                mTimeToNextCreep = sf::seconds(1.0f);
                --mRemaining;
            }
            for (size_t i = 0; i < mCreepsOnMap.size(); ++i) {
                if (mCreepsOnMap[i]->isAlive()) {
                    mCreepsOnMap[i]->move(mMap.getPath());
                }
            }
        }
    } else {
        sf::operator-=(mTimeToNextWave, sf::seconds(1.0f/60.0f));
        if (mTimeToNextWave.asSeconds() <= 0.0f) {
            if (mCreepList[mLevel - 1]->isFlying())
                mMap.updatePathAir();
            else
                mMap.updatePathGround();

            mActive = true;
            mCreepsOnMap.clear();
        }
    }
}

void Wave::draw(sf::RenderWindow& window)
{
    for (size_t i = 0; i < mCreepsOnMap.size(); ++i) {
        if (mCreepsOnMap[i]->isAlive()) {
            mCreepsOnMap[i]->draw();
        }
    }
}

Creep* Wave::getCreep(int a)
{
    if (a >=0 && (size_t) a < mCreepsOnMap.size()) {
        return mCreepsOnMap[a].get();
    } else {
        return nullptr;
    }
}

bool Wave::allDead() const
{
    for (size_t i = 0; i < mCreepsOnMap.size(); ++i) {
        if (mCreepsOnMap[i]->isAlive()) {
            return false;
        }
    }
    return true;
}

template <class T>
std::unique_ptr<Creep> Wave::make(float hp)
{
    return std::unique_ptr<Creep>(new T((int) (hp + 0.5f), (sf::Vector2f) mMap.getCheckpoints()[0].getCenter(), mWindow, mPlayer));
}

void Wave::pushToQueue(std::string cn, int level)
{
    if (cn == "grunt")
        mCreepList.push_back(std::move(make<Grunt>(  40.f + std::pow(1.0f + level, 2.f)  )));
    else if (cn == "bat")
        mCreepList.push_back(std::move(make<Bat>(  20.f + std::pow(1.0f + level, 2.f)  )));
}

void Wave::create()
{
    mCreepsOnMap.push_back(std::unique_ptr<Creep>(mCreepList[mLevel - 1]->clone()));
}

void Wave::pushRandomCreepToQueue(int i)
{
    switch (thor::random(0,0))
    {
        case 0:
            pushToQueue("grunt", i);
            break;
        case 1:
            pushToQueue("bat", i);
            break;
    }
}
