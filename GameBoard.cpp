#include "GameBoard.h"
GameBoard::GameBoard() {
	
}
void GameBoard::Reset() {

}

void GameBoard::Draw(sf::RenderWindow& window) {
	//window.draw(m_sprite);
	for (int i = 0; i < m_SpriteTokens.size(); i++)
	{
		window.draw(m_SpriteTokens[i]);
	}
	for (int i = 0; i < m_EnemySpriteTargets.size(); i++) {
		window.draw(m_EnemySpriteTargets[i]);
	}
	for (int i = 0; i < m_MySpriteTargets.size(); i++) {
		window.draw(m_MySpriteTargets[i]);
	}
	std::map<Body_Part::Name, int>::iterator it = TokenCount.begin();
	while (it != TokenCount.end()) {
		for (int i = 0; i < it->second; i++) {
			window.draw(m_Tokens[i]);
		}
	}
}

void GameBoard::SetArmorPosition(Body_Part::Name part, int amt, bool isEnemy) {
	bool horizontalCheck = isPieceTravelHorizontal.find(part)->second;
	if (isEnemy) {
		Vector2f& valuePair = EnemyBodyPartPositionMap.find(part)->second;
		valuePair = Vector2f(valuePair.x + m_spriteDims.x * amt * horizontalCheck, valuePair.y + m_spriteDims.y * amt * !horizontalCheck);
	}
	else {
		Vector2f& valuePair = MyBodyPartPositionMap.find(part)->second;
		valuePair = Vector2f(valuePair.x + m_spriteDims.x * amt * horizontalCheck, valuePair.y + m_spriteDims.y * amt * !horizontalCheck);
	}
}
void GameBoard::SetTargetPosition(Body_Part::Name part, bool isEnemy) {

}
void GameBoard::SetHealth(int amt, bool isEnemy) {
	m_MyHealthBar = Vector2f(HEALTHBARSTART.x * amt + HEALTHBARSTART.x, HEALTHBARSTART.y - isEnemy * 600);
}
Vector2f GameBoard::GetPartPostion(Body_Part::Name part, bool isEnemy) {
	if (isEnemy) {
		return EnemyBodyPartPositionMap.find(part)->second;
	}
	else {
		return MyBodyPartPositionMap.find(part)->second;
	}
}
Sprite& GameBoard::GetSprite() {
	return m_sprite;
}
void GameBoard::SetTargetSprite(SpriteSheet Sprites) {
	for (int i = 0; i < Sprites.numSprites(); i++) {
		Sprites.GetSprites()[i].setOrigin(Sprites.GetSprites()[i].getTexture()->getSize().x / 2, Sprites.GetSprites()[i].getTexture()->getSize().y / 2);
		m_EnemySpriteTargets.push_back(Sprites.GetSprites()[i]);
		m_EnemySpriteTargets[i].setScale(Vector2f(.1f, .1f));
		m_EnemySpriteTargets[i].setPosition(m_sprite.getPosition() +  m_EnemyPositions[i]);
		m_MySpriteTargets.push_back(Sprites.GetSprites()[i]);
		m_MySpriteTargets[i].setScale(Vector2f(.1f, .1f));
		
		m_MySpriteTargets[i].setPosition(m_sprite.getPosition() +  m_MyPositions[i]);
	}
}
vector<Sprite> GameBoard::GetPlayerPartSprites() {
	return m_MySpriteTargets;
}
vector<Sprite> GameBoard::GetEnemyPartSprites() {
	return m_EnemySpriteTargets;
}
void GameBoard::AddToken(Body_Part::Name name,int isEnemy) {
	Vector2f& temp = MyBodyPartPositionMap.find(name)->second;
	if (isEnemy == 0) {
		m_Tokens.push_back(Sprite(aTokenTex));		
	}
	else {
		temp = MyBodyPartPositionMap.find(name)->second;
		m_Tokens.push_back(Sprite(dTokenTex));
	}
	TokenCount.find(name)->second += 1;
	m_Tokens[m_Tokens.size() - 1].setPosition(temp.x + m_spriteDims.x * TokenCount.find(name)->second, temp.y);
}

int GameBoard::ReturnToken(Body_Part::Name name) {
	int temp = TokenCount.find(name)->second;
	ClearToken(name);
		return temp;
}
void GameBoard::ClearToken(Body_Part::Name name) {
	TokenCount.find(name)->second = 0;
}
void GameBoard::ClearAllTokens() {
	for (int i = 0; i < ALLPARTS.size(); i++) {
		ClearToken(ALLPARTS[i]);
	}
}
void GameBoard::SetTokenTextures(sf::Texture& tex1, sf::Texture& tex2) {
	aTokenTex = tex1;
	dTokenTex = tex2;
}