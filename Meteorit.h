#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Meteorit
{
public:
	Meteorit();
	~Meteorit();

	void move(float & time);
	void draw(RenderWindow & window);
	void animation(); 
	bool collision(FloatRect object);
	void restart();
	FloatRect getMeteoritBounds();

private:
	Sprite SpaceObject;
	Texture TextureObject;

	int xsp[5]{3,73,135,198,262};
	int ysp[6]{3,68,132,200,265,325};
	int ix, iy = 0;
	int st = 0;

};

