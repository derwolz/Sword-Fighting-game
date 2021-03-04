#pragma once
#include <vector>
#include <string>
#include "Card.h"
#include <SFML/Graphics.hpp>
#include "SpriteSheet.h"
#include <map>
using namespace sf;
using namespace std;
class DeckLoader
{
private:
    
    const int DECKTYPES = 4;
    const Vector2f SCALE = Vector2f(.25f, .25f);
    
    vector<vector<Card>> m_decks;
    
    Sprite* AllCardSprites;
    /*vector<Card::Style> armingSwordtypes{ 
        Card::Style::strike, Card::Style::strike, 
        Card::Style::strike, Card::Style::strike, 
        Card::Style::strike, Card::Style::stance, 
        Card::Style::action, Card::Style::counter,
        Card::Style::counter, Card::Style::counter,
        Card::Style::action, Card::Style::action, 
        Card::Style::stance, Card::Style::stance, 
        Card::Style::stance, Card::Style::action,
        Card::Style::stance,  Card::Style::action };*/

    vector<Card::Style> LongSwordtypes{ 
        Card::Style::strike,    Card::Style::strike, 
        Card::Style::strike,    Card::Style::strike,
        Card::Style::strike,    Card::Style::stance,
        Card::Style::action,    Card::Style::counter,
        Card::Style::counter,   Card::Style::counter,
        Card::Style::action,    Card::Style::action,
        Card::Style::stance,    Card::Style::stance,
        Card::Style::stance,    Card::Style::action,
        Card::Style::stance,    Card::Style::action };

    vector<Card::CardNames> mappedLSword{
        Card::CardNames::Zwerchhau,   Card::CardNames::Zornhau,     //2
        Card::CardNames::Krumphau,    Card::CardNames::Schielhau,
        Card::CardNames::Schietelhau, Card::CardNames::Ochs,        //6
        Card::CardNames::Nachshlag,   Card::CardNames::Transition,
        Card::CardNames::Feint,       Card::CardNames::Void,        //10
        Card::CardNames::Mordschlag,  Card::CardNames::Tempo,
        Card::CardNames::Pflug,       Card::CardNames::vom_Tag,     //14
        Card::CardNames::Alber,       Card::CardNames::End_Him_Rightly,
        Card::CardNames::Nebenhut,    Card::CardNames::Tempo };     //18
    vector<int> Damage{
    0,0,    0,0,
    0,1,    0,0,
    0,0,    0,0,
    1,1,    0,0,
    1,0
    };
    vector<vector<int>> LswordNums{
    vector<int> {0,0,0, 0,0,0,  0,0,0,  0,0,0,  0,0,0,  0,0,0}, // Health
    vector<int> {0,0,0, 0,0,1,  0,0,0,  0,0,0,  1,1,0,  0,1,0}, //Damage
    vector<int> {0,0,0, 0,0,0,  1,0,0,  0,0,0,  0,0,0,  1,0,0}, // AttackToken
    vector<int> {0,0,0, 0,0,0,  0,0,0,  0,0,0,  0,0,0,  -1,0,0}, // DefenseToken
    vector<int> {1,1,0, 1,1,0,  0,0,0,  0,0,0,  0,0,0,  0,0,0}, // ReserveAttackToken
    vector<int> {0,0,1, 0,0,0,  0,0,0,  0,0,0,  0,0,0,  0,0,0},  // ReserveDefenseToken
    vector<int> {0,0,0, 0,0,0,  0,0,0,  0,0,0,  0,0,0,  0,0,0}  //ArmorDamage
    };
    vector<vector<Body_Part::Name>> lSwordTargets{
        vector<Body_Part::Name> {Body_Part::Name::lLeg, Body_Part::Name::rLeg, Body_Part::Name::rArm, Body_Part::Name::lArm},
        vector<Body_Part::Name> {Body_Part::Name::Head, Body_Part::Name::Torso},
        vector<Body_Part::Name> {Body_Part::Name::Torso, Body_Part::Name::rArm, Body_Part::Name::lArm},
        vector<Body_Part::Name> {Body_Part::Name::Torso, Body_Part::Name::rArm, Body_Part::Name::lArm},
        vector<Body_Part::Name> {Body_Part::Name::Torso, Body_Part::Name::rLeg, Body_Part::Name::lLeg},
        vector<Body_Part::Name> {Body_Part::Name::Head}, vector<Body_Part::Name> {Body_Part::Name::None},
        vector<Body_Part::Name> {Body_Part::Name::None}, vector<Body_Part::Name> {Body_Part::Name::None},
        vector<Body_Part::Name> {Body_Part::Name::None}, vector<Body_Part::Name> {Body_Part::Name::None},
        vector<Body_Part::Name> {Body_Part::Name::None},
        vector<Body_Part::Name> {Body_Part::Name::lLeg, Body_Part::Name::rLeg},
        vector<Body_Part::Name> {Body_Part::Name::Torso}, vector<Body_Part::Name> {Body_Part::Name::None},
        vector<Body_Part::Name> {Body_Part::Name::None}, vector<Body_Part::Name> {Body_Part::Name::lArm, Body_Part::Name::rArm},
        vector<Body_Part::Name> {Body_Part::Name::None}
    };
    vector<vector<Body_Part::Name>> lSwordWeaknesses{
        vector<Body_Part::Name> {Body_Part::Name::Torso, Body_Part::Name::Head},
        vector<Body_Part::Name> {Body_Part::Name::rArm, Body_Part::Name::lArm, Body_Part::Name::Head},
        vector<Body_Part::Name> {Body_Part::Name::Torso, Body_Part::Name::lArm, Body_Part::Name::rArm},
        vector<Body_Part::Name> {Body_Part::Name::Torso, Body_Part::Name::lArm, Body_Part::Name::rArm},
        vector<Body_Part::Name> {Body_Part::Name::Torso, Body_Part::Name::lLeg, Body_Part::Name::rLeg},
        vector<Body_Part::Name> {Body_Part::Name::None},vector<Body_Part::Name> {Body_Part::Name::None},
        vector<Body_Part::Name> {Body_Part::Name::None},vector<Body_Part::Name> {Body_Part::Name::None},
        vector<Body_Part::Name> {Body_Part::Name::None},vector<Body_Part::Name> {Body_Part::Name::None},
        vector<Body_Part::Name> {Body_Part::Name::None},vector<Body_Part::Name> {Body_Part::Name::None},
        vector<Body_Part::Name> {Body_Part::Name::None},vector<Body_Part::Name> {Body_Part::Name::None},
        vector<Body_Part::Name> {Body_Part::Name::None},vector<Body_Part::Name> {Body_Part::Name::None},
        vector<Body_Part::Name> {Body_Part::Name::None}
    };
    vector<Card::reward> lSwordRewards { 
    Card::reward::Token, Card::reward::Token,
    Card::reward::Token, Card::reward::Token,
    Card::reward::Token, Card::reward::Point,
    Card::reward::None, Card::reward::None,
    Card::reward::None, Card::reward::None,
    Card::reward::Point, Card::reward::None,
    Card::reward::Point, Card::reward::Point,
    Card::reward::None, Card::reward::Point, 
    Card::reward::Point, Card::reward::None, };

