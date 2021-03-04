#pragma once
#include "Card.h"
#include "SFML/Graphics.hpp"
#include "Weapon.h"
#include <map>
#include <vector>
using namespace sf;
using namespace std;
class Deck
{
private:

    //std::map<std::string, Card> AllCards;
    vector<Card> Contents;
    int deckSize;
    int currentSize;

public:
    void Reshuffle(vector<Card> discardPile);
    void Reshuffle();
    void SetContents(vector<Card> cards);
    vector<Card> GetContents();
    void Destroy();
    Card& DealCard();
    void Discard();
    
};

