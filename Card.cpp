#include "Card.h"
Card::Card(CardNames name) {
	m_name = name;
}
Card::reward Card::GetReward() {
	return m_token;
}
int Card::GetDamage() {
	return m_Damage;
}
Card::CardNames& Card::GetName() {
	return m_name;
}
int Card::GetHealth() {
	return m_Health;
}
int Card::GetAttackTokens() {
	return m_AttackToken;
}
int Card::GetReserveDefenseTokens() {
	return m_ReserveDefenseToken;
}
int Card::GetReserveAttackTokens() {
	return m_ReserveAttackToken;
}
int Card::GetDefenseTokens() {
	return m_DefenseToken;
}
void Card::SetPosition(sf::Vector2f pos) {
	sprite.setPosition(pos);
}

void Card::Destroy() {
}

vector<Body_Part::Name> Card::GetTarget() {
	return m_target;
}

vector<Body_Part::Name> Card::GetWeakness() {
	return m_weakness;
}
void Card::SetTarget(vector<Body_Part::Name>& part_list) {
	for (int i = 0; i < part_list.size(); i++) {
		m_target.push_back(part_list[i]);
	}
}
void Card::SetWeakness(vector<Body_Part::Name>& part_list) {
	for (int i = 0; i < part_list.size(); i++) {
		m_weakness.push_back(part_list[i]);
	}
}
void Card::SetATokens(int& amt) {
	m_AttackToken = amt;
}
void Card::SetDTokens(int& amt){
	m_DefenseToken = amt;
}
void Card::SetReservedATokens(int& amt){
	m_ReserveAttackToken = amt;
}
void Card::SetReservedDTokens(int& amt){
	m_ReserveDefenseToken = amt;
}
void Card::SetHealth(int& amt){
	m_Health = amt;
}
void Card::SetDamage(int& amt){
	m_Damage = amt;
}
void Card::SetType(Card::reward style) {
	m_token = style;
}
void Card::SetArmorDamage(int& amt) {

}
int Card::GetArmorDamage() {
	return m_armorDamage;
}
