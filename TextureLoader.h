#pragma once
#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H
#include <map>
#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;
using namespace std;
class TextureLoader
{
private:
	std::map<std::string, Texture> m_Textures;
	static TextureLoader* m_s_Instance;
	std::vector<sf::IntRect> m_arr;
public:
	TextureLoader();
	static Texture& GetTexture(string const& filename);
	
};
#endif
