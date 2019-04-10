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
    fpsInfo.text.setPosition(SETTINGS::FPS_POS, SETTINGS::FPS_POS);
    fpsInfo.text.setCharacterSize(SETTINGS::FPS_FONT_SIZE);

    auto player = std::unique_ptr<Player>(new Player(texture, SETTINGS::PLAYER_OFFSET, {SETTINGS::PLAYER_POSITION}));
    auto base = std::unique_ptr<Staff> (new Staff(texture, SETTINGS::BASE_OFFSET, SETTINGS::BASE_POSITION));
    entities.push_back(std::move(player));
    entities.push_back(std::move(base));


    // Количество оставшихся enemy
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            auto count = std::unique_ptr<CounterEnemy>(new CounterEnemy(texture, {49, 273}, {j * 16 + 470, i * 16 + 50}));
            entities.push_back(std::move(count));
        }
    }

    // чтение данных уровня из файла (int level)
    std::vector<std::string> map = utils::readFromFileMap(1);

    // Создание тайлов карты
    sf::Vector2i offset;
    std::string str;
    int type;
    for (int i = 0; i < SETTINGS::COUNT_TILES_MAP; ++i)
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
                tile->setPosition(SETTINGS::MAP_OFFSET_LEFT + static_cast<int>(j) * SETTINGS::SIZE_TILE_MAP,
                               SETTINGS::MAP_OFFSET_TOP + static_cast<int>(i) * SETTINGS::SIZE_TILE_MAP);
                entities.push_back(std::move(tile));
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

    borders = {&topBorder, &leftBorder, &bottomBorder, &rightBorder};

    // Создание врагов
    for (int i = 0; i < SETTINGS::MAX_NUM_ENEMY; ++i)
    {
        auto enemy = std::unique_ptr<Enemy>(new Enemy(texture, SETTINGS::EnemyType::Simple, utils::setStartPosition(i)));
        entities.push_back(std::move(enemy));
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

        if (enemyTime.asSeconds() > (1.5f /entities.size()))
        {
            while (enemyTime > SETTINGS::TIME_PER_FRAME)
            {
                enemyTime -= SETTINGS::TIME_PER_FRAME;

            }
            //            if (entities.size() > 0)
            //            {
            //                int i = random(0, enemies.size()-1);
            //                enemies[i]->changeDirectionMoving();
            //            }
            if (entities.size() < SETTINGS::MAX_NUM_ENEMY and Enemy::getCount() > 0)
            {
                auto enemy = std::unique_ptr<Entity>(new Enemy(texture, SETTINGS::EnemyType::Simple, utils::setStartPosition()));
                entities.push_back(std::move(enemy));
            }
        }

        while (timeSinceLastUpdate > SETTINGS::TIME_PER_FRAME)
        {
            timeSinceLastUpdate -= SETTINGS::TIME_PER_FRAME;
            processEvents();
            update(SETTINGS::TIME_PER_FRAME);
        }

        bulletTime += elapsedTime;
        if (player.shoot)
        {
            if (bulletTime.asSeconds() > 0.4f)
            {
                while(bulletTime > SETTINGS::TIME_PER_FRAME)
                {
                    bulletTime -= SETTINGS::TIME_PER_FRAME;
                }
                auto b = std::unique_ptr<Bullet>(new Bullet(texture, {1, 352}, player.getPosition()));
                b->setDirection(player.getDirection());
                b->setType(SETTINGS::bulletType::Player);
                bullets.push_back(std::move(b));

                player.shoot = false;
            }
        }
        enemyBulletTime += elapsedTime;
        if (enemyBulletTime.asSeconds() > 1.f)
        {
            while(enemyBulletTime > SETTINGS::TIME_PER_FRAME)
            {
                enemyBulletTime -= SETTINGS::TIME_PER_FRAME;
            }
            for (auto &enemy : enemies)
            {
                auto b = std::unique_ptr<Bullet>(new Bullet(texture, {1, 352}, enemy->getPosition()));
                b->setDirection(enemy->getDirection());
                b->setType(SETTINGS::bulletType::Enemy);
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
    // обработка нажатий клавиш
    static_cast<Player*>(entities[0].get())->handleRealTimeInput();
}

void Game::update(const sf::Time &elapsedTime)
{
    for(const auto &entity : entities)
    {
        entity->update(elapsedTime);

        switch (entity->getObjectType())
        {
        case SETTINGS::ObjectType::Enemy:
            static_cast<Enemy*>(entity.get())->adaptEnemyPosition();
            break;

        case SETTINGS::ObjectType::Player:
            static_cast<Player*>(entity.get())->adaptPlayerPosition();
        }
    }
////////////////////////////////////////////////////////
/// ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    auto p = player.getGlobalRect();
    auto baseRect = base.getGlobalRect();

    base.update(elapsedTime);

    //Коллизии bullet
    // со стенками окна и с тайлами карты
    for (const auto& bullet : bullets)
    {
        // со стенками окна
        auto b = bullet->getGlobalRect();
        if(b.top < SETTINGS::SIZE_TILE_MAP ||
                (b.left < (SETTINGS::SIZE_TILE_MAP*2)) ||
                (b.top + b.height > (SETTINGS::WINDOW_HEIGHT - SETTINGS::SIZE_TILE_MAP)) ||
                (b.left + b.width > (SETTINGS::WINDOW_WIDTH - SETTINGS::SIZE_TILE_MAP*4)))
        {
            bullet->setForRemoved();
        }

        // с другими пулями
        for (const auto& otherBullet : bullets)
        {
            if (otherBullet != bullet)
            {
                auto ob = otherBullet->getGlobalRect();
                if (b.intersects(ob))
                {
                    bullet->setForRemoved();
                    otherBullet->setForRemoved();
                }
            }

        }

        // с тайлами карты
        for (const auto& tile : tiles)
        {
            auto t = tile->getGlobalRect();

            if(t.intersects(b))
            {
                if(tile->getType() == SETTINGS::Tile::Brick)
                {
                    tile->setRemoved(true);
                    bullet->setForRemoved();
                }
                if(tile->getType() == SETTINGS::Tile::Concrete)
                {
                    bullet->setForRemoved();
                }
            }
        }

        // с врагами
        for(auto &enemy : enemies)
        {
            auto e = enemy->getGlobalRect();
            if (e.intersects(b) && bullet->getType() == SETTINGS::bulletType::Player)
            {
                bullet->setForRemoved();
                enemy->setRemoved(true);
                tanks.pop_back();
            }
        }

        // с Игроком
        if(p.intersects(b) && bullet->getType() == SETTINGS::bulletType::Enemy)
        {
            bullet->setForRemoved();
            player.setRemoved(true);
        }

        // С базой

        if(baseRect.intersects(b))
        {
            bullet->setForRemoved();
            base.setRemoved(true);
        }

    }

    // TODO Enemy with Enemy


    // Коллизии Player with tile
    for (auto &tile : tiles)
    {
        if (tile->getType() != SETTINGS::Tile::Ice && tile->getType() != SETTINGS::Tile::Shrub)
        {
            auto r = tile->getGlobalRect();
            sf::IntRect result;

            if(p.intersects(r, result))
            {
                switch(player.getDirection())
                {
                case SETTINGS::Direction::RIGHT:
                    player.setPosition(p.left + p.width/2 - result.width, p.top + p.width/2);
                    break;
                case SETTINGS::Direction::LEFT:
                    player.setPosition(p.left + p.width/2 + result.width, p.top + p.width/2);
                    break;
                case SETTINGS::Direction::UP:
                    player.setPosition(p.left + p.width/2, p.top + p.height/2 + result.height);
                    break;
                case SETTINGS::Direction::DOWN:
                    player.setPosition(p.left + p.width/2, p.top + p.height/2 - result.height);
                    break;
                }
            }
        }
    }

    // Коллизии player with base
    sf::IntRect res;
    if (p.intersects(baseRect, res))
    {
        switch(player.getDirection())
        {
        case SETTINGS::Direction::RIGHT:
            player.setPosition(p.left + p.width/2 - res.width, p.top + p.width/2);
            break;
        case SETTINGS::Direction::LEFT:
            player.setPosition(p.left + p.width/2 + res.width, p.top + p.width/2);
            break;
        case SETTINGS::Direction::UP:
            player.setPosition(p.left + p.width/2, p.top + p.height/2 + res.height);
            break;
        case SETTINGS::Direction::DOWN:
            player.setPosition(p.left + p.width/2, p.top + p.height/2 - res.height);
            break;
        }
    }


    //Коллизии Enemy
    for (const auto& enemy : enemies)
    {
        auto e = enemy->getGlobalRect();
        for(const auto& tile : tiles)
        {
            if (tile->getType() != SETTINGS::Tile::Ice && tile->getType() != SETTINGS::Tile::Shrub)
            {
                sf::IntRect result;
                auto r = tile->getGlobalRect();

                if(e.intersects(r, result))
                {
                    //enemy->changeDirectionMoving();
                    switch(enemy->getDirection())
                    {
                    case SETTINGS::Direction::RIGHT:
                        enemy->setPosition(e.left + e.width/2 - result.width, e.top + e.height/2);
                        break;
                    case SETTINGS::Direction::LEFT:
                        enemy->setPosition(e.left + e.width/2 + result.width, e.top + e.height/2);
                        break;
                    case SETTINGS::Direction::UP:
                        enemy->setPosition(e.left + e.width/2, e.top + e.height/2 + result.height);
                        break;
                    case SETTINGS::Direction::DOWN:
                        enemy->setPosition(e.left + e.width/2, e.top + e.height/2 - result.height);
                        break;
                    }
                }
            }
        }


        //коллизии с базой
        sf::IntRect result;
        if (e.intersects(baseRect, result))
        {
            switch(enemy->getDirection())
            {
            case SETTINGS::Direction::RIGHT:
                enemy->setPosition(e.left + e.width/2 - result.width, e.top + e.height/2);
                break;
            case SETTINGS::Direction::LEFT:
                enemy->setPosition(e.left + e.width/2 + result.width, e.top + e.height/2);
                break;
            case SETTINGS::Direction::UP:
                enemy->setPosition(e.left + e.width/2, e.top + e.height/2 + result.height);
                break;
            case SETTINGS::Direction::DOWN:
                enemy->setPosition(e.left + e.width/2, e.top + e.height/2 - result.height);
                break;
            }
        }
    }

    // удаление Bullets
    auto itBullet = std::remove_if(bullets.begin(), bullets.end(), [](const std::unique_ptr<Bullet>& c)
    {
        return !c->isAlive();
    });
    bullets.erase(itBullet, bullets.end());

    // удаление тайлов карты
    auto itTile = std::remove_if(tiles.begin(), tiles.end(), [](const std::unique_ptr<Tile>& c)
    {
        return c->getRemoved();
    });
    tiles.erase(itTile, tiles.end());

    //удаление enemy
    auto itEnemy = std::remove_if(entities.begin(), entities.end(), [](const std::unique_ptr<Entity>& c)
    {
        return static_cast<Enemy *>(c.get())->getRemoved();
    });
    entities.erase(itEnemy, entities.end());

    //удаление элемента счетчика танков
    //    auto itCountTank = std::remove_if(tanks.begin(), tanks.end(), [](const std::unique_ptr<CountTanks>& c)
    //    {
    //        return c->getRemoved();
    //    });
    //    tanks.erase(itCountTank, tanks.end());



    //удаление player
    // delete &player;
}

void Game::render()
{
    window.clear();

    for (const auto& border : borders)
    {
        window.draw(border);
    }

    for(const auto& bullet : bullets)
    {
        window.draw(*bullet);
    }

    for (auto &tile : tiles)
    {
        if (tile->getType() == SETTINGS::Tile::Ice)
        {
            window.draw(*tile);
        }
    }


    window.draw(player);

    for (auto &enemy : entities)
    {
        window.draw(*enemy);
    }

    for (auto &tile : tiles)
    {
        if (tile->getType() != SETTINGS::Tile::Ice)
        {
            window.draw(*tile);
        }
    }

    for (auto &countTank : tanks)
    {
        window.draw(*countTank);
    }

    window.draw(base);

    window.draw(fpsInfo.text);
    // window.draw(enemyCount);
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
