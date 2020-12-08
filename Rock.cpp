#include "Rock.h"

Rock::Rock( sf::Vector2i p, sf::Vector2i s )
: MapObject( p, s )
{
    mSprite.setTexture(ResourceManager::rock);
}

HorizontalRock::HorizontalRock( sf::Vector2i p )
: Rock ( p, sf::Vector2i( 4, 2 ) )
{
    setPosition( getPosition() );
}

VerticalRock::VerticalRock( sf::Vector2i p )
: Rock ( p, sf::Vector2i( 2, 4 ) )
{
    mSprite.setOrigin( 0.0f, 100.0f );
    mSprite.rotate( 90.0f );
    setPosition( getPosition() );
}

