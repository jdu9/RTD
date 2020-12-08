#include "Checkpoint.h"

Checkpoint::Checkpoint(sf::Vector2i p, int number)
: mPosition(p)
{
    std::string name;
    sf::Color color;
    if (number == 0) {
        name = "Start";
        color = sf::Color(0,255,0,150);
    } else if (number == -1) {
        name = "Finish";
        color = sf::Color(255,0,0,150);
    } else {
        name = std::to_string(number);
        color = sf::Color(255,255,255,150);
    }
    mText.setString(name);
    mText.setCharacterSize(50);
    mText.setFont(ResourceManager::font);

    sf::FloatRect textRect = mText.getLocalBounds();
    mText.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top  + textRect.height/2.0f);

    mShape.setPosition(p.x * 50, p.y * 50);
    mShape.setSize(sf::Vector2f(150,150));
    mShape.setFillColor(color);
    mText.setPosition(mShape.getPosition() + sf::Vector2f(mShape.getSize().x/2.0f,mShape.getSize().y/2.0f));
}

void Checkpoint::draw(sf::RenderWindow& w)
{
    w.draw(mShape);
    w.draw(mText);
}
