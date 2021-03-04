#pragma once

class Weapon
{
private:
public:
	Weapon();
	
	enum WeaponType {
		longSword,
		armingSword,
		mace,
		spear
	};
	Weapon(WeaponType);
	int damage;
	int attackToken;
	int defenseToken;
	//void WeaponAbility(Player& player);
	//void LongswordAbility(Player& player);
	//void ArmingswordAbility(Player& player);
	//void MaceAbility(Player& player);
	//void SpearAbility(Player& player);
};

