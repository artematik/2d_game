#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Meteorit.h"
#include "Full.h"
#include <sstream>
#include <string>
#include <SFML/Audio.hpp>
using namespace sf;
using namespace std;

struct FrameAnim
{
	int Frame = 0;
	int Step = 100;
	int Frame1 = 0;
	int Step1 = 100;
};

void playermove(Sprite& player, Vector2f moveRec);
void playerAnim(Sprite& player, FrameAnim & FramePlAnim, int traffic);
// проверка на совпадение координат метеоритов
void Correct(Full& canister, int i, Meteorit* meteorit, int nmeteor);
// проверка на совпадение координат канистры с топливом
void CorrectFull(Full& canister, Meteorit* meteorit, int nmeteor);
// приведение целочисенного типа к строковому
string IntToStr(int number);