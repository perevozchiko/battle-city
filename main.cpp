#include <SFML/Graphics.hpp>
using namespace sf;
int main()
{
   sf::RenderWindow window(sf::VideoMode(640, 480), "testSfml1");

   sf::Image gameImage;
   gameImage.loadFromFile("sprite.bmp");
   sf::Texture gameTexture;
   gameTexture.loadFromImage(gameImage);

   sf::Sprite tank;
   tank.setTexture(gameTexture);
   tank.setPosition(250, 250);
   tank.setTextureRect(sf::IntRect(0,0,32,32));

   sf::Sprite tank2;
   tank2.setTexture(gameTexture);
   tank2.setPosition(100, 132);
   tank2.setTextureRect(sf::IntRect (128,128,32,32));


   while (window.isOpen())
       {
           sf::Event event;
           while (window.pollEvent(event))
           {
               if (event.type == sf::Event::Closed)
               window.close();
           }
           float delta = 0.01;
           if (Keyboard::isKeyPressed(Keyboard::Left)) { tank.setOrigin(16, 16); tank.move(-delta, 0); tank.setRotation(-90); }
           else if (Keyboard::isKeyPressed(Keyboard::Right)) { tank.setOrigin(16, 16); tank.move(delta, 0); tank.setRotation(90); }
           else if (Keyboard::isKeyPressed(Keyboard::Up)) { tank.setOrigin(16, 16); tank.setRotation(0); tank.move(0, -delta); }
           else if (Keyboard::isKeyPressed(Keyboard::Down)) { tank.setOrigin(16, 16); tank.setRotation(180); tank.move(0, delta); }
           if (Keyboard::isKeyPressed(Keyboard::Space)) { tank.setTextureRect(sf::IntRect(128,128,32,32)); }
           if (Keyboard::isKeyPressed(Keyboard::A)) { tank.setTextureRect(sf::IntRect(0,0,32,32)); }

//           if (Keyboard::isKeyPressed(Keyboard::Left)) { tank2.setOrigin(16, 16); tank2.move(-delta, 0); tank2.setRotation(-90); }
//           else if (Keyboard::isKeyPressed(Keyboard::Right)) { tank2.setOrigin(16, 16); tank2.move(delta, 0); tank2.setRotation(90); }
//           else if (Keyboard::isKeyPressed(Keyboard::Up)) { tank2.setOrigin(16, 16); tank2.setRotation(0); tank2.move(0, -delta); }
//           else if (Keyboard::isKeyPressed(Keyboard::Down)) { tank2.setOrigin(16, 16); tank2.setRotation(180); tank2.move(0, delta); }
//           if (Keyboard::isKeyPressed(Keyboard::Space)) { tank2.setTextureRect(sf::IntRect(128,128,32,32)); }
//           if (Keyboard::isKeyPressed(Keyboard::A)) { tank2.setTextureRect(sf::IntRect(0,0,32,32)); }

           window.clear();
           window.draw(tank);
           window.draw(tank2);
           window.display();
       }

   return 0;
}
