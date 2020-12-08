#include "Creep.h"

Creep::Creep(float s, int h, bool f, sf::Vector2f startPos, sf::RenderWindow& window, Player& player)
: mPosition(startPos), mHitpoints(h), mHitpoints_default(h), mPathPosition(0U), mSpeed(s), mAlive(true), mFlying(f), mWindow(window), mPlayer(player)
{
    mSprite.setOrigin(25.f, 25.f);
    mHpbar.setPosition(mSprite.getPosition());
}

void Creep::move(const std::vector<sf::Vector2i>& nodes)
{
    mAnimator.update(mFrameClock.restart());
    mAnimator.animate(mSprite);

    if (mPathPosition >= 0 && (size_t) mPathPosition < nodes.size() && (size_t) mPathPosition + 1 < nodes.size() )
    {
        sf::Vector2f target = (sf::Vector2f) nodes[mPathPosition + 1];

        sf::Vector2f vec_dir = target - mPosition;

        float angle = myn::getAngleBetween( getPosition(), target );

        mSprite.setRotation(angle + 90.f);

        float length = std::sqrt( vec_dir.x * vec_dir.x + vec_dir.y * vec_dir.y );

        vec_dir = sf::Vector2f( vec_dir.x / length, vec_dir.y / length );

        if (myn::isPointBetween(mPosition, target, getPosition() + vec_dir * mSpeed)) {
            setPosition(getPosition() + vec_dir * mSpeed);
        }
        else {
            setPosition((sf::Vector2f) nodes[++mPathPosition]);
            // TODO: recursive..
            //move(nodes);
        }
    } else {
        kill();
        mPlayer.addLives(-1);
    }

    mSprite.move(25.f, 25.f);
}

void Creep::setPosition(sf::Vector2f p)
{
    mPosition = p;
    mSprite.setPosition((sf::Vector2f) mPosition * 50.f);
    mHpbar.setPosition(getPosition() * 50.f);
}

void Creep::setSize(sf::Vector2f s)
{
    mSize = s;
    mSprite.setScale((sf::Vector2f) mSize * 50.f);
}

bool Creep::attack(int damage)
{
    if (mAlive) {
        mHitpoints -= damage;
        if (mHitpoints <= 0) {
            kill();
            return true;
        }

        mHpbar.setPercentage(mHitpoints / (float)mHitpoints_default);
        return false;
    }
    return false;
}

void Creep::kill()
{
    mAlive = false;
}

void Creep::draw()
{
    mWindow.draw(getSprite());
    mWindow.draw(mHpbar.getShape());
}

Grunt::Grunt(int h, sf::Vector2f startPos, sf::RenderWindow& window, Player& player)
: Creep(0.05f, h, false, startPos, window, player)
{
    mSprite.setTexture(ResourceManager::grunt);
    mAnimator.addAnimation("walk", ResourceManager::grunt_walk, sf::seconds(0.75f));
    mAnimator.playAnimation("walk", true);
}

Bat::Bat(int h, sf::Vector2f startPos, sf::RenderWindow& window, Player& player)
: Creep(0.025f, h, true, startPos, window, player)
{
    mSprite.setTexture(ResourceManager::grunt);
    mAnimator.addAnimation("walk", ResourceManager::grunt_walk, sf::seconds(1.5f));
    mAnimator.playAnimation("walk", true);
}
