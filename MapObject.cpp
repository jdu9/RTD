#include "MapObject.h"

MapObject::MapObject( sf::Vector2i p, sf::Vector2i s )
: mPosition( p ), mSize( s )
{
}

void MapObject::setPosition( sf::Vector2i p )
{
    mPosition = p;
    mSprite.setPosition( (sf::Vector2f) mPosition * 50.f );
}

void MapObject::move( sf::Vector2i dp )
{
    setPosition( getPosition() + dp );
}

AnimatedMapObject::AnimatedMapObject( sf::Vector2i p, sf::Vector2i s )
: MapObject( p, s )
{

}
