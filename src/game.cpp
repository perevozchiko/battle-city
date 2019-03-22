#include "game.h"

namespace BattleCity {

Game::Game(const sf::String& name, const sf::ContextSettings& settings) :
    window(sf::VideoMode(SET::WINDOW_WIDTH, SET::WINDOW_HEIGHT), name, sf::Style::Titlebar | sf::Style::Close, settings)
  //player()
{
    font.loadFromFile(SET::PATH_FONTS);
    fpsInfo.text.setFont(font);
    fpsInfo.text.setPosition(SET::FPS_POS, SET::FPS_POS);
    fpsInfo.text.setCharacterSize(SET::FPS_FONT_SIZE);

    Game::init();





    //    for (std::size_t rows = 0; rows < 10; rows++)
    //    {
    //        for (std::size_t cols = 0; cols < 10; cols++)
    //        {
    //            if (testMap[rows][cols] == '*')
    //            {
    //                tile.setTextureRectange(sf::IntRect(0, 272, 16, 16));
    //            }
    //            if (testMap[rows][cols] == ' ')
    //            {
    //                tile.setTextureRectange(sf::IntRect(308, 147, 16, 16));
    //            }
    //            tile.getSprite().setOrigin(0, 0);
    //            tile.getSprite().setPosition(cols * 16.f, rows * 16.f);
    //            tiles.push_back(tile);
    //        }
    //    }



    //    for (unsigned long i = 0; i < 3; i++)
    //    {
    //        sf::Vector2f pos = {SET::WINDOW_WIDTH * i/2 + (i%2) * 16.f, 16.f};
    //        enemies[i].setPosition(pos);
    //        enemies[i].setTextureRectange(sf::IntRect(224, 809, 32, 32));
    //        enemies[i].changeDirectionMoving();
    //    }

}

void Game::init()
{
    TileMap tile({0, 304});
    tile.setPosition({100,100});
    tiles.push_back(tile);


    TileMap tile2({0, 304});
    tile2.setPosition({200,200});
    tiles.push_back(tile2);

    run();
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
    // player.handleRealTimeInput();

}

void Game::update(const sf::Time &elapsedTime)
{

    //    player.update(elapsedTime);
    //    player.adaptPlayerPosition();
    //    for (auto& enemy : enemies)
    //    {
    //        enemy.update(elapsedTime);
    //        enemy.adaptEnemyPosition();
    //    }

    // Коллизии
    //    if (player.getDir() == Conf::Direction::UP or player.getDir() == Conf::Direction::DOWN)
    //    {
    //        for (int rows = 0; rows < WIDTHMAP; rows++)
    //        {
    //            int col = static_cast<int> (player.getPosition().x);
    //            tiles[rows][col].ge;
    //            if (player.getSprite().getGlobalBounds().intersects(tiles[2].getSprite().getGlobalBounds())
    //            {

    //            }
    //        }

    //    }

}

void Game::render()
{
    window.clear();



    //    window.draw(player.getSprite());


    //    for (auto& enemy : enemies)
    //    {
    //        window.draw(enemy.getSprite());
    //    }


    //    for (auto& _tile : tiles)
    //    {
    //        window.draw(_tile.getSprite());
    //    }
    window.draw(tiles[0].getSprite());
    window.draw(tiles[1].getSprite());
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
