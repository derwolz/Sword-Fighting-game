#include "SpriteSheet.h"
#include<SFML\Graphics.hpp>
#include "TextureLoader.h"
using namespace sf;
SpriteSheet::SpriteSheet(Texture& texture, Vector2u cardSize) {
	Vector2u image_size = texture.getSize();
	m_image = &texture;
	for (int i = 0; i < (int)(image_size.y / cardSize.y); i++) {
		for (int j = 0; j < (int)(image_size.x / cardSize.x); j++) {
			IntRect ImageInfo(cardSize.x * j, cardSize.y * i, cardSize.x, cardSize.y);
			SpriteBoxes.push_back(ImageInfo);
		}
	}
}
Sprite* SpriteSheet::GetSprites() {
	Sprite* result = new Sprite[SpriteBoxes.size()];
	for (int i = 0; i < SpriteBoxes.size(); i++) {
		result[i].setTexture(m_image[0]);
		result[i].setTextureRect(SpriteBoxes[i]);
	}
	return result;
}
int SpriteSheet::numSprites() {
	return SpriteBoxes.size();
}