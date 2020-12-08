#include "Tower.h"

Tower::Tower( sf::Vector2i p, sf::Vector2i s, float c, Wave& wave )
: AnimatedMapObject( p, s ), mCooldown( c ), mpTarget( nullptr ), mTransparent(true), mWave(wave)
{
    mSprite.setTexture( ResourceManager::tower_base );

    if (mWave.isActive()) {
        mSprite.setColor(sf::Color(255,255,255, 125));
        mMoveable.setColor(sf::Color(255,255,255, 125));
    }
    else uncover();

    setPosition( getPosition() );

    mTime = sf::seconds( 0.0f );
}

void Tower::setPosition( sf::Vector2i p )
{
    mPosition = p;
    mSprite.setPosition( (sf::Vector2f) mPosition * 50.f );
    mMoveable.setPosition( (sf::Vector2f) mPosition * 50.f );
}

void Tower::updateTarget( Wave& w, const sf::Time& deltaTime, Player& player )
{
    for ( size_t i = 0; i < mProjectiles.size(); ++i ) {
        if ( mProjectiles[i]->collides() ) {
            if ( mProjectiles[i]->getTarget().attack( thor::random( 1, 2 ) ) ) {
                player.addGold(1);
            }
            mProjectiles.erase( mProjectiles.begin() + i );
        } else {
            mProjectiles[i]->update();
        }
    }
    if( mpTarget != nullptr &&
        mpTarget->isAlive() &&
        myn::getDistanceBetween( (sf::Vector2f) mPosition + sf::Vector2f( 1.0f, 1.0f ), mpTarget->getPosition() + sf::Vector2f( 0.5f, 0.5f ) ) < 12.0f )
    {
        mTime = sf::operator-( mTime, deltaTime );
        if ( mTime <= sf::Time::Zero )
        {
            mAnimator.playAnimation( "shoot" );
            mTime = sf::Time::Zero;
            mTime = sf::operator+( sf::seconds( mCooldown ), mTime );
            mProjectiles.push_back( std::unique_ptr<Projectile>( new Projectile( *mpTarget, 20.f, getSpritePosition() + sf::Vector2f( 50.f, 50.f ) ) ) );
        }
        mMoveable.setRotation( myn::getAngleBetween( (sf::Vector2f) getPosition() + sf::Vector2f( 1.f, 1.f ), mpTarget->getPosition() + sf::Vector2f( 0.5f, 0.5f ) ) + 90.f );
        mAnimator.update( deltaTime );
        mAnimator.animate(mMoveable);
    }
    else
    {
        mpTarget = nullptr;
        mTime = sf::operator-( mTime, deltaTime );
        if ( mTime <= sf::Time::Zero )
        {
            mAnimator.playAnimation( "default" );
            for ( size_t i = 0; i < w.countOnMap(); ++i )
            {
                if ( w.getCreep( i )->isAlive() &&
                     myn::getDistanceBetween( (sf::Vector2f) mPosition + sf::Vector2f( 1.f, 1.f ), w.getCreep( i )->getPosition() + sf::Vector2f( 0.5f, 0.5f ) ) < 12.f )
                {
                    mpTarget = w.getCreep( i );
                    mAnimator.playAnimation( "shoot" );
                    mProjectiles.push_back( std::unique_ptr<Projectile>( new Projectile( *mpTarget, 20.f, getSpritePosition() + sf::Vector2f( 50.f, 50.f ) ) ) );
                    mTime = sf::Time::Zero;
                    mTime = sf::operator+( sf::seconds( mCooldown ), mTime );
                    break;
                } else {
                    mpTarget = nullptr;
                }
            }
            mMoveable.rotate( 0.1f );
        }
        mAnimator.update( deltaTime );
        mAnimator.animate( mMoveable );
    }
}

void Tower::drawProjectiles( sf::RenderWindow& window )
{
    for (size_t i = 0; i < mProjectiles.size(); ++i)
    {
        window.draw( mProjectiles[i]->getSprite() );
    }
}

Projectile* Tower::getProjectile( int a )
{
    if ( a >= 0 && (size_t) a < mProjectiles.size() )
    {
        return mProjectiles[a].get();
    }
    return nullptr;
}

CrossbowTower::CrossbowTower( sf::Vector2i p, sf::Vector2i s, Wave& wave )
: Tower( p, s, 1.0f, wave )
{
    mMoveable.setTexture( ResourceManager::tower_crossbow );

    mMoveable.move( 50.f, 46.3 );
    mMoveable.setOrigin( 65.f, 102.f );

    mAnimator.addAnimation( "shoot", ResourceManager::tower_shoot, sf::seconds(getCooldown()) );
    mAnimator.addAnimation( "default", ResourceManager::tower_default, sf::seconds(getCooldown()) );

    mAnimator.playAnimation( "shoot", true );
    mAnimator.update( restartClock() );
    mAnimator.animate( mMoveable );
}

void Tower::uncover()
{
    mTransparent = false;
    mSprite.setColor(sf::Color(255,255,255, 255));
    mMoveable.setColor(sf::Color(255,255,255, 255));
}
