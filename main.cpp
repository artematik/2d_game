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

    // Игровая панель
    Texture TextureInfoPanel;
    TextureInfoPanel.loadFromFile("Image/panel.png");
    RectangleShape GameInfopanel(Vector2f(1280, 113));
    GameInfopanel.setTexture(&TextureInfoPanel);
    GameInfopanel.setPosition(Vector2f(0, 0));
    
    // Топливо
    int pusk = 0; // переменная для задержки информации о кол-ве заряда полученным топливом
    double amountfull = 0;
    int full = 100; // объём топлива в корабле
    Text textfull, plusfull, text_pause, end_game;
    Font GameFont; // шрифт для текста
    if (!GameFont.loadFromFile("Font/BankGothic Md BT Medium.otf"))
    {
        std::cerr << "Ошибка загрузки шрифта!" << std::endl;
        return 2;
    }

    // Топливо космического корабля
    textfull.setFont(GameFont);
    textfull.setFillColor(Color::Green);
    textfull.setCharacterSize(30);
    textfull.setPosition(1070, 20);

    // Топливо в канистрах
    plusfull.setFont(GameFont);
    plusfull.setFillColor(Color::Red);
    plusfull.setCharacterSize(25);

    // Конец игры
    text_pause.setFont(GameFont);
    text_pause.setFillColor(Color::Red);
    text_pause.setCharacterSize(100);
    text_pause.setString(L"Конец игры");
    text_pause.setPosition(300, 333);

    // Пауза
    end_game.setFont(GameFont);
    end_game.setFillColor(Color::Magenta);
    end_game.setCharacterSize(50);
    end_game.setString(L"П А У З А");
    end_game.setPosition(500, 333);

    // космос
    Texture TextureSpace;
    TextureSpace.loadFromFile("Image/space.jpg");
    RectangleShape gamingBackground(Vector2f(1280,720));
    gamingBackground.setTexture(&TextureSpace);

    RectangleShape gamingBackground2(Vector2f(1280, 720));
    gamingBackground2.setTexture(&TextureSpace);
    gamingBackground2.setPosition(Vector2f(1280, 0));

    // переменные
    bool GameOver = false, GamePause=false;
    Vector2f pos;
    Clock clock, clockAnimPlay, clockAnim, clockAnimMeteorit, clockAnimText;
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

    // Метеориты
    Meteorit meteorit[15];
    int nmeteorit = 15;

    // Топливо
    Full canister("Image/galon.png", 1000,1000);

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
                    if (full!=0)
                    {
                        moveRec.y = 0.3 * timePlayer;
                        traffic = 2;
                        full--;
                    }
                }
                if ((event.key.code == Keyboard::W) || (event.key.code == Keyboard::Up))
                {
                    if (full != 0)
                    {
                        moveRec.y = -0.3 * timePlayer;
                        traffic = 1;
                        full--;
                    }
                }
                if ((event.key.code == Keyboard::A) || (event.key.code == Keyboard::Left))
                {
                    if (full != 0)
                    {
                        moveRec.x = -0.3 * timePlayer;
                        full--;
                    }
                }
                if ((event.key.code == Keyboard::D) || (event.key.code == Keyboard::Right))
                {
                    if (full != 0)
                    {
                        moveRec.x = 0.3 * timePlayer;
                        full--;
                    }
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
                    canister.restart();
                    DestructAnim.Frame = 5;
                    DestructAnim.Frame1 = 15;
                    full = 100;
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

            if (clockAnimText.getElapsedTime() > milliseconds(50))
            {
                clockAnimMeteorit.restart();
                if (pusk > 0)
                {
                    pusk--;
                    plusfull.move(0, -1);
                }
            }

            // Космос
            gamingBackground.move(-0.2 * timeGamingBackground, 0);
            pos = gamingBackground.getPosition();
            if (pos.x < -1280) gamingBackground.setPosition(1280, pos.y);

            gamingBackground2.move(-0.2 * timeGamingBackground, 0);
            pos = gamingBackground2.getPosition();
            if (pos.x < -1280) gamingBackground2.setPosition(1280, pos.y);

            // Движение космического коробля
            playermove(player, moveRec);

            // Движение метеоритов
            for (int i = 0; i < nmeteorit;++i)
            {
                if (meteorit[i].newborn) Correct(canister, i, meteorit, nmeteorit); // проверка на совпадение и переназначение координат для метеоритов
                meteorit[i].move(timeMeteorit);
                if (meteorit[i].collision(player.getGlobalBounds()))
                {
                    GameOver = true;
                    destraction.setPosition(player.getPosition().x, player.getPosition().y);
                    break;
                }
            }

            // Топливо
            if (canister.newborn) CorrectFull(canister, meteorit, nmeteorit);
            canister.move(timeMeteorit);

            // Заправка корабля
            if (canister.collision(player.getGlobalBounds()))
            {
                amountfull = 10 + rand() % 90;
                full += amountfull;
                plusfull.setString(IntToStr(amountfull));
                plusfull.setPosition(canister.getLastBonus().x, canister.getLastBonus().y);
                pusk = 40;
                canister.restart();
            }

            // Топливо на игровой панели
            // необязательно потом можно реализовать
            textfull.setFillColor(Color::Green);
            textfull.setString(IntToStr(full) + L"тонн");
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
        canister.draw(win);
        win.draw(textfull);
        if (pusk > 0) win.draw(plusfull);
        win.display();
    }

    return 0;
}