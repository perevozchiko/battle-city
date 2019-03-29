#include "game.h"

namespace BattleCity {

Game::Game(const sf::String& name, const sf::ContextSettings& settings) :
    window(sf::VideoMode(SET::WINDOW_WIDTH, SET::WINDOW_HEIGHT), name, sf::Style::Titlebar | sf::Style::Close, settings),
    //TODO сделать offset и position по умолчанию
    player(texture, {3, 5}, {SET::PLAYER_POSITION})

{
    texture.loadFromFile(SET::PATH_IMAGES);

    // FPS
    font.loadFromFile(SET::PATH_FONTS);
    fpsInfo.text.setFont(font);
    fpsInfo.text.setPosition(SET::FPS_POS, SET::FPS_POS);
    fpsInfo.text.setCharacterSize(SET::FPS_FONT_SIZE);

    // чтение данных уровня из файла (int level)
    std::vector<std::string> map = utils::readFromFileMap(1);

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
                //auto b = std::unique_ptr<Bullet>(new Bullet(texture, {1, 352}, player.getPosition()));
                auto t = std::unique_ptr<Tile>(new Tile(texture, offset));
                t->setType(type);
                t->setPosition(static_cast<int>(j) * SET::SIZE_TILE_MAP.x, static_cast<int>(i) * SET::SIZE_TILE_MAP.y);
                tiles.push_back(std::move(t));
            }
        }
    }

    for (int i = 0; i < 3; ++i)
    {
        auto en = std::unique_ptr<Enemy>(new Enemy());
        sf::Vector2i offset = utils::getEnemyType(i);

        en->setTexture(texture, offset);
        int posX = SET::WINDOW_WIDTH * i/2 + (i%2) * SET::SIZE_TILE_ENEMY.x/2;
        int posY = SET::SIZE_TILE_ENEMY.y/2;
        //std::cout << posX << " " << posY << std::endl;
        en->setPosition(posX, posY);
        en->setDirection(SET::Direction::DOWN);
        enemies.push_back(std::move(en));
    }
}

