#include "GameObject.h"
#include "Game.h"

bool GameObject::rectIntersects(float x1, float y1, int w1, int h1, float x2, float y2, int w2, int h2)
{
	if (x1 >= x2 + w2 || x2 >= x1 + w1 || y1 >= y2 + h2 || y2 >= y1 + h1)
	{
		return false;
	}
	else
	{
		return true;
	}
}

GameObject::GameObject(Game* game, float x, float y, int width, int height) : x(x), y(y), width(width), height(height), game(game)
{
	renderer = game->renderer;
}

bool GameObject::intersects(GameObject* gameObject)
{
	return rectIntersects(x, y, width, height, gameObject->x, gameObject->y, gameObject->width, gameObject->height);
}

bool GameObject::intersects(float x, float y, int width, int height)
{
	return rectIntersects(this->x, this->y, this->width, this->height, x, y, width, height);
}