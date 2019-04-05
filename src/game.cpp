#include "game.h"
typedef unsigned long ul;

namespace BattleCity {

Game::Game(const sf::String& name, const sf::ContextSettings& settings) :
    window(sf::VideoMode(SETTINGS::WINDOW_WIDTH, SETTINGS::WINDOW_HEIGHT), name, sf::Style::Titlebar | sf::Style::Close, settings),
    //TODO сделать offset и position по умолчанию
    player(texture, {3, 5}, {SETTINGS::PLAYER_POSITION})

{
    texture.loadFromFile(SETTINGS::PATH_IMAGES);

    // FPS
    font.loadFromFile(SETTINGS::PATH_FONTS);
    fpsInfo.text.setFont(font);
    fpsInfo.text.setPosition(SETTINGS::FPS_POS, SETTINGS::FPS_POS);
    fpsInfo.text.setCharacterSize(SETTINGS::FPS_FONT_SIZE);

    // Отображение количества enemy за раунд
    enemyCount.setFont(font);
    enemyCount.setPosition(5, 18);
    enemyCount.setCharacterSize(SETTINGS::FPS_FONT_SIZE);

    // чтение данных уровня из файла (int level)
    std::vector<std::string> map = utils::readFromFileMap(1);

    // Создание тайлов карты
    sf::Vector2i offset;
    std::string str;
    int type;
    for (ul i = 0; i < SETTINGS::COUNT_TILES_MAP; ++i)
    {
        str  = map[i];
        for (ul j = 0; j < SETTINGS::COUNT_TILES_MAP; ++j)
        {
            type = utils::charToInt(str.c_str()[j]);
            if (type != 0)
            {
                offset = utils::setOffset(type);
                auto t = std::unique_ptr<Tile>(new Tile(texture, offset));
                t->setType(type);
                t->setPosition(SETTINGS::MAP_OFFSET_LEFT + static_cast<int>(j) * SETTINGS::SIZE_TILE_MAP,
                               SETTINGS::MAP_OFFSET_TOP + static_cast<int>(i) * SETTINGS::SIZE_TILE_MAP);
                tiles.push_back(std::move(t));
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
        auto en = std::unique_ptr<Enemy>(new Enemy());
        sf::Vector2i offset = utils::getEnemyType(i);

        en->setTexture(texture, offset);
        int posX = SETTINGS::MAP_SIZE * i/2 + (i%2) * SETTINGS::SIZE_TILE_ENEMY.x/2;
        int posY = SETTINGS::SIZE_TILE_ENEMY.y/2;
        //std::cout << posX << " " << posY << std::endl;
        en->setPosition(posX, posY);
        en->setDirection(SETTINGS::Direction::DOWN);
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
            while (enemyTime > SETTINGS::TIME_PER_FRAME)
            {
                enemyTime -= SETTINGS::TIME_PER_FRAME;

            }
            if (enemies.size() > 0)
            {
                std::size_t i = static_cast<std::size_t>(random(0, static_cast<int>(enemies.size()-1)));
                enemies[i]->changeDirectionMoving();
            }
            if (enemies.size() < SETTINGS::MAX_NUM_ENEMY and Enemy::getCount() > 0)
            {
                int i = random(0, 3);
                auto en = std::unique_ptr<Enemy>(new Enemy());
                sf::Vector2i offset = utils::getEnemyType(i);

                en->setTexture(texture, offset);
                int posX = SETTINGS::WINDOW_WIDTH * i/2 + (i%2) * SETTINGS::SIZE_TILE_ENEMY.x/2;
                int posY = SETTINGS::SIZE_TILE_ENEMY.y/2;
                //std::cout << posX << " " << posY << std::endl;
                en->setPosition(posX, posY);
                en->setDirection(SETTINGS::Direction::DOWN);
                enemies.push_back(std::move(en));
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
            if (bulletTime.asSeconds() > 0.2f)
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

        enemyCount.setString("Enemy: " + std::to_string(Enemy::getCount()));

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
        // со стенками окна
        auto b = bullet->getGlobalRect();
        if(b.top < SETTINGS::SIZE_TILE_MAP ||
                (b.left < (SETTINGS::SIZE_TILE_MAP*2)) ||
                (b.top + b.height > (SETTINGS::WINDOW_HEIGHT - SETTINGS::SIZE_TILE_MAP)) ||
                (b.left + b.width > (SETTINGS::WINDOW_WIDTH - SETTINGS::SIZE_TILE_MAP*4)))
        {
            bullet->setRemoved(true);
        }

        // с другими пулями
        for (const auto& otherBullet : bullets)
        {
            if (otherBullet != bullet)
            {
                auto ob = otherBullet->getGlobalRect();
                if (b.intersects(ob))
                {
                    bullet->setRemoved(true);
                    otherBullet->setRemoved(true);
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
                    bullet->setRemoved(true);
                }
                if(tile->getType() == SETTINGS::Tile::Concrete)
                {
                    bullet->setRemoved(true);
                }
            }
        }

        // с врагами
        for(auto &enemy : enemies)
        {
            auto e = enemy->getGlobalRect();
            if (e.intersects(b) && bullet->getType() == SETTINGS::bulletType::Player)
            {
                bullet->setRemoved(true);
                enemy->setRemoved(true);
            }
        }

        // с Игроком
        if(p.intersects(b) && bullet->getType() == SETTINGS::bulletType::Enemy)
        {
            bullet->setRemoved(true);
            player.setRemoved(true);
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

    // enemy with player collisions
    //    for (auto &enemy : enemies)
    //    {
    //        auto e = enemy->getGlobalRect();

    //        switch (player.getDirection())
    //        {
    //        case SETTINGS::Direction::UP:

    //            break;

    //        }

    //    }

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


    for (auto &enemy : enemies)
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
    window.draw(fpsInfo.text);
    window.draw(enemyCount);
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
