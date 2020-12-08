#include "ResourceManager.h"

sf::Texture ResourceManager::rock;
sf::Texture ResourceManager::grass;
sf::Texture ResourceManager::tower_base;
sf::Texture ResourceManager::tower_crossbow;
sf::Texture ResourceManager::tower_arrow;
sf::Texture ResourceManager::grunt;
thor::FrameAnimation ResourceManager::grunt_walk;
thor::FrameAnimation ResourceManager::tower_default;
thor::FrameAnimation ResourceManager::tower_shoot;
thor::ColorGradient ResourceManager::healthbar_color;
sf::Font ResourceManager::font;
sf::Music ResourceManager::music;

bool ResourceManager::init()
{
    if (!rock.loadFromFile("Resources/Images/Stone1.png"))   return false;
    rock.setSmooth(true);
    if (!grass.loadFromFile("Resources/Images/grass.png")) return false;
    grass.setSmooth(true);
    grass.setRepeated(true);

    // CreepS
    if (!grunt.loadFromFile("Resources/Images/Grunt/skeleton-Walk.png")) return false;
    grunt.setSmooth(true);

    std::vector<sf::IntRect> rects_grunt;

    for (int i = 1; i < 15; ++i)
        rects_grunt.push_back(sf::IntRect (2 + i * 56, 2, 54, 57));

    for (size_t i = 0; i < rects_grunt.size(); ++i)
        grunt_walk.addFrame(1.f, rects_grunt[i]);

    //TOWER
    if (!tower_base.loadFromFile("Resources/Images/CrossbowTower/Crossbow_Base.png")) return false;
    tower_base.setSmooth(true);
    if (!tower_crossbow.loadFromFile("Resources/Images/CrossbowTower/skeleton-Shoot.png")) return false;
    tower_crossbow.setSmooth(true);

    if (!tower_arrow.loadFromFile("Resources/Images/CrossbowTower/Crossbow_Projectile.png")) return false;
    tower_arrow.setSmooth(true);

    std::vector<sf::IntRect> rects_tower;

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 7; ++j) {
                rects_tower.push_back(sf::IntRect (2 + j * 132, 2 + i * 161, 130, 159));
        }
    }

    rects_tower.push_back(sf::IntRect (2, 2, 130, 159));


    for (size_t i = 0; i < rects_tower.size(); ++i)
        tower_shoot.addFrame(1.f, rects_tower[i]);

    tower_default.addFrame(1.f, rects_tower[0]);

    healthbar_color[0.f] = sf::Color(255, 0  , 0);
    healthbar_color[1.f] = sf::Color(0  , 255, 0);

    if ( !font.loadFromFile("Resources/Fonts/arial.ttf") )
        return 1;

//    if (!music.openFromFile("Resources/Music/vlmusic.wav"))
//        return 1;

    return true;
}
