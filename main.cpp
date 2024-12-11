#include "moving.h"

int main()
{
    srand(time(NULL));
    sf::RenderWindow win(sf::VideoMode(1280, 720), L"������ ������ � ������");
    Image icon;
    if (!icon.loadFromFile("Image/icon.png")) {
        std::cerr << "������ �������� �����������!" << std::endl;
        return 1;
    }
    win.setIcon(32, 32, icon.getPixelsPtr());

    // ������� ������
    Texture TextureInfoPanel;
    TextureInfoPanel.loadFromFile("Image/panel.png");
    RectangleShape GameInfopanel(Vector2f(1280, 113));
    GameInfopanel.setTexture(&TextureInfoPanel);
    GameInfopanel.setPosition(Vector2f(0, 0));
    
    // �������
    int pusk = 0; // ���������� ��� �������� ���������� � ���-�� ������ ���������� ��������
    double amountfull = 0;
    int full = 100; // ����� ������� � �������
    Text textfull, plusfull, text_pause, end_game;
    Font GameFont; // ����� ��� ������
    if (!GameFont.loadFromFile("Font/BankGothic Md BT Medium.otf"))
    {
        std::cerr << "������ �������� ������!" << std::endl;
        return 2;
    }

    // ������� ������������ �������
    textfull.setFont(GameFont);
    textfull.setFillColor(Color::Green);
    textfull.setCharacterSize(30);
    textfull.setPosition(1070, 20);

    // ������� � ���������
    plusfull.setFont(GameFont);
    plusfull.setFillColor(Color::Red);
    plusfull.setCharacterSize(25);

    // ����� ����
    text_pause.setFont(GameFont);
    text_pause.setFillColor(Color::Red);
    text_pause.setCharacterSize(100);
    text_pause.setString(L"����� ����");
    text_pause.setPosition(300, 333);

    // �����
    end_game.setFont(GameFont);
    end_game.setFillColor(Color::Magenta);
    end_game.setCharacterSize(50);
    end_game.setString(L"� � � � �");
    end_game.setPosition(500, 333);

    // ������
    Texture TextureSpace;
    TextureSpace.loadFromFile("Image/space.jpg");
    RectangleShape gamingBackground(Vector2f(1280,720));
    gamingBackground.setTexture(&TextureSpace);

    RectangleShape gamingBackground2(Vector2f(1280, 720));
    gamingBackground2.setTexture(&TextureSpace);
    gamingBackground2.setPosition(Vector2f(1280, 0));

    // ����������
    bool GameOver = false, GamePause=false;
    Vector2f pos;
    Clock clock, clockAnimPlay, clockAnim, clockAnimMeteorit, clockAnimText;
    float time, timePlayer, timeGamingBackground, timeMeteorit;

    //���������� �������
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


    // ����� ������������ �������
    FrameAnim DestructAnim;
    DestructAnim.Frame = 5;
    DestructAnim.Frame1 = 15;
    Texture texdest;
    texdest.loadFromFile("Image/bum.png");
    Sprite destraction;
    destraction.setTexture(texdest);
    destraction.setTextureRect(IntRect(5, 15, 95, 80));
    destraction.scale(0.7, 0.7);

    // ���������
    Meteorit meteorit[15];
    int nmeteorit = 15;

    // �������
    Full canister("Image/galon.png", 1000,1000);

    while (win.isOpen()) // ������� ����
    {
        sf::Event event;
        // �������� ��������� �������� �� �������
        time = clock.getElapsedTime().asMicroseconds();
        timeGamingBackground = time / 6000;
        timePlayer = time / 2000;
        timeMeteorit = time / 3000;
        clock.restart();
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                win.close();
            // ���������� �������
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
            // �������� ������
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
            // �������� ������
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

            // ������
            gamingBackground.move(-0.2 * timeGamingBackground, 0);
            pos = gamingBackground.getPosition();
            if (pos.x < -1280) gamingBackground.setPosition(1280, pos.y);

            gamingBackground2.move(-0.2 * timeGamingBackground, 0);
            pos = gamingBackground2.getPosition();
            if (pos.x < -1280) gamingBackground2.setPosition(1280, pos.y);

            // �������� ������������ �������
            playermove(player, moveRec);

            // �������� ����������
            for (int i = 0; i < nmeteorit;++i)
            {
                if (meteorit[i].newborn) Correct(canister, i, meteorit, nmeteorit); // �������� �� ���������� � �������������� ��������� ��� ����������
                meteorit[i].move(timeMeteorit);
                if (meteorit[i].collision(player.getGlobalBounds()))
                {
                    GameOver = true;
                    destraction.setPosition(player.getPosition().x, player.getPosition().y);
                    break;
                }
            }

            // �������
            if (canister.newborn) CorrectFull(canister, meteorit, nmeteorit);
            canister.move(timeMeteorit);

            // �������� �������
            if (canister.collision(player.getGlobalBounds()))
            {
                amountfull = 10 + rand() % 90;
                full += amountfull;
                plusfull.setString(IntToStr(amountfull));
                plusfull.setPosition(canister.getLastBonus().x, canister.getLastBonus().y);
                pusk = 40;
                canister.restart();
            }

            // ������� �� ������� ������
            // ������������� ����� ����� �����������
            textfull.setFillColor(Color::Green);
            textfull.setString(IntToStr(full) + L"����");
        }

        
        // ��������� ��������
        win.clear();
        win.draw(gamingBackground2); // �������� ����
        win.draw(gamingBackground); // ������� ����
        if (GameOver)
        {
            win.draw(destraction);
        }
        else win.draw(player);
        win.draw(player); // ����������� �������
        win.draw(GameInfopanel); // ������� ������
        for (int i = 0; i < nmeteorit; i++) meteorit[i].draw(win);
        canister.draw(win);
        win.draw(textfull);
        if (pusk > 0) win.draw(plusfull);
        win.display();
    }

    return 0;
}