#include "game.h"

namespace BattleCity {

Game::Game(const sf::String& name, const sf::ContextSettings& settings) :
    window(sf::VideoMode(SET::WINDOW_WIDTH, SET::WINDOW_HEIGHT), name, sf::Style::Titlebar | sf::Style::Close, settings),
    //TODO сделать offset и position по умолчанию
    player(texture, {2,4}, {0.f, 0.f})
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
                Tile tile(offset, texture);
                tile.setType(type);
                tile.setPosition({static_cast<float>(j) * SET::SIZE_TILE_MAP.x, static_cast<float>(i) * SET::SIZE_TILE_MAP.y});
                tiles.push_back(tile);
            }
        }
    }

    //    for (unsigned long i = 0; i < 3; i++)
    //    {
    //        sf::Vector2f pos = {SET::WINDOW_WIDTH * i/2 + (i%2) * 16.f, 16.f};
    //        enemies[i].setPosition(pos);
    //        enemies[i].setTextureRectange(sf::IntRect(224, 809, 32, 32));
    //        enemies[i].changeDirectionMoving();
    //    }

}


void Game::run()
{


    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    //    sf::Time enemyTime = sf::Time::Zero;
    //    RandomGen change;
    //    int ch = change(1, 3);


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




        //        enemyTime += elapsedTime;


        //        if (enemyTime.asSeconds() > ch)
        //        {
        //            while (enemyTime > SET::TimePerFrame)
        //            {
        //                enemyTime -= SET::TimePerFrame;
        //            }
        //            std::size_t i = static_cast<std::size_t>(change(0, enemies.size()));

        //            enemies[i].changeDirectionMoving();
        //        }


        //            }
        //        }


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
    player.adaptPosition();

    auto p = player.getGlobalRect();
    for(auto &tile : tiles)
    {
        if (tile.getType() != SET::Tile::Ice && tile.getType() != SET::Tile::Shrub)
        {
            auto r = tile.getGlobalRect();

            if(p.intersects(r))
            {
                switch(player.getDirection())
                {
                case SET::Direction::RIGHT:
                    player.setPosition({r.left-p.width/2, p.top + p.height/2});
                    break;
                case SET::Direction::LEFT:
                    player.setPosition({r.left + r.width + p.width/2, p.top + p.height/2});
                    break;
                case SET::Direction::UP:
                    player.setPosition({p.left + p.width/2, r.top + r.height + p.height/2});
                    break;
                case SET::Direction::DOWN:
                    player.setPosition({p.left + p.width/2, r.top - p.height/2});
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