    vector<vector<vector<int>>> WeaponNums{LswordNums};
    vector<vector<vector<Body_Part::Name>>> Targets{ lSwordTargets };
    vector<vector<vector<Body_Part::Name>>> Weaknesses{ lSwordWeaknesses };
    vector < vector<Card::reward>> CardRewards{ lSwordRewards };

    /*vector<string> longswordDeckCardNames{
        "Zwerchhau",        "Zornhau",
        "Krumphau",        "Schielhau",
        "Schietelhau",        "Ochs",
        "Nachshlag",        "Transition",
        "Feint",        "Void",
        "Mordschlag",        "Tempo",
        "Pflug",        "vom Tag",
        "Alber",        "End Him Rightly",
        "Nebenhut",        "Tempo"
    };*/

        

    /*vector<Card::Style> Macetypes{ Card::Style::strike, Card::Style::strike, Card::Style::strike, Card::Style::strike, Card::Style::strike, Card::Style::stance, Card::Style::action,
    Card::Style::counter, Card::Style::counter, Card::Style::counter, Card::Style::action, Card::Style::action, Card::Style::stance, Card::Style::stance, Card::Style::stance, Card::Style::action,
     Card::Style::stance,  Card::Style::action, };*/
    // vector<Card::Style> Speartypes{ Card::Style::strike, Card::Style::strike, Card::Style::strike, Card::Style::strike, Card::Style::strike, Card::Style::stance, Card::Style::action,
    // Card::Style::counter, Card::Style::counter, Card::Style::counter, Card::Style::action, Card::Style::action, Card::Style::stance, Card::Style::stance, Card::Style::stance, Card::Style::action,
    // Card::Style::stance,  Card::Style::action, }; Speartypes Macetypes,

    vector<vector<Card::Style>> cardTypes{LongSwordtypes};

    //vector<string> armingSwordDeckCardNames{ "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", };
    /*vector<string> SpearDeckCardNames{ "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", };
    vector<string> HammerDeckCardNames{ "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", };*/\

    vector<vector<Card::CardNames>> DeckNames{
        mappedLSword
        /*SpearDeckCardNames,
        HammerDeckCardNames*/
    };

public:
    DeckLoader(std::vector<SpriteSheet> sheets);
    vector<Card> GetDeck(int WeaponType);
};

