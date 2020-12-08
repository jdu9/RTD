#include "Projectile.h"

Projectile::Projectile( Creep& t, float s, sf::Vector2f a )
: mTarget(t), mSpeed(s)
{
    mSprite.setPosition( a );
    mSprite.setTexture( ResourceManager::tower_arrow );
    mSprite.setOrigin( 4.0f, 48.5f );
}

void Projectile::update()
{
    mSprite.move( myn::normalizeVector( mTarget.getSprite().getPosition() - mSprite.getPosition() ) * mSpeed );
    mSprite.setRotation( myn::getAngleBetween( mSprite.getPosition(), mTarget.getSprite().getPosition() ) + 90.f );
}

bool Projectile::collides()
{
    return myn::getDistanceBetween( mSprite.getPosition(), mTarget.getSprite().getPosition() + sf::Vector2f( 25.f, 25.f )) < 53.5f;
}
