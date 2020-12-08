#include "Mob.h"

Mob::Mob(sf::Vector2f pos, float s, int h)
: position(pos), hitpoints(h), hitpoints_default(h), pathPosition(0U), speed(s), alive(true)
{
    sprite.setTexture(ResourceManager::grunt);
    sprite.setOrigin(25.f, 25.f);
    diagonalspeed = std::sqrt(std::pow(speed, 2) / 2.f);

    hpbar.setPosition(sprite.getPosition());

    // testing

    animator.addAnimation("walk", ResourceManager::grunt_walk, sf::seconds(0.75f));

    animator.playAnimation("walk", true);
}

sf::Vector2f Mob::move(const std::vector<sf::Vector2i>& nodes)
{
    animator.update(frameClock.restart());
    animator.animate(sprite);

    if (pathPosition >= 0 && (size_t) pathPosition < nodes.size() && (size_t) pathPosition + 1 < nodes.size())
    {
        sf::Vector2f target = (sf::Vector2f) nodes[pathPosition + 1];

        sf::Vector2f direction = sf::Vector2f(0.f,0.f);

        {
            sf::Vector2f temp   = target - position;

            sprite.setRotation(0.f);

            if (temp.x && temp.y) {
                if (temp.x > 0) {
                    direction.x = diagonalspeed;
                    if (temp.y > 0) {
                        direction.y = diagonalspeed;
                        sprite.setRotation(135.f);
                    } else {
                        direction.y = -diagonalspeed;
                        sprite.setRotation(45.f);
                    }
                }
                else if (temp.x < 0) {
                    direction.x = -diagonalspeed;
                    if (temp.y > 0) {
                        direction.y = diagonalspeed;
                        sprite.setRotation(-135.f);
                    } else {
                        direction.y = -diagonalspeed;
                        sprite.setRotation(-45.f);
                    }
                }
            } else {
                if      (temp.x > 0) {
                    sprite.setRotation(90.f);
                    direction.x = speed;
                }
                else if (temp.x < 0) {
                    sprite.setRotation(-90.f);
                    direction.x = -speed;
                }
                else if      (temp.y > 0) {
                    sprite.setRotation(-180.f);
                    direction.y = speed;
                }
                else if (temp.y < 0) {
                    sprite.setRotation(0.f);
                    direction.y = -speed;
                }
            }
        }

        if (myn::isPointBetween(position, target, position + direction)) {
            if (position == target) {
                ++pathPosition;
            } else {
                setPosition(position + direction);
            }
        }
        else {
            setPosition((sf::Vector2f) nodes[++pathPosition]);
            // TODO: fix this shit
            // move(pathposition, start, value - 1.0f);
        }
    }
    sprite.move(25.f, 25.f);
    return getPosition();
}



void Mob::setPosition(sf::Vector2f p)
{
    position = p;
    sprite.setPosition((sf::Vector2f) position * 50.f);
    hpbar.setPosition(getPosition() * 50.f);
}

void Mob::setSize(sf::Vector2f s)
{
    size = s;
    sprite.setScale((sf::Vector2f) size * 50.f);
}

bool Mob::attack(int damage)
{
    if (alive) {
    hitpoints -= damage;
    if (hitpoints <= 0) {
        kill();
        return true;
    }

    hpbar.setPercentage(hitpoints / (float)hitpoints_default);
    return false;
    }
    return false;
}

void Mob::kill()
{
    alive = false;
}

Grunt::Grunt(sf::Vector2f pos, int h)
: Mob(pos, 0.05f, h)
{

}
