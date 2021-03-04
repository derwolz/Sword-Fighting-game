  #include "Body_Part.h"

Body_Part::Body_Part() {
	m_armor = MAX_ARMOR;
}
void Body_Part::decArmor() {
	m_armor--;
}
void Body_Part::decArmor(int num) {
	m_armor -= num;
}
int Body_Part::getArmor() {
	return m_armor;
}
Body_Part::Name Body_Part::getPart() {
	return name;
}