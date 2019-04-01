#include "game.h"

int main(int /*argc*/, char** /*argv*/)
{
    sf::ContextSettings settings;
    settings.majorVersion = BattleCity::SETTINGS::MAJOR;
    settings.minorVersion = BattleCity::SETTINGS::MINOR;
    settings.antialiasingLevel = BattleCity::SETTINGS::ANTIALIASING;

    BattleCity::Game game(BattleCity::SETTINGS::GAME_NAME, settings);
    game.run();

    return 0;
}

