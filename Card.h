#pragma once
#include "Body_Part.h"
#include <sstream>
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;
class Card
{

public:
	enum class CardNames {
		Zwerchhau, Zornhau,
		Krumphau, Schielhau,
		Schietelhau, Ochs,
		Nachshlag, Transition,
		Feint, Void,
		Mordschlag, Tempo,
		Pflug, vom_Tag,
		Alber, End_Him_Rightly,
		Nebenhut
	};
	
	Card(CardNames name);
	enum class Style {
		None,
		strike,
		counter,
		stance,
		action
	};
	enum class reward {
		None,
		Token,
		Point,

	};
	Style m_style;

	Card::reward m_token;
	sf::Sprite sprite;
	sf::Vector2f position;
	void SetPosition(sf::Vector2f pos);
	vector<Body_Part::Name> GetTarget();
	vector<Body_Part::Name> GetWeakness();
	
	void SetTarget(vector<Body_Part::Name>& part_list);
	void SetWeakness(vector<Body_Part::Name>& part_list);
	
	reward GetReward();
	CardNames& GetName();
	void ChangeActive();
	bool GetActive();
	void HideCard();
	void Destroy();
	
	void SetATokens(int& amt);
	void SetDTokens(int& amt);
	void SetReservedATokens(int& amt);
	void SetReservedDTokens(int& amt);
	void SetHealth(int& amt);
	void SetDamage(int& amt);
	void SetType(Card::reward style);

	int GetAttackTokens();
	int GetDefenseTokens();
	int GetReserveAttackTokens();
	int GetReserveDefenseTokens();
	int GetHealth();
	int GetDamage();
	void SetArmorDamage(int& amt);
	int GetArmorDamage();
private:
	int m_armorDamage;
	const int defaultDamage = 0;
	int damage;
	bool isActive = false;
	CardNames m_name;

	
	vector<Body_Part::Name> m_target;
	vector<Body_Part::Name> m_weakness;
	int m_Damage = 0;
	int m_AttackToken = 0;
	int m_DefenseToken = 0;
	int m_ReserveAttackToken = 0;
	int m_ReserveDefenseToken = 0;
	int m_Health = 0;



};

