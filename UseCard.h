#pragma once
#include "Player.h"
#include "Card.h"


static class UseCard
{
private:
	static	 void OtherReward(Card& card, Player& player);
	static	 void TokenReward(Card& card, Player& player);
	static	 void PointReward(Card& card, Player& player);
	
public:
	UseCard();
	static	void Use(Card& card, Player& player);
	
	
	

	
	



};

