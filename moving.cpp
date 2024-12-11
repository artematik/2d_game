#include "moving.h"

void playermove(Sprite& player, Vector2f moveRec)
{
    player.move(moveRec);
    Vector2f pos = player.getPosition();
    if (pos.x > 1200) player.setPosition(Vector2f(1200, pos.y));
    if (pos.x < 50) player.setPosition(Vector2f(50, pos.y));
    if (pos.y > 660) player.setPosition(Vector2f(pos.x, 660));
    if (pos.y < 110) player.setPosition(Vector2f(pos.x, 110));

    if ((pos.x > 1200) && (pos.y < 110)) player.setPosition(Vector2f(1200, 110));
    if ((pos.x > 1200) && (pos.y > 660)) player.setPosition(Vector2f(1200, 660));
    if ((pos.x < 50) && (pos.y > 660)) player.setPosition(Vector2f(50, 660));
    if ((pos.x < 50) && (pos.y < 110)) player.setPosition(Vector2f(50, 660));

}

void playerAnim(Sprite& player, FrameAnim& FramePlAnim, int traffic)
{
    FramePlAnim.Frame += FramePlAnim.Step;
    player.setTextureRect(IntRect(0, FramePlAnim.Frame, 90, 90));
    if (traffic) if (FramePlAnim.Frame > 0) FramePlAnim.Step = -100;
    else FramePlAnim.Step = 0;
    else
    {
        if (FramePlAnim.Frame == 800) FramePlAnim.Step = 0;
        if (FramePlAnim.Frame <= 700) FramePlAnim.Step = 100;
    }

}
