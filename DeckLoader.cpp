
#include "DeckLoader.h"
#include "SpriteSheet.h"
#include <iostream>
DeckLoader::DeckLoader(std::vector<SpriteSheet> spriteSheet) {
	for (int i = 0; i < spriteSheet.size(); i++) {
		vector<Card> tempvector;
		for (int j = 0; j < spriteSheet[i].numSprites() ; j++) {
			//std::cout << DeckNames[i][j] << std::endl;
			Card temp(DeckNames[i][j]);
			temp.m_style = cardTypes[i][j];
			temp.sprite = spriteSheet[i].GetSprites()[j];
			temp.sprite.setScale(SCALE);
			
				temp.SetHealth(WeaponNums[i][0][j]);
				temp.SetDamage(WeaponNums[i][1][j]);
				temp.SetArmorDamage(WeaponNums[i][6][j]);
				temp.SetATokens(WeaponNums[i][2][j]);
				temp.SetDTokens(WeaponNums[i][3][j]);
				temp.SetReservedATokens(WeaponNums[i][4][j]);
				temp.SetReservedDTokens(WeaponNums[i][5][j]);
				temp.SetTarget(Targets[i][j]);
				temp.SetWeakness(Targets[i][j]);
				temp.SetType(CardRewards[i][j]);
				tempvector.push_back(temp);
		}
		m_decks.push_back(tempvector);
	}

}
vector<Card> DeckLoader::GetDeck(int weapon) {
	return m_decks[weapon];
}
