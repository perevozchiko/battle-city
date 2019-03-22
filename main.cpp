#include "game.h"

int main(int /*argc*/, char** /*argv*/)
{
    sf::ContextSettings settings;
    settings.majorVersion = BattleCity::SET::MAJOR;
    settings.minorVersion = BattleCity::SET::MINOR;
    settings.antialiasingLevel = BattleCity::SET::ANTIALIASING;

    BattleCity::Game game(BattleCity::SET::GAME_NAME, settings);
    game.run();

    return 0;
}

