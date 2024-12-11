#include "Meteorit.h"

Meteorit::Meteorit()
{
	TextureObject.loadFromFile("Image/asteroid.png");
	SpaceObject.setTexture(TextureObject);
	SpaceObject.setTextureRect(IntRect(262,325,55,50));
	restart();
}

Meteorit::~Meteorit()
{

}

void Meteorit::move(float& time)
{
	SpaceObject.move(static_cast<float>(-0.5*time),0);
	if (SpaceObject.getPosition().x < -60) restart();
}

void Meteorit::draw(RenderWindow & window)
{
	window.draw(SpaceObject);
}

void Meteorit::animation()
{
	if (st > 0)
	{
		SpaceObject.setTextureRect(IntRect(xsp[ix], ysp[iy], 50, 45));
		ix += st;
		if (ix>4) 
		{
			ix = 0;
			iy++;
			if (iy > 0) iy = 0;
		}
	}
}

bool Meteorit::collision(FloatRect object)
{
	if (SpaceObject.getGlobalBounds().intersects(object)) return true;
	return false;
}
void Meteorit::restart()
{
	float size = static_cast<float>((rand() % 13 + 5) / 10);
	float x = static_cast<float>(rand() % 1280+1280);
	float y = static_cast<float>(rand() % 540 + 130);

	SpaceObject.setPosition(Vector2f(x, y));
	SpaceObject.setScale(size, size);
	ix = rand() % 4;
	iy = rand() % 5;
	st = rand() % 2;
}

FloatRect Meteorit::getMeteoritBounds()
{
	return SpaceObject.getGlobalBounds();
}