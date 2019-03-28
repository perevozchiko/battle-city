#include "game.h"

namespace BattleCity {

Game::Game(const sf::String& name, const sf::ContextSettings& settings) :
    window(sf::VideoMode(SET::WINDOW_WIDTH, SET::WINDOW_HEIGHT), name, sf::Style::Titlebar | sf::Style::Close, settings),
    //TODO сделать offset и position по умолчанию
    player(texture, {2,4}, {SET::PLAYER_POSITION}),
    enemy(texture, {290,810}, {14, 14})
{
    texture.loadFromFile(SET::PATH_IMAGES);

    // FPS
    font.loadFromFile(SET::PATH_FONTS);
    fpsInfo.text.setFont(font);
    fpsInfo.text.setPosition(SET::FPS_POS, SET::FPS_POS);
    fpsInfo.text.setCharacterSize(SET::FPS_FONT_SIZE);

    // чтение данных уровня из файла (int level)
    std::vector<std::string> map = utils::readFileMap(1);

    // Создание тайлов карты
    sf::Vector2i offset;
    std::string str;
    int type;
    for (size_t i = 0; i < size_t(SET::MAP_HEIGHT); ++i)
    {
        str  = map[i];
        for (size_t j = 0; j < size_t(SET::MAP_WIDTH); ++j)
        {
            type = utils::charToInt(str.c_str()[j]);
            if (type != 0)
            {
                offset = utils::setOffset(type);
                Tile tile(texture, offset);
                tile.setType(type);
                tile.setPosition(static_cast<int>(j) * SET::SIZE_TILE_MAP.x, static_cast<int>(i) * SET::SIZE_TILE_MAP.y);
                tiles.push_back(tile);
            }
        }
    }



    //    for (std::size_t i = 0; i < 3; i++)
    //    {
    //        sf::Vector2f pos = {SET::WINDOW_WIDTH * i/2 + (i%2) * 16.f, 16.f};
    //        enemies[i].getSprite().setTexture(texture);
    //        enemies[i].getSprite().setTextureRect(sf::IntRect(204,809,32,32));
    //        enemies[i].changeDirectionMoving();
    //    }

}


void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time enemyTime = sf::Time::Zero;

    while (window.isOpen())
    {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while (timeSinceLastUpdate > SET::TIME_PER_FRAME)
        {
            timeSinceLastUpdate -= SET::TIME_PER_FRAME;

            processEvents();
            update(SET::TIME_PER_FRAME);
        }
        enemyTime += elapsedTime;

        if (enemyTime.asSeconds() > 2)
        {
            while (enemyTime > SET::TIME_PER_FRAME)
            {
                enemyTime -= SET::TIME_PER_FRAME;
            }
            //std::size_t i = static_cast<std::size_t>(random(0, enemies.size()));

            enemy.changeDirectionMoving();
        }

        updateFPS(elapsedTime);
        render();
    }
}


void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;

        default:
            break;
        }
    }
    player.handleRealTimeInput();

}