Game::~Game()
{

}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time enemyTime = sf::Time::Zero;
    sf::Time bulletTime = sf::Time::Zero;
    sf::Time enemyBulletTime = sf::Time::Zero;

    while (window.isOpen())
    {
        //window.setKeyRepeatEnabled (true);
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        enemyTime += elapsedTime;
        if (enemyTime.asSeconds() > 0.5f)
        {
            while (enemyTime > SET::TIME_PER_FRAME)
            {
                enemyTime -= SET::TIME_PER_FRAME;
            }
            if (enemies.size() > 0)
            {
                std::size_t i = static_cast<std::size_t>(random(0, static_cast<int>(enemies.size()-1)));
                enemies[i]->changeDirectionMoving();
            }
            if (enemies.size() < 3)
            {
                std::size_t i = static_cast<std::size_t>(random(0, 3));
                auto en = std::unique_ptr<Enemy>(new Enemy());
                sf::Vector2i offset = utils::getEnemyType(i);

                en->setTexture(texture, offset);
                int posX = SET::WINDOW_WIDTH * i/2 + (i%2) * SET::SIZE_TILE_ENEMY.x/2;
                int posY = SET::SIZE_TILE_ENEMY.y/2;
                //std::cout << posX << " " << posY << std::endl;
                en->setPosition(posX, posY);
                en->setDirection(SET::Direction::DOWN);
                enemies.push_back(std::move(en));
            }
        }

        while (timeSinceLastUpdate > SET::TIME_PER_FRAME)
        {
            timeSinceLastUpdate -= SET::TIME_PER_FRAME;
            processEvents();
            update(SET::TIME_PER_FRAME);
        }

        bulletTime += elapsedTime;
        if (player.shoot)
        {
            if (bulletTime.asSeconds() > 1.f)
            {
                while(bulletTime > SET::TIME_PER_FRAME)
                {
                    bulletTime -= SET::TIME_PER_FRAME;
                }
                auto b = std::unique_ptr<Bullet>(new Bullet(texture, {1, 352}, player.getPosition()));
                b->setDirection(player.getDirection());
                b->setType(SET::bulletType::Player);
                bullets.push_back(std::move(b));

                player.shoot = false;
            }
        }
        enemyBulletTime += elapsedTime;
        if (enemyBulletTime.asSeconds() > 1.f)
        {
            while(enemyBulletTime > SET::TIME_PER_FRAME)
            {
                enemyBulletTime -= SET::TIME_PER_FRAME;
            }
            for (auto &enemy : enemies)
            {
                auto b = std::unique_ptr<Bullet>(new Bullet(texture, {1, 352}, enemy->getPosition()));
                b->setDirection(enemy->getDirection());
                b->setType(SET::bulletType::Enemy);
                bullets.push_back(std::move(b));
            }
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
    for(const auto &enemy : enemies)
    {
        enemy->update(elapsedTime);
        enemy->adaptEnemyPosition();
    }

    for(const auto& bullet: bullets)
    {
        bullet->update(elapsedTime);
    }

    auto p = player.getGlobalRect();

    //Коллизии bullet
    // со стенками окна и с тайлами карты
    for (const auto& bullet : bullets)
    {
        auto b = bullet->getGlobalRect();
        if(b.top < 0 || b.left < 0 || (b.top + b.height > SET::WINDOW_HEIGHT) || (b.left + b.width > SET::WINDOW_WIDTH) )
        {
            bullet->setRemoved(true);
        }

        for (const auto& tile : tiles)
        {
            auto t = tile->getGlobalRect();

            if(t.intersects(b))
            {
                if(tile->getType() == SET::Tile::Brick)
                {
                    tile->setRemoved(true);
                    bullet->setRemoved(true);
                }
                if(tile->getType() == SET::Tile::Concrete)
                {
                    bullet->setRemoved(true);
                }
            }
        }

        for(auto &enemy : enemies)
        {
            auto e = enemy->getGlobalRect();
            if (e.intersects(b) && bullet->getType() == SET::bulletType::Player)
            {
                bullet->setRemoved(true);
                enemy->setRemoved(true);
            }
        }

        if(p.intersects(b) && bullet->getType() == SET::bulletType::Enemy)
        {
            bullet->setRemoved(true);
            player.setRemoved(true);
        }
    }

    // TODO Enemy with Player
    //    sf::IntRect result;
    //    if (e.intersects(p, result))
    //    {
    //        switch(player.getDirection())
    //        {
    //        case SET::Direction::RIGHT:
    //        {
    //            if(enemy.getDirection() == SET::Direction::LEFT)
    //            {
    //                player.setPosition(e.left - p.width/2, p.top + p.height/2);
    //                enemy.setPosition(p.left + e.width/2, e.top + e.height/2);
    //            }
    //            break;
    //        }
    //        case SET::Direction::LEFT:
    //        {
    //            if(enemy.getDirection() == SET::Direction::RIGHT)
    //            {
    //                enemy.setPosition(p.left - e.width/2, e.top + e.height/2);
    //                player.setPosition(p.left + p.width/2, p.top + p.height/2);
    //            }
    //            break;
    //        }
    //        case SET::Direction::UP:
    //            player.setCollisionDetected(true);
    //            if (enemy.getDirection() == SET::Direction::DOWN)
    //            {
    //                enemy.setCollisionDetected(true);
    //            }
    //            break;
    //        case SET::Direction::DOWN:
    //            player.setCollisionDetected(true);
    //            if (enemy.getDirection() == SET::Direction::UP)
    //            {
    //                enemy.setCollisionDetected(true);
    //            }
    //            break;
    //        }


    //        switch(enemy.getDirection())
    //        {
    //        case SET::Direction::RIGHT:
    //            enemy.setPosition(p.left - e.width/2, e.top + e.height/2);
    //            break;
    //        case SET::Direction::LEFT:
    //            enemy.setPosition(p.left + e.width/2, e.top + e.height/2);
    //            break;
    //        case SET::Direction::UP:
    //            enemy.setCollisionDetected(true);
    //            break;
    //        case SET::Direction::DOWN:
    //            enemy.setCollisionDetected(true);
    //            break;
    //        }
    //    }
    // Коллизии Player
    for(auto &tile : tiles)
    {
        if (tile->getType() != SET::Tile::Ice && tile->getType() != SET::Tile::Shrub)
        {
            auto r = tile->getGlobalRect();
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

    //Коллизии Enemy
    for (const auto& enemy : enemies)
    {
        auto e = enemy->getGlobalRect();
        for(const auto& tile : tiles)
        {
            if (tile->getType() != SET::Tile::Ice && tile->getType() != SET::Tile::Shrub)
            {
                sf::IntRect result;
                auto r = tile->getGlobalRect();

                if(e.intersects(r, result))
                {
                    switch(enemy->getDirection())
                    {
                    case SET::Direction::RIGHT:
                        enemy->setPosition(e.left + e.width/2 - result.width, e.top + e.height/2);
                        break;
                    case SET::Direction::LEFT:
                        enemy->setPosition(e.left + e.width/2 + result.width, e.top + e.height/2);
                        break;
                    case SET::Direction::UP:
                        enemy->setPosition(e.left + e.width/2, e.top + e.height/2 + result.height);
                        break;
                    case SET::Direction::DOWN:
                        enemy->setPosition(e.left + e.width/2, e.top + e.height/2 - result.height);
                        break;
                    }
                }
            }
        }
    }


    // удаление Bullets
    auto it = std::remove_if(bullets.begin(), bullets.end(), [](const std::unique_ptr<Bullet>& c)
    {
        return c->getRemoved();
    });
    bullets.erase(it, bullets.end());

    // удаление тайлов карты
    auto itTile = std::remove_if(tiles.begin(), tiles.end(), [](const std::unique_ptr<Tile>& c)
    {
        return c->getRemoved();
    });
    tiles.erase(itTile, tiles.end());

    //удаление enemy
    auto itEnemy = std::remove_if(enemies.begin(), enemies.end(), [](const std::unique_ptr<Enemy>& c)
    {
        return c->getRemoved();
    });
    enemies.erase(itEnemy, enemies.end());

    //удаление player
    if (player.getRemoved())
    {
        delete &player;
    }

}

void Game::render()
{
    window.clear();

    for(const auto& bullet : bullets)
    {
        window.draw(*bullet);
    }

    for (auto &tile : tiles)
    {
        if (tile->getType() == SET::Tile::Ice)
        {
            window.draw(*tile);
        }
    }


    window.draw(player);


    for (auto &enemy : enemies)
    {
        window.draw(*enemy);
    }

    for (auto &tile : tiles)
    {
        if (tile->getType() != SET::Tile::Ice)
        {
            window.draw(*tile);
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
