#include "Player.h"
#include "Body_Part.h"
#include <iostream>
#include <math.h>

Player::Player() {

	m_damage = DEFAULTDAMAGE;
	m_health = MAXHEALTH;
	m_body = GenerateBody();
	m_ATokens.resize(TOKENVECTORSIZE);
	m_DTokens.resize(TOKENVECTORSIZE);
	MINDEFENSETOKEN = 1;
	MINATTACKTOKEN = 1;
	m_attackToken = 12;
	m_defenseToken = 12;
	for (int i = 0; i < m_ATokens.size(); i++) {
		
			m_ATokens[i].setPosition(sf::Vector2f((i % (TOKENVECTORSIZE / 4)) * 50 + 50, 
				std::floor(i / (TOKENVECTORSIZE / 4)) * 50));
			m_DTokens[i].setPosition(sf::Vector2f((i % (TOKENVECTORSIZE / 4)) * 50 + 50 * (TOKENVECTORSIZE / 3), 
				std::floor(i / (TOKENVECTORSIZE / 4)) * 50));
		}
	
	m_successfulAttack = false;
	//WeaponSetup(weapon);
}

Body_Part* Player::GenerateBody() {
	m_body = new Body_Part[MAXLIMBS];
	for (auto part = partList.begin(); part != partList.end(); ++part) {
		m_body[part->first].name = part->second;
	}
	return m_body;
}

void Player::Destroy() {
	m_deck.Destroy();
	delete m_body;
	//delete m_deck;
	m_body = nullptr;
	//m_deck = nullptr;
}

void Player::Attack(Player& player, Body_Part::Name name) {
	for (int i = 0; i < MAXLIMBS; i++) {
		if (player.m_body[i].name == name) {
			int healthDamage = player.m_body[i].getArmor() - player.m_damage;
			if (healthDamage > 0)
				player.m_health -= healthDamage;
			player.m_body[i].decArmor(m_armorDamage);
		}
	}
}

void Player::PrintParts() {
	for (int i = 0; i < MAXLIMBS - 1; i++) {
		switch (m_body[i].name) {
		case Body_Part::Head:
			std::cout << "Head";
		case Body_Part::rArm:
			std::cout << "Right Arm";
		case Body_Part::lArm:
			std::cout << "Left Arm";
		case Body_Part::rLeg:
			std::cout << "Right Leg";
		case Body_Part::lLeg:
			std::cout << "Left Leg";
		case Body_Part::Torso:
			std::cout << "Torso";
		}
		std::cout << std::endl;
	}
}

int Player::GetAttackTokens() {
	return m_attackToken;
}

int Player::GetDefenseTokens() {
	return m_defenseToken;
}

int Player::GetDamage() {
	return m_damage;
}

int Player::GetReserveDefenseTokens() {
	return m_reserveDefenseToken;
}

int Player::GetReserveAttackTokens() {
	return m_reserveAttackToken;
}

void Player::AddAttackTokens(int amt) {
	m_attackToken += amt;
}

void Player::AddDefenseTokens(int amt) {
	m_defenseToken += amt;
}

void Player::AddReserveAttackTokens(int amt) {
	m_reserveAttackToken += amt;
}

void Player::AddReserveDefenseTokens(int amt) {
	m_reserveDefenseToken += amt;
}

void Player::ResetToken() {
	m_defenseToken = MINDEFENSETOKEN + m_reserveDefenseToken;
	m_attackToken = MINATTACKTOKEN + m_reserveAttackToken;
	m_reserveAttackToken = 0;
	m_reserveDefenseToken = 0;
	m_damage = DAMAGE;
	m_armorDamage = ARMORDAMAGE;

}

int Player::GetHealth() {
	return m_health;
}

vector<Card>& Player::GetHand() {
	return m_hand;
}

