#include "Deck.h"
#include "Deckloader.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>

void Deck::SetContents(vector<Card> cards) {
	int size = cards.size();
	for (int m = 0; m < size; m++) {
		Contents.push_back(cards[m]);
	}
	Reshuffle();
}

void Deck::Reshuffle() {
	// Shuffles deck without adding from discard pile
	srand(time(NULL));
	vector<vector<Card>> temp;
	temp.resize(4);
	for (int times = 0; times < rand() % 20; times++) {
		for (int i = 0; i < Contents.size(); i++) {
			int num = rand() % 4;
			temp[num].push_back(Contents[Contents.size() - 1 - i]);
		}
		Contents.clear();
		for (int i = 0; i < temp.size(); i++) {
			for (int j = 0; j < temp[i].size(); j++) {
				Contents.push_back(temp[i][j]);
			}
			temp[i].clear();
		}
	}	
}

void Deck::Reshuffle(vector<Card> discardPile) {
	// Adds Cards from Discard, and Reshuffles Deck
	for (int i = 0; i < discardPile.size(); i++) {
		Contents.push_back(discardPile[i]);
	}
	Reshuffle();
	
}

void Deck::Discard() {
	//Disposes of Card Discard held by player
	Contents.pop_back();
}

Card& Deck::DealCard() {
	// returns card to playerhand
	if (Contents.size() > 0) {
		return Contents[Contents.size() - 1];
	}
	else {
		std::cout << "Deck size is less than 1 \n";
	}
}

std::vector<Card> Deck::GetContents() {
	return Contents;
}

void Deck::Destroy() {
	//disposes of any pointers used
	for (int i = 0; i < Contents.size(); i++) {
		Contents[i].Destroy();
	}
}