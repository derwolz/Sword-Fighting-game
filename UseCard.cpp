#include "UseCard.h"
UseCard::UseCard(){
}
void UseCard::Use(Card& card, Player& player) {
	auto reward = card.GetReward();
	if (reward == Card::reward::None)
		OtherReward(card, player);
	if (reward == Card::reward::Point)
		PointReward(card, player);
	if (reward == Card::reward::Token)
		TokenReward(card, player);
}
void UseCard::TokenReward(Card& card, Player& player) {
	player.AddAttackTokens(card.GetAttackTokens());
	player.AddDefenseTokens(card.GetDefenseTokens());
	player.AddReserveAttackTokens(card.GetReserveAttackTokens());
	player.AddReserveDefenseTokens(card.GetReserveDefenseTokens());
	return;
}
void UseCard::PointReward(Card& card, Player& player) {
	player.AddHealth(card.GetHealth());
	player.AddDamage(card.GetDamage());
	player.AddArmorDamage(card.GetArmorDamage());
}
void UseCard::OtherReward(Card& card, Player& player) {

}
