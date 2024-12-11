#include "moving.h"

int main()
{
    srand(time(NULL));
    sf::RenderWindow win(sf::VideoMode(1280, 720), L"Сквозь тернии к звёздам");
    Image icon;
    if (!icon.loadFromFile("Image/icon.png")) {
        std::cerr << "Ошибка загрузки изображения!" << std::endl;
        return 1;
    }
    win.setIcon(32, 32, icon.getPixelsPtr());

    Texture TextureInfoPanel;
    TextureInfoPanel.loadFromFile("Image/panel.png");
    RectangleShape GameInfopanel(Vector2f(1280, 113));
    GameInfopanel.setTexture(&TextureInfoPanel);
    GameInfopanel.setPosition(Vector2f(0, 0));


    // космос
    Texture TextureSpace;
    TextureSpace.loadFromFile("Image/space.jpg");
    RectangleShape gamingBackground(Vector2f(1280,720));
    gamingBackground.setTexture(&TextureSpace);

    RectangleShape gamingBackground2(Vector2f(1280, 720));
    gamingBackground2.setTexture(&TextureSpace);
    gamingBackground2.setPosition(Vector2f(1280, 0));

    // переменные
    bool GameOver = false;
    Vector2f pos;
    Clock clock, clockAnimPlay, clockAnim, clockAnimMeteorit;
    float time, timePlayer, timeGamingBackground, timeMeteorit;

    //космиеский корабль
    int traffic = 0;
    FrameAnim FramePlAnim;
    FramePlAnim.Frame = 700;
    Vector2f moveRec;
    Texture TexturePlayer;
    TexturePlayer.loadFromFile("Image/playeranim1.png");
    Sprite player;
    player.setTexture(TexturePlayer);
    player.setTextureRect(IntRect(0, FramePlAnim.Frame, 90, 90));
    player.scale(0.7, 0.7);
    player.setPosition(Vector2f(80, 380));


    // Взрыв космического корабля
    FrameAnim DestructAnim;
    DestructAnim.Frame = 5;
    DestructAnim.Frame1 = 15;
    Texture texdest;
    texdest.loadFromFile("Image/bum.png");
    Sprite destraction;
    destraction.setTexture(texdest);
    destraction.setTextureRect(IntRect(5, 15, 95, 80));
    destraction.scale(0.7, 0.7);

    Meteorit meteorit[15];
    int nmeteorit = 15;


    while (win.isOpen()) // Игровой цикл
    {
        sf::Event event;
        // Привязка игорового процесса ко времени
        time = clock.getElapsedTime().asMicroseconds();
        timeGamingBackground = time / 6000;
        timePlayer = time / 2000;
        timeMeteorit = time / 3000;
        clock.restart();
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                win.close();
            // Управление Кораблём
            switch (event.type)
            {
            case Event::KeyPressed:
                if ((event.key.code == Keyboard::S) || (event.key.code == Keyboard::Down))
                { 
                    moveRec.y = 0.3 * timePlayer;
                    traffic = 2;
                }
                if ((event.key.code == Keyboard::W) || (event.key.code == Keyboard::Up))
                {
                    moveRec.y = -0.3 * timePlayer;
                    traffic = 1;
                }
                if ((event.key.code == Keyboard::A) || (event.key.code == Keyboard::Left))
                {
                    moveRec.x = -0.3 * timePlayer;
                }
                if ((event.key.code == Keyboard::D) || (event.key.code == Keyboard::Right))
                {
                    moveRec.x = 0.3 * timePlayer;
                }
                break;
            case Event::KeyReleased:
                if ((event.key.code == Keyboard::S) || (event.key.code == Keyboard::Down))
                {
                    moveRec.y = 0;
                    traffic = 0;
                }
                if ((event.key.code == Keyboard::W) || (event.key.code == Keyboard::Up))
                {
                    moveRec.y = 0;
                    traffic = 0;
                }
                if ((event.key.code == Keyboard::A) || (event.key.code == Keyboard::Left)) moveRec.x = 0;
                if ((event.key.code == Keyboard::D) || (event.key.code == Keyboard::Right)) moveRec.x = 0;
                break;
            default:
                break;
            }
        }
        if (GameOver)
        {
            // Анимация взрыва
            if (clockAnimMeteorit.getElapsedTime() > milliseconds(80))
            {
                clockAnimMeteorit.restart();
                DestructAnim.Frame += DestructAnim.Step;
                if (DestructAnim.Frame > 405)
                {
                    DestructAnim.Frame1 += DestructAnim.Step1;
                    DestructAnim.Frame = 5;
                }
                if (DestructAnim.Frame1 > 415)
                {
                    GameOver = false;
                    player.setPosition(Vector2f(80, 380));
                    for (int i = 0; i < nmeteorit; ++i) meteorit[i].restart();
                    DestructAnim.Frame = 5;
                    DestructAnim.Frame1 = 15;
                }
                else
                {
                    destraction.setTextureRect(IntRect(DestructAnim.Frame, DestructAnim.Frame1, 95, 80));
                }
            }
        }

        else
        {
            // Анимация игрока
            if (clockAnimPlay.getElapsedTime() > milliseconds(100))
            {
                clockAnimPlay.restart();
                playerAnim(player, FramePlAnim, traffic);

            }

            if (clockAnimMeteorit.getElapsedTime() > milliseconds(80))
            {
                clockAnimMeteorit.restart();
                for (int i = 0; i < nmeteorit; ++i) meteorit[i].animation();
            }

            // Космос
            gamingBackground.move(-0.2 * timeGamingBackground, 0);
            pos = gamingBackground.getPosition();
            if (pos.x < -1280) gamingBackground.setPosition(1280, pos.y);

            gamingBackground2.move(-0.2 * timeGamingBackground, 0);
            pos = gamingBackground2.getPosition();
            if (pos.x < -1280) gamingBackground2.setPosition(1280, pos.y);

            playermove(player, moveRec);// Движение космического коробля

            for (int i = 0; i < nmeteorit;++i) // движение метеоритов
            {
                meteorit[i].move(timeMeteorit);
                if (meteorit[i].collision(player.getGlobalBounds()))
                {
                    GameOver = true;
                    destraction.setPosition(player.getPosition().x, player.getPosition().y);
                    break;
                }
            }
        }

        
        // отрисовка объектов
        win.clear();
        win.draw(gamingBackground2); // звездное небо
        win.draw(gamingBackground); // звёздное небо
        if (GameOver)
        {
            win.draw(destraction);
        }
        else win.draw(player);
        win.draw(player); // космический корабль
        win.draw(GameInfopanel); // игровая панель
        for (int i = 0; i < nmeteorit; i++) meteorit[i].draw(win);
        win.display();
    }

    return 0;
}