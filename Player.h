#pragma once

#include "Body_Part.h"
#include "Weapon.h"
#include "Card.h"
#include "Deck.h"
#include "GameBoard.h"
#include <SFML/Graphics.hpp>

//#include "Deck.h"
#include <map>
#include <vector>
class Player
{
private:
	const Vector2i Resolution = Vector2i(1920, 1080);
	const int MAXLIMBS = 6;
	const int MAXHEALTH = 10;
	const int MAXHANDSIZE = 5;
	const int MAXPLAYINGHAND = 3;
	const int DEFAULTDAMAGE = 1;
	const int TOKENVECTORSIZE = 12;
	const int DAMAGE = 1;
	const int ARMORDAMAGE = 1;

	int MINATTACKTOKEN = 1;
	int MINDEFENSETOKEN = 1;

	const std::map<int, Body_Part::Name> partList{
		std::make_pair(0,Body_Part::rArm),
		std::make_pair(1,Body_Part::lArm),
		std::make_pair(2,Body_Part::rLeg),
		std::make_pair(3,Body_Part::lLeg),
		std::make_pair(4,Body_Part::Head),
		std::make_pair(5,Body_Part::Torso)
	};

	int m_defenseToken = 0;
	int m_attackToken = 0;
	int m_reserveDefenseToken = 0;
	int m_reserveAttackToken = 0;
	int m_health;
	int m_numAttacks;
	int m_damage;
	
	int m_dispos = 0;
	int m_armorDamage = 1;
	bool m_isDone;

	vector<Card> m_discard;
	vector<Card> m_hand;
	Deck m_deck;
	vector<Card> m_playedCards;
	vector<Sprite> m_ATokens;
	vector<Sprite> m_DTokens;
	

public:
	Player();
	Player(Deck deck);
	Body_Part* m_body = nullptr;
	bool m_successfulAttack;
	Body_Part* GenerateBody();
	vector<Card>& GetHand();

	void PrintParts();
	void Destroy();
	void Attack(Player& player, Body_Part::Name name);
	
	void AddToken(Card::reward reward);
	void ResetToken();
	void SetDeck(Deck deck);
	void DiscardPlay(int card);
	void AddAttackTokens(int amt);
	void AddReserveAttackTokens(int amt);
	void AddDefenseTokens(int amt);
	void AddReserveDefenseTokens(int amt);
	void ShuffleDeck();
	void DrawCard();
	void DiscardCard(int card);
	void PlayCard(int i);
	void isDone(bool check);
	void AddHealth(int amt);
	void AddDamage(int amt);
	void EnsureOneStance();
	void Draw(sf::RenderWindow& window);
	void SetTokenTex(sf::Texture& ATokenTex, sf::Texture& DTokenTex);
	void AddArmorDamage(int amt);
	void Reset();
	

	int GetArmorDamage();
	int GetMaxPlayHandSize();
	int GetAttackTokens();
	int GetDefenseTokens();
	int GetReserveDefenseTokens();
	int GetReserveAttackTokens();
	int GetHealth();
	int GetAttacks();
	int GetDamage();
	int GetHandSize();
	int GetMaxHandSize();


	bool GetIsDone();

	vector<Card>& GetFieldCards();
};

