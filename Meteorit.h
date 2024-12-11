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
	virtual void restart();
	const FloatRect getMeteoritBounds();
	bool newborn;

	Vector2f getLastBonus()
	{
		return LastBonus;
	}
protected:
	Sprite SpaceObject;
	Texture TextureObject;
	Vector2f LastBonus;

private:
	
	int xsp[5]{3,73,135,198,262};
	int ysp[6]{3,68,132,200,265,325};
	int ix, iy = 0;
	int st = 0;

};

