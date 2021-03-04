#pragma once
#include <SFML\Graphics.hpp>
#include "Body_Part.h"
#include "SpriteSheet.h"
#include <vector>
#include <map>
using namespace std;
using namespace sf;
class GameBoard
{
	
private:
	const Vector2f HEALTHBARSTART = Vector2f(75, 432);
	const vector<Body_Part::Name> ALLPARTS{
		Body_Part::Name::Head,Body_Part::Name::lArm,
		Body_Part::Name::rArm, Body_Part::Name::lLeg,
		Body_Part::Name::rLeg, Body_Part::Name::Torso, };
	Texture& aTokenTex;
	Texture& dTokenTex;
	const vector<Vector2f> MYARMORPOSITIONSSTART{
		Vector2f(315,45), Vector2f(25,140), 
		Vector2f(333,140), Vector2f(45,365), 
		Vector2f(320,365), Vector2f(55,45) };
	const vector<Vector2f> ENEMYPOSITIONSSTART{ 
		Vector2f(507,113), Vector2f(428,142),
		Vector2f(590,142), Vector2f(460,305),
		Vector2f(550,305), Vector2f(507,230) };
	const int TargetTokens = MYARMORPOSITIONSSTART.size() + ENEMYPOSITIONSSTART.size() + 1;
	Sprite m_sprite;
	vector<Sprite> m_SpriteTokens;
	vector<Sprite> m_Tokens;
	vector<Sprite> m_EnemySpriteTargets;
	vector<Sprite> m_MySpriteTargets;
	
	//these ones move
	vector<Vector2f> m_MyPositions{
		Vector2f(153,78), Vector2f(70,112), // head - lArm
		Vector2f(242,112), Vector2f(107,270) // rArm - lLeg
		, Vector2f(202,270), Vector2f(153,175) }; // rLeg - Torso
	Vector2f m_MyHealthBar;
	Vector2f m_EnemyHealthBar;
	vector<Vector2f> m_MyArmorPositions{
		MYARMORPOSITIONSSTART[0],
		MYARMORPOSITIONSSTART[1],
		MYARMORPOSITIONSSTART[2],
		MYARMORPOSITIONSSTART[3],
		MYARMORPOSITIONSSTART[4],
		MYARMORPOSITIONSSTART[5],
	};
	vector<Vector2f> m_EnemyPositions{
		ENEMYPOSITIONSSTART[0],
		ENEMYPOSITIONSSTART[1],
		ENEMYPOSITIONSSTART[2],
		ENEMYPOSITIONSSTART[3],
		ENEMYPOSITIONSSTART[4],
		ENEMYPOSITIONSSTART[5],
	};
	map<Body_Part::Name, Vector2f> MyBodyPartPositionMap{
		pair<Body_Part::Name,Vector2f>(Body_Part::Name::Head, m_MyPositions[0]),
		pair<Body_Part::Name,Vector2f>(Body_Part::Name::lArm, m_MyPositions[1]),
		pair<Body_Part::Name,Vector2f>(Body_Part::Name::rArm, m_MyPositions[2]),
		pair<Body_Part::Name,Vector2f>(Body_Part::Name::lLeg, m_MyPositions[3]),
		pair<Body_Part::Name,Vector2f>(Body_Part::Name::rLeg, m_MyPositions[4]),
		pair<Body_Part::Name,Vector2f>(Body_Part::Name::Torso, m_MyPositions[5]) 
	};
	map<Body_Part::Name, Vector2f> EnemyBodyPartPositionMap{
		pair<Body_Part::Name,Vector2f>(Body_Part::Name::Head, m_EnemyPositions[0]),
		pair<Body_Part::Name,Vector2f>(Body_Part::Name::lArm, m_EnemyPositions[1]),
		pair<Body_Part::Name,Vector2f>(Body_Part::Name::rArm, m_EnemyPositions[2]),
		pair<Body_Part::Name,Vector2f>(Body_Part::Name::lLeg, m_EnemyPositions[3]),
		pair<Body_Part::Name,Vector2f>(Body_Part::Name::rLeg, m_EnemyPositions[4]),
		pair<Body_Part::Name,Vector2f>(Body_Part::Name::Torso, m_EnemyPositions[5]) 
	};
	map<Body_Part::Name, bool> isPieceTravelHorizontal{
	pair<Body_Part::Name, bool>(Body_Part::Name::Head, true),
	pair<Body_Part::Name, bool>(Body_Part::Name::lArm, false),
	pair<Body_Part::Name, bool>(Body_Part::Name::rArm, false),
	pair<Body_Part::Name, bool>(Body_Part::Name::lLeg, true),
	pair<Body_Part::Name, bool>(Body_Part::Name::rLeg, true),
	pair<Body_Part::Name, bool>(Body_Part::Name::Torso, true)
	
	};
	map<Body_Part::Name, int> TokenCount{
	pair<Body_Part::Name, int>(Body_Part::Name::Head, 0),
	pair<Body_Part::Name, int>(Body_Part::Name::lArm, 0),
	pair<Body_Part::Name, int>(Body_Part::Name::rArm, 0),
	pair<Body_Part::Name, int>(Body_Part::Name::lLeg, 0),
	pair<Body_Part::Name, int>(Body_Part::Name::rLeg, 0),
	pair<Body_Part::Name, int>(Body_Part::Name::Torso, 0),
	};
	Vector2f m_spriteDims;
public:	
	GameBoard();
	Sprite& GetSprite();
	Vector2f GetPartPostion(Body_Part::Name part, bool isEnemy = false);
	void SetTargetPosition(Body_Part::Name part, bool isEnemy = false);
	void SetArmorPosition(Body_Part::Name part, int amt, bool isEnemy = false);
	void SetTargetSprite(SpriteSheet Sprites);
	void SetHealth(int amt, bool isEnemy = false);
	void AddToken(Body_Part::Name name, int isEnemy);
	vector<Sprite> GetPlayerPartSprites();
	vector<Sprite> GetEnemyPartSprites();
	void Reset();
	void Draw(sf::RenderWindow& window);
	int ReturnToken(Body_Part::Name name);
	void ClearToken(Body_Part::Name name);
	void ClearAllTokens();
	void SetTokenTextures(sf::Texture& tex1, sf::Texture& tex2);
	
};

