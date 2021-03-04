#pragma once
class Body_Part
{
private:

	
	const int MAX_ARMOR = 2;
	int m_armor;
	
public:
	enum Name {
		None,
		Head,
		lArm,
		rArm,
		lLeg,
		rLeg,
		Torso
	};
	Name name;
	void decArmor();
	void decArmor(int num);
	Body_Part::Name getPart();
	int getArmor();
	Body_Part();
	Body_Part(int id);
};