void Game::update(const sf::Time &elapsedTime)
{

    player.update(elapsedTime);
    player.adaptPlayerPosition();
    enemy.update(elapsedTime);
    enemy.adaptEnemyPosition();

    auto p = player.getGlobalRect();
    auto e = enemy.getGlobalRect();
    //enemy.setCollisionDetected(false);
    sf::IntRect result;
    if (e.intersects(p, result))
    {
        switch(player.getDirection())
        {
        case SET::Direction::RIGHT:
        {
            if(enemy.getDirection() == SET::Direction::LEFT)
            {
                player.setPosition(e.left - p.width/2, p.top + p.height/2);
                enemy.setPosition(p.left + e.width/2, e.top + e.height/2);
            }
            break;
        }
        case SET::Direction::LEFT:
        {
            if(enemy.getDirection() == SET::Direction::RIGHT)
            {
                enemy.setPosition(p.left - e.width/2, e.top + e.height/2);
                player.setPosition(p.left + p.width/2, p.top + p.height/2);
            }
            break;
        }
        case SET::Direction::UP:
            player.setCollisionDetected(true);
            if (enemy.getDirection() == SET::Direction::DOWN)
            {
                enemy.setCollisionDetected(true);
            }
            break;
        case SET::Direction::DOWN:
            player.setCollisionDetected(true);
            if (enemy.getDirection() == SET::Direction::UP)
            {
                enemy.setCollisionDetected(true);
            }
            break;
        }


        switch(enemy.getDirection())
        {
        case SET::Direction::RIGHT:
            enemy.setPosition(p.left - e.width/2, e.top + e.height/2);
            break;
        case SET::Direction::LEFT:
            enemy.setPosition(p.left + e.width/2, e.top + e.height/2);
            break;
        case SET::Direction::UP:
            enemy.setCollisionDetected(true);
            break;
        case SET::Direction::DOWN:
            enemy.setCollisionDetected(true);
            break;
        }
    }

    // Коллизии Player
    for(auto &tile : tiles)
    {
        if (tile.getType() != SET::Tile::Ice && tile.getType() != SET::Tile::Shrub)
        {
            auto r = utils::toIntRect(tile.getGlobalRect());
            sf::IntRect result;

            if(p.intersects(r, result))
            {
                switch(player.getDirection())
                {
                case SET::Direction::RIGHT:
                    player.setPosition(p.left + p.width/2 - result.width, p.top + p.width/2);
                    break;
                case SET::Direction::LEFT:
                    player.setPosition(p.left + p.width/2 + result.width, p.top + p.width/2);
                    break;
                case SET::Direction::UP:
                    player.setPosition(p.left + p.width/2, p.top + p.height/2 + result.height);
                    break;
                case SET::Direction::DOWN:
                    player.setPosition(p.left + p.width/2, p.top + p.height/2 - result.height);

                    break;

                }
            }
        }
    }

    // Коллизии Enemy
    for(auto &tile : tiles)
    {
        if (tile.getType() != SET::Tile::Ice && tile.getType() != SET::Tile::Shrub)
        {
            sf::IntRect result;
            auto r = utils::toIntRect(tile.getGlobalRect());

            if(e.intersects(r, result))
            {
                switch(enemy.getDirection())
                {
                case SET::Direction::RIGHT:
                    enemy.setPosition(e.left + e.width/2 - result.width, e.top + e.height/2);
                    break;
                case SET::Direction::LEFT:
                    enemy.setPosition(e.left + e.width/2 + result.width, e.top + e.height/2);
                    break;
                case SET::Direction::UP:
                    enemy.setPosition(e.left + e.width/2, e.top + e.height/2 + result.height);
                    break;
                case SET::Direction::DOWN:
                    enemy.setPosition(e.left + e.width/2, e.top + e.height/2 - result.height);
                    break;
                }
            }
        }
    }

}

void Game::render()
{
    window.clear();



    for (auto &tile : tiles)
    {
        if (tile.getType() == SET::Tile::Ice)
        {
            window.draw(tile);
        }
    }

    window.draw(player);
    window.draw(enemy);
    //    for (auto& enemy : enemies)
    //    {
    //        window.draw(enemy.getSprite());
    //    }


    //    for (auto& _tile : tiles)
    //    {
    //        window.draw(_tile.getSprite());
    //    }

    for (auto &tile : tiles)
    {
        if (tile.getType() != SET::Tile::Ice)
        {
            window.draw(tile);
        }
    }
    window.draw(fpsInfo.text);
    window.display();
}

void Game::updateFPS(const sf::Time &elapsedTime)
{
    fpsInfo.updateTime += elapsedTime;
    ++fpsInfo.frame;

    if (fpsInfo.updateTime >= sf::seconds(1.f))
    {
        fpsInfo.text.setString("FPS = " + std::to_string(fpsInfo.frame) + "\n");
        fpsInfo.updateTime -= sf::seconds(1.f);
        fpsInfo.frame = 0;
    }
}
} //namespace BattleCity
