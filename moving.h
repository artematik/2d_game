#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Meteorit.h"
using namespace sf;

struct FrameAnim
{
	int Frame = 0;
	int Step = 100;
	int Frame1 = 0;
	int Step1 = 100;
};

void playermove(Sprite& player, Vector2f moveRec);
void playerAnim(Sprite& player, FrameAnim & FramePlAnim, int traffic);