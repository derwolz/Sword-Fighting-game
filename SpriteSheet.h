#pragma once
#include <string>
#include <SFML\graphics.hpp>
#include <vector>
using namespace std;
using namespace sf;
class SpriteSheet
{
private:
	Texture* m_image;
	vector<IntRect> SpriteBoxes;
public:
	SpriteSheet(Texture& texture, Vector2u cardSize);
	Sprite* GetSprites();
	int numSprites();
};

