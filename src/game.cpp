#include "game.h"

namespace BattleCity {

Game::Game(const sf::String& name, const sf::ContextSettings& settings) :
    window(sf::VideoMode(SETTINGS::WINDOW_WIDTH, SETTINGS::WINDOW_HEIGHT), name, sf::Style::Titlebar | sf::Style::Close, settings)
  //TODO сделать offset и position по умолчанию

{    
    texture.loadFromFile(SETTINGS::PATH_IMAGES);
    // FPS
    font.loadFromFile(SETTINGS::PATH_FONTS);
    fpsInfo.text.setFont(font);
    fpsInfo.text.setPosition(SETTINGS::FPS_POS);
    fpsInfo.text.setCharacterSize(SETTINGS::FPS_FONT_SIZE);

    player = std::make_unique<Player>(texture, SETTINGS::PLAYER_OFFSET, SETTINGS::PLAYER_POSITION);
    staff = std::make_unique<Staff> (texture, SETTINGS::BASE_OFFSET, SETTINGS::BASE_POSITION);

    // Количество оставшихся enemy
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            auto count = std::unique_ptr<CounterEnemy>(new CounterEnemy(texture, {49, 273}, {j * 16 + 470, i * 16 + 50}));
            aliveTanks.push_back(std::move(count));
        }
    }

    // чтение данных уровня из файла (int level)
    auto map = utils::readFromFileMap(1);

    // Создание тайлов карты
    sf::Vector2i offset;
    std::string str;
    int type;
    for (std::size_t i = 0; i < SETTINGS::COUNT_TILES_MAP; ++i)
    {
        str  = map[i];
        for (int j = 0; j < SETTINGS::COUNT_TILES_MAP; ++j)
        {
            type = utils::charToInt(str.c_str()[j]);
            if (type != 0)
            {
                offset = utils::setOffset(type);
                auto tile = std::unique_ptr<Tile>(new Tile(texture, offset));
                tile->setType(type);
                tile->setPosition(SETTINGS::MAP_LEFT + static_cast<int>(j) * SETTINGS::SIZE_TILE_MAP,
                                  SETTINGS::MAP_TOP + static_cast<int>(i) * SETTINGS::SIZE_TILE_MAP);
                tiles.push_back(std::move(tile));
            }
        }
    }

    // Создание рамок окна
    sf::RectangleShape topBorder = utils::createBorder({SETTINGS::WINDOW_WIDTH, SETTINGS::SIZE_TILE_MAP},{0,0});
    sf::RectangleShape leftBorder = utils::createBorder({SETTINGS::SIZE_TILE_MAP * 2, SETTINGS::WINDOW_HEIGHT}, {0,0});
    sf::RectangleShape bottomBorder = utils::createBorder({SETTINGS::WINDOW_WIDTH, SETTINGS::SIZE_TILE_MAP},
    {0,SETTINGS::WINDOW_HEIGHT - SETTINGS::SIZE_TILE_MAP});
    sf::RectangleShape rightBorder = utils::createBorder({SETTINGS::SIZE_TILE_MAP * 4, SETTINGS::WINDOW_HEIGHT},
    {SETTINGS::WINDOW_WIDTH - 4 * SETTINGS::SIZE_TILE_MAP, 0});

    borders = {topBorder, leftBorder, bottomBorder, rightBorder};

    // Создание врагов
    for (int i = 0; i < SETTINGS::MAX_NUM_ENEMY; ++i)
    {
        auto enemy = std::make_unique<Enemy>(texture, SETTINGS::EnemyType::Simple, utils::setStartPosition(i));
        enemies.push_back(std::move(enemy));
    }
}

Game::~Game()
{

}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time timeEnemyChangeDirection = sf::Time::Zero;
    sf::Time timeEnemyShoot = sf::Time::Zero;
    sf::Time delayPlayerShoot = sf::Time::Zero;

    while (window.isOpen())
    {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        timeEnemyChangeDirection += elapsedTime;
        delayPlayerShoot += elapsedTime;
        timeEnemyShoot += elapsedTime;
        while (timeSinceLastUpdate > SETTINGS::TIME_PER_FRAME)
        {
            timeSinceLastUpdate -= SETTINGS::TIME_PER_FRAME;
            processEvents();
            update(SETTINGS::TIME_PER_FRAME);
        }
        if(player->isAlive() && player->shoot)
        {
            if (delayPlayerShoot.asSeconds() > 0.7f)
            {
                while(delayPlayerShoot > SETTINGS::TIME_PER_FRAME)
                {
                    delayPlayerShoot -= SETTINGS::TIME_PER_FRAME;
                }
                const sf::Vector2i i = {1, 352}; // создать константу в сеттингс
                auto bullet= std::make_unique<Bullet>(texture, i, player->getPosition());
                bullet->setDirection(player->getDirection());
                bullet->setType(SETTINGS::bulletType::Player);
                bullets.push_back(std::move(bullet));
                player->shoot = false;
            }
        }
        for (const auto &enemy : enemies)
        {
            if(timeEnemyChangeDirection.asSeconds() > random(2, 5))
            {
                while(timeEnemyChangeDirection > SETTINGS::TIME_PER_FRAME)
                {
                    timeEnemyChangeDirection -= SETTINGS::TIME_PER_FRAME;
                    enemy->changeDirectionMoving();
                }
            }
            if (timeEnemyShoot.asSeconds() > random(1, 2))
            {
                while (timeEnemyShoot > SETTINGS::TIME_PER_FRAME)
                {
                    timeEnemyShoot -= SETTINGS::TIME_PER_FRAME;
                    auto bullet= std::unique_ptr<Bullet>(new Bullet(texture, {1, 352}, enemy->getPosition()));
                    bullet->setDirection(enemy->getDirection());
                    bullet->setType(SETTINGS::bulletType::Enemy);
                    bullets.push_back(std::move(bullet));
                }
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
    // обработка нажатий клавиш
    player->handleRealTimeInput();
}

void Game::update(const sf::Time &elapsedTime)
{
    auto p = player->getGlobalRect();
    auto s = staff->getGlobalRect();

    // коллизии bullet
    for(auto &bullet : bullets)
    {
        bullet->update(elapsedTime);
        auto b = bullet->getGlobalRect();

//        if(bullet->collisionDtect())
//        {
//            bullet->setForRemove();
//        }

        if(b.top < SETTINGS::MAP_TOP ||
                (b.left < (SETTINGS::MAP_LEFT)) ||
                (b.top + b.height > SETTINGS::MAP_HEIGHT) ||
                (b.left + b.width > SETTINGS::MAP_WIDTH))
        {
            bullet->setForRemove();
        }
        else if (bullet->getType() == SETTINGS::bulletType::Player)
        {
            for (auto &enemy : enemies)
            {
                auto e = enemy->getGlobalRect();
                if (b.intersects(e))
                {
                    bullet->setForRemove();
                    enemy->setForRemove();
                }
            }
        }
        else if (bullet->getType() == SETTINGS::bulletType::Enemy)
        {
            if (b.intersects(p))
            {
                bullet->setForRemove();
                player->setForRemove();
            }
        }

        if (b.intersects(s))
        {
            bullet->setForRemove();
            staff->setForRemove();
        }
        for (const auto &tile : tiles)
        {
            auto t = tile->getGlobalRect();
            if (b.intersects(t))
            {
                bullet->setForRemove();
                tile->setForRemoved();
            }
        }
    }

    for (auto &tile : tiles)
    {
        tile->update(elapsedTime);
    }

    for(auto &enemy : enemies)
    {
        enemy->update(elapsedTime);
    }

    player->update(elapsedTime);
    staff->update(elapsedTime);

    for(auto &aliveTank : aliveTanks)
    {
        aliveTank->update(elapsedTime);
    }



    //        case Entity::ObjectType::Player:
    //            auto player = static_cast<Player*>(entity.get());
    //            player->adaptPlayerPosition();
    //            auto playerBounds = player->getGlobalRect();
    //            sf::IntRect result;

    //            for (auto &anotherEntity : entities)
    //            {
    //                auto entityBounds = anotherEntity->getGlobalRect();

    //                if(playerBounds.intersects(entityBounds, result))
    //                {
    //                    switch(player->getDirection())
    //                    {
    //                    case SETTINGS::Direction::RIGHT:
    //                        player->setPosition(playerBounds.left + playerBounds.width/2 - result.width, playerBounds.top + playerBounds.width/2);
    //                        break;
    //                    case SETTINGS::Direction::LEFT:
    //                        player->setPosition(playerBounds.left + playerBounds.width/2 + result.width, playerBounds.top + playerBounds.width/2);
    //                        break;
    //                    case SETTINGS::Direction::UP:
    //                        player->setPosition(playerBounds.left + playerBounds.width/2, playerBounds.top + playerBounds.height/2 + result.height);
    //                        break;
    //                    case SETTINGS::Direction::DOWN:
    //                        player->setPosition(playerBounds.left + playerBounds.width/2, playerBounds.top + playerBounds.height/2 - result.height);
    //                        break;
    //                    }
    //                }
    //            }



    //    auto p = player.getGlobalRect();
    //    auto baseRect = base.getGlobalRect();

    //    //Коллизии bullet
    //    // со стенками окна и с тайлами карты
    //    for (const auto& bullet : bullets)
    //    {
    //        // со стенками окна
    //        auto b = bullet->getGlobalRect();
    //        if(b.top < SETTINGS::SIZE_TILE_MAP ||
    //                (b.left < (SETTINGS::SIZE_TILE_MAP*2)) ||
    //                (b.top + b.height > (SETTINGS::WINDOW_HEIGHT - SETTINGS::SIZE_TILE_MAP)) ||
    //                (b.left + b.width > (SETTINGS::WINDOW_WIDTH - SETTINGS::SIZE_TILE_MAP*4)))
    //        {
    //            bullet->setForRemoved();
    //        }

    //        // с другими пулями
    //        for (const auto& otherBullet : bullets)
    //        {
    //            if (otherBullet != bullet)
    //            {
    //                auto ob = otherBullet->getGlobalRect();
    //                if (b.intersects(ob))
    //                {
    //                    bullet->setForRemoved();
    //                    otherBullet->setForRemoved();
    //                }
    //            }

    //        }

    //        // с тайлами карты
    //        for (const auto& tile : tiles)
    //        {
    //            auto t = tile->getGlobalRect();

    //            if(t.intersects(b))
    //            {
    //                if(tile->getType() == SETTINGS::Tile::Brick)
    //                {
    //                    tile->setRemoved(true);
    //                    bullet->setForRemoved();
    //                }
    //                if(tile->getType() == SETTINGS::Tile::Concrete)
    //                {
    //                    bullet->setForRemoved();
    //                }
    //            }
    //        }

    //        // с врагами
    //        for(auto &enemy : enemies)
    //        {
    //            auto e = enemy->getGlobalRect();
    //            if (e.intersects(b) && bullet->getType() == SETTINGS::bulletType::Player)
    //            {
    //                bullet->setForRemoved();
    //                enemy->setRemoved(true);
    //                tanks.pop_back();
    //            }
    //        }

    //        // с Игроком
    //        if(p.intersects(b) && bullet->getType() == SETTINGS::bulletType::Enemy)
    //        {
    //            bullet->setForRemoved();
    //            player.setRemoved(true);
    //        }

    //        // С базой

    //        if(baseRect.intersects(b))
    //        {
    //            bullet->setForRemoved();
    //            base.setRemoved(true);
    //        }

    //    }

    //    // TODO Enemy with Enemy


    //    // Коллизии Player with tile
    //    for (auto &tile : tiles)
    //    {
    //        if (tile->getType() != SETTINGS::Tile::Ice && tile->getType() != SETTINGS::Tile::Shrub)
    //        {
    //            auto r = tile->getGlobalRect();
    //            sf::IntRect result;

    //            if(p.intersects(r, result))
    //            {
    //                switch(player.getDirection())
    //                {
    //                case SETTINGS::Direction::RIGHT:
    //                    player.setPosition(p.left + p.width/2 - result.width, p.top + p.width/2);
    //                    break;
    //                case SETTINGS::Direction::LEFT:
    //                    player.setPosition(p.left + p.width/2 + result.width, p.top + p.width/2);
    //                    break;
    //                case SETTINGS::Direction::UP:
    //                    player.setPosition(p.left + p.width/2, p.top + p.height/2 + result.height);
    //                    break;
    //                case SETTINGS::Direction::DOWN:
    //                    player.setPosition(p.left + p.width/2, p.top + p.height/2 - result.height);
    //                    break;
    //                }
    //            }
    //        }
    //    }

    //    // Коллизии player with base
    //    sf::IntRect res;
    //    if (p.intersects(baseRect, res))
    //    {
    //        switch(player.getDirection())
    //        {
    //        case SETTINGS::Direction::RIGHT:
    //            player.setPosition(p.left + p.width/2 - res.width, p.top + p.width/2);
    //            break;
    //        case SETTINGS::Direction::LEFT:
    //            player.setPosition(p.left + p.width/2 + res.width, p.top + p.width/2);
    //            break;
    //        case SETTINGS::Direction::UP:
    //            player.setPosition(p.left + p.width/2, p.top + p.height/2 + res.height);
    //            break;
    //        case SETTINGS::Direction::DOWN:
    //            player.setPosition(p.left + p.width/2, p.top + p.height/2 - res.height);
    //            break;
    //        }
    //    }


    //    //Коллизии Enemy
    //    for (const auto& enemy : enemies)
    //    {
    //        auto e = enemy->getGlobalRect();
    //        for(const auto& tile : tiles)
    //        {
    //            if (tile->getType() != SETTINGS::Tile::Ice && tile->getType() != SETTINGS::Tile::Shrub)
    //            {
    //                sf::IntRect result;
    //                auto r = tile->getGlobalRect();

    //                if(e.intersects(r, result))
    //                {
    //                    //enemy->changeDirectionMoving();
    //                    switch(enemy->getDirection())
    //                    {
    //                    case SETTINGS::Direction::RIGHT:
    //                        enemy->setPosition(e.left + e.width/2 - result.width, e.top + e.height/2);
    //                        break;
    //                    case SETTINGS::Direction::LEFT:
    //                        enemy->setPosition(e.left + e.width/2 + result.width, e.top + e.height/2);
    //                        break;
    //                    case SETTINGS::Direction::UP:
    //                        enemy->setPosition(e.left + e.width/2, e.top + e.height/2 + result.height);
    //                        break;
    //                    case SETTINGS::Direction::DOWN:
    //                        enemy->setPosition(e.left + e.width/2, e.top + e.height/2 - result.height);
    //                        break;
    //                    }
    //                }
    //            }
    //        }


    //        //коллизии с базой
    //        sf::IntRect result;
    //        if (e.intersects(baseRect, result))
    //        {
    //            switch(enemy->getDirection())
    //            {
    //            case SETTINGS::Direction::RIGHT:
    //                enemy->setPosition(e.left + e.width/2 - result.width, e.top + e.height/2);
    //                break;
    //            case SETTINGS::Direction::LEFT:
    //                enemy->setPosition(e.left + e.width/2 + result.width, e.top + e.height/2);
    //                break;
    //            case SETTINGS::Direction::UP:
    //                enemy->setPosition(e.left + e.width/2, e.top + e.height/2 + result.height);
    //                break;
    //            case SETTINGS::Direction::DOWN:
    //                enemy->setPosition(e.left + e.width/2, e.top + e.height/2 - result.height);
    //                break;
    //            }
    //        }
    //    }

    // удаление Bullets
    auto itBullet = std::remove_if(bullets.begin(), bullets.end(), [](const std::unique_ptr<Bullet>& c)
    {
        return !c->isAlive();
    });
    bullets.erase(itBullet, bullets.end());

    // удаление тайлов карты
    auto itTile = std::remove_if(tiles.begin(), tiles.end(), [](const std::unique_ptr<Tile>& c)
    {
        return !c->isAlive();
    });
    tiles.erase(itTile, tiles.end());

    //удаление enemy
    auto itEnemy = std::remove_if(enemies.begin(), enemies.end(), [](const std::unique_ptr<Enemy>& c)
    {
        return !c->isAlive();
    });
    enemies.erase(itEnemy, enemies.end());

    //удаление элемента счетчика танков
    auto itCountTank = std::remove_if(aliveTanks.begin(), aliveTanks.end(), [](const std::unique_ptr<CounterEnemy>& c)
    {
        return c->getRemoved();
    });
    aliveTanks.erase(itCountTank, aliveTanks.end());

}

void Game::render()
{
    window.clear();

    for (const auto& border : borders)
    {
        window.draw(border);
    }

    for (const auto &aliveTank : aliveTanks)
    {
        window.draw(*aliveTank);
    }

    for (const auto &tile : tiles)
    {
        window.draw(*tile);
    }

    for (const auto &bullet : bullets)
    {
        window.draw(*bullet);
    }

    for (const auto &enemy : enemies)
    {
        window.draw(*enemy);
    }

    if (player->isAlive())
    {
        window.draw(*player);
    }

    window.draw(*staff);
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