void Player::DiscardCard(int card) {
	m_discard.push_back(m_hand[card]);
	vector<Card> temp;
	for (int j = 0; j < m_hand.size(); j++) {
		if (card != j) {
			temp.push_back(m_hand[j]);
		}
	}
	m_hand.clear();
	for (int i = 0; i < temp.size(); i++) {
		m_hand.push_back(temp[i]);
	}
	temp.clear();
	
}

void Player::DrawCard() {
	m_hand.push_back(m_deck.DealCard());
	m_deck.Discard();
}

int Player::GetHandSize() {
	return m_hand.size();
}

void Player::SetDeck(Deck deck) {
	m_deck.SetContents(deck.GetContents());
}

int Player::GetMaxHandSize() {
	return MAXHANDSIZE;
}

void Player::PlayCard(int i) {
	//Physically places Cards
	m_playedCards.push_back(m_hand[i]);
	for (int j = 0; j < m_playedCards.size(); j++) {
		m_playedCards[j].sprite.setPosition(Vector2f(200 + j *200, Resolution.y * 1 / 5));
	}
	EnsureOneStance();
}

int Player::GetMaxPlayHandSize() {
	return MAXPLAYINGHAND;
}

void Player::ShuffleDeck() {
	//sends discard back to deck and reshuffles
	m_deck.Reshuffle(m_discard);
	m_discard.clear();
}

void Player::isDone(bool check) {
	m_isDone = check;
}

bool Player::GetIsDone() {
	return m_isDone;
}

void Player::DiscardPlay(int card) {
	vector<Card> temp;
	for (int j = 0; j < m_playedCards.size(); j++) {
		if (card != j) {
			temp.push_back(m_playedCards[j]);
		}
	}
	m_playedCards.clear();
	for (int i = 0; i < temp.size(); i++) {
		m_playedCards.push_back(temp[i]);
	}
	temp.clear();

}

vector<Card>& Player::GetFieldCards() {
	return m_playedCards;
}

void Player::AddHealth(int amt) {
	m_health += amt;
}

void Player::AddDamage(int amt) {
	m_damage += amt;
}

void Player::EnsureOneStance() {
	//Leaves one stance in FIFO
	std::vector<int> _nonStance;
	int _lastStance = -1;
	for (int i = 0; i < GetFieldCards().size(); i++) {
		if (GetFieldCards()[i].m_style != Card::Style::stance) {
			_nonStance.push_back(i);
		}
		else _lastStance = i;
	}
	std::vector<Card> _temp;
	for (int i = 0; i < _nonStance.size(); i++) {
		_temp.push_back(GetFieldCards()[_nonStance[i]]);
	}
	if (_lastStance >-1)
		_temp.push_back(GetFieldCards()[_lastStance]);
	GetFieldCards().clear();
	for (int i = 0; i < _temp.size(); i++) {
		GetFieldCards().push_back(_temp[i]);
	}
	_temp.clear();
}
void Player::SetTokenTex(sf::Texture& ATokenTex, sf::Texture& DTokenTex) {
	for (int i = 0; i < TOKENVECTORSIZE; i++) {
		m_ATokens[i].setTexture(ATokenTex);
		m_DTokens[i].setTexture(DTokenTex);
	}
}
void Player::Draw(sf::RenderWindow& window) {
	for (int i = 0; i < GetFieldCards().size(); i++) {
		window.draw(GetFieldCards()[i].sprite);
	}
	for (int i = 0; i < m_hand.size(); i++) {
		window.draw(m_hand[i].sprite);
	}
	for (int i = 0; i < m_attackToken; i++) {
		window.draw(m_ATokens[i]);
	}
	for (int i = 0; i < m_defenseToken; i++) {
		window.draw(m_DTokens[i]);
	}
}
void Player::AddArmorDamage(int amt) {
	m_armorDamage += amt;
}
int Player::GetArmorDamage() {
	return m_armorDamage;
}
void Player::Reset() {
	m_health = MAXHEALTH;
	ResetToken();
	ResetToken(); // second time will clear out reserve tokens;

}