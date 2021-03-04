#include <SFML/Graphics.hpp>
#include "Body_Part.h"
#include "GameBoard.h"
#include "Weapon.h"
#include "Player.h"
#include "Card.h"
#include <iostream>
#include "SpriteSheet.h"
#include "TextureLoader.h"
#include "DeckLoader.h"
#include "Deck.h"
#include "UseCard.h"

int main()
{
    TextureLoader tex;
    UseCard User;
    /// <summary>.........................................................
    /// ......................Setup for game..............................
    /// ........................................................</summary>

    Vector2u CardSize(744, 1028);
    Vector2u ArmorSize(538, 538);
    const static Vector2i Resolution(1920, 1080);
    enum State {
        NONE,
        NEWGAME,
        GAMEOVER,
        PAUSED,
        PLAYING
    };
    enum class Turn {
        NONE = 2,
        PLAYER1 = 0,
        PLAYER2 = 1
    };
    Turn turn = Turn::NONE;
    enum class Phase {
        DrawPhase,
        SetUp,
        Posture,
        Attack,
        Resolve
    };
    Phase phase = Phase::DrawPhase;
    State gameState = State::PLAYING;
    const int maxParts = 5;

Player player1;
vector<SpriteSheet> deckSheets;
deckSheets.push_back(SpriteSheet(TextureLoader::GetTexture("sprites/longswordDeck.png"), CardSize));
Sprite ReshuffleButton(TextureLoader::GetTexture("sprites/reshuffle.png"));
ReshuffleButton.setOrigin(Vector2f(ReshuffleButton.getTexture()->getSize().x, ReshuffleButton.getTexture()->getSize().y));
ReshuffleButton.setPosition(Vector2f(Resolution.x - 100, Resolution.y / 2));
Sprite EndPhaseButton(TextureLoader::GetTexture("sprites/EndPhaseButton.png"));
EndPhaseButton.setOrigin(Vector2f(ReshuffleButton.getTexture()->getSize().x, ReshuffleButton.getTexture()->getSize().y));
EndPhaseButton.setPosition(Vector2f(300, Resolution.y / 2));
DeckLoader dLoader(deckSheets);
Deck deck;
deck.SetContents(dLoader.GetDeck(0));
player1.SetDeck(deck);

Texture& AtokenTex(TextureLoader::GetTexture("sprites/Attack_Token.png"));
Texture& DtokenTex(TextureLoader::GetTexture("sprites/Defense_Token.png"));

vector<Player> player;
player.push_back(player1);
for (int i = 0; i < player.size(); i++) {
    player[i].SetTokenTex(AtokenTex, DtokenTex);
}
GameBoard player1board;
player1board.GetSprite().setTexture(TextureLoader::GetTexture("sprites/GameBoard1.jpg"));

vector<GameBoard> boards;
boards.push_back(player1board);

for (int i = 0; i < boards.size(); i++) {
    //boards[i].GetSprite().setOrigin(boards[i].GetSprite().getTexture()->getSize().x / 2, boards[i].GetSprite().getTexture()->getSize().y / 2);
    boards[i].GetSprite().setPosition(Resolution.x / 2 - 150 - boards[i].GetSprite().getTexture()->getSize().x / 2, Resolution.y / 2 - 100 - boards[i].GetSprite().getTexture()->getSize().y / 2);
    boards[i].SetTargetSprite(SpriteSheet(TextureLoader::GetTexture("sprites/BodySpriteSheet.png"), ArmorSize));
}


Sprite Background(TextureLoader::GetTexture("sprites/bg.jpg"));
Background.setOrigin(0, 0);
Background.setPosition(0, 0);

sf::RenderWindow window(sf::VideoMode(Resolution.x, Resolution.y), "SFML works!");

//Loop start....................................................
//..............................................................
//..............................................................
while (window.isOpen())
{
    /// <summary>
    /// Handle Controls
    /// </summary>
    /// <returns></returns>
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed) {
            auto mous_pos = Mouse::getPosition(window);
            auto translated_pos = window.mapPixelToCoords(mous_pos);
            std::cout << "x: " << translated_pos.x << " y: " << translated_pos.y << endl;
            int playerOn = (int)turn;
            if (EndPhaseButton.getGlobalBounds().contains(translated_pos)) player[playerOn].isDone(true);
            if (ReshuffleButton.getGlobalBounds().contains(translated_pos)) phase = Phase::DrawPhase;
            for (int i = 0; i < player[playerOn].GetHand().size(); i++) {
                if (player[playerOn].GetHand()[i].sprite.getGlobalBounds().contains(translated_pos)) {

                    // Click events if in Setup
                    if (phase == Phase::SetUp) {

                        player[playerOn].DiscardCard(i);
                        if (player[playerOn].GetHand().size() == player[playerOn].GetMaxPlayHandSize()) {
                            if (turn == Turn::PLAYER1) turn = Turn::PLAYER2;
                            else turn = Turn::PLAYER1;
                        }
                    }
                    //Click events if in Posture
                    if (phase == Phase::Posture) {

                        if (player[playerOn].GetHand()[i].m_style != Card::Style::counter) {
                            player[playerOn].PlayCard(i);
                            player[playerOn].DiscardCard(i);
                        }

                    }
                    if (phase == Phase::Attack) {
                        for (int j = 0;j < boards.size(); j++) {
                            for (int k = 0; k < boards[j].GetEnemyPartSprites().size(); k++) {
                                if (boards[j].GetEnemyPartSprites()[k].getGlobalBounds().contains(translated_pos)) {
                                    if (player[playerOn].GetAttackTokens() > 0) {
                                        boards[j].AddToken(k,0);
                                    }
                                   /* else {
                                        player[playerOn].AddAttackTokens();
                                    }*/
                                }
                            }
                            for (int k = 0; k < boards[j].GetPlayerPartSprites().size(); k++) {
                                if (boards[j].GetPlayerPartSprites()[k].getGlobalBounds().contains(translated_pos)) {

                                }
                            }
                        }
                    }
                    if (phase == Phase::Resolve) {
                        if (player[playerOn].GetHand()[i].m_style == Card::Style::counter) {
                            player[playerOn].PlayCard(i);
                            player[playerOn].DiscardCard(i);
                        }
                    }
                }
            }
            if (phase == Phase::Attack) {
                
            }
            
        }
    }
    if (gameState == State::NEWGAME) {
        // player1.reset();
         //player2.e();


    }
    /*if (turn == Turn::NONE) {
        if (std::rand() < .5) {
            turn = Turn::PLAYER1;
        }
        else {
            turn = Turn::PLAYER2;
        }
    }*/
    if (gameState == State::PLAYING) {
        /// <summary>
        /// Game Logic
        /// </summary>
        /// <returns></returns>

        turn = Turn::PLAYER1;
        //...................................................................................................
        //...................................Posturing Phase.................................................
        //...................................................................................................
        if (phase == Phase::DrawPhase) {
            for (int i = 0; i < player.size(); i++) {
                player[i].ShuffleDeck();
                while (player[i].GetHand().size() <= player[i].GetMaxHandSize()) {
                    player[i].DrawCard();
                }
                for (int j = 0; j < player[i].GetHand().size(); j++) {
                    player[i].GetHand()[j].SetPosition(Vector2f(400.f + j * 200.f, 720.f));
                }
               /* for (int j = 0; j < player[i].GetAttackTokens(); j++) {
                    AttackTokens[CurrentAToken].setPosition(Vector2f(100 + j * 65, 30));
                    CurrentAToken = (CurrentAToken + 1) % AttackTokens.size();
                }
                for (int j = 0; j < player[i].GetDefenseTokens(); j++) {
                    DefenseTokens[CurrentDToken].setPosition(Vector2f(100 + j * 65, 90));
                    CurrentDToken = (CurrentDToken + 1) % DefenseTokens.size();
                }*/
            }
            phase = Phase::SetUp;
        }
        

        //...................................Draw Cards to full
        //...................................Select Cards to DISCARD
        //Determine who goes first this round
        //first player plays cards
        //second player players cards
        //...................................................................................................
        //....................................Attack Phase...................................................
        //...................................................................................................
        //if hotseat player 1 then player 2 will choose where to strike following formula msg'player1' -> hide player2board show player1board 
        //..........-> place -> msg'player2' ->hide player1board show player2board ->place
        //not hotseat then hide otheplayer board -armor
        //place attack and defense tokens
        //...................................................................................................
        //....................................Resolution Phase...............................................
        //...................................................................................................
        //reveal both sides, 
        //if player has counter card reserved then allow them to play it
        //calculate damage
        //see if a player has won -> exit loop
        //allow continuing of game

        //for (int i = 0; i < numplayers; i++) {
        //    if (player[i].GetHealth() <= 0) {
        //        gameState = State::GAMEOVER;
        //        break;
        //    }
        //}
    }
    if (gameState == State::GAMEOVER) {
        turn = Turn::NONE;
    }
    if (gameState == State::PAUSED) {
    }
    /// <summary>
    /// post turn checks to change phases
    /// </summary>
    // Check to see if SetUp phase is completed, then move to Posture Phase
    int completedTurns = 0;
    if (phase == Phase::SetUp) {
        std::cout << "Set Up Phase\n";
        for (int k = 0; k < player.size(); k++) {
            completedTurns += (player[k].GetMaxPlayHandSize() ==  player[k].GetHandSize());
        }
        if (completedTurns == player.size()) {
            phase = Phase::Posture;
            completedTurns = 0;
        }
    }

    //Check to see if Posture phase is completed, then apply Cards and move to attack phase
    if (phase == Phase::Posture) {
        std::cout << "Posture Phase\n";
        for (int i = 0; i < player.size(); i++) {
            int counterCardCount = 0;
            for (int j = 0; j < player[i].GetHandSize(); j++) {
                counterCardCount += (player[i].GetHand()[j].m_style == Card::Style::counter);
            }
            player[i].isDone(counterCardCount == player[i].GetHandSize() ||
                player[i].GetHandSize() == 0 ||
                player[i].GetIsDone());
            completedTurns += player[i].GetIsDone();
        }
        if (completedTurns == player.size()) {
            phase = Phase::Attack;
            for (int i = 0; i < player.size(); i++) {
                completedTurns = 0;
                player[i].isDone(false);
                for (int j = 0; j < player[i].GetFieldCards().size(); j++)
                    UseCard::Use(player[i].GetFieldCards()[j], player[i]);

               /* for (int j = 0; j < player[i].GetAttackTokens(); j++) {
                    AttackTokens[CurrentAToken].setPosition(Vector2f(100 + j * 65, 30));
                    CurrentAToken = (CurrentAToken + 1) % AttackTokens.size();
                }
                for (int j = 0; j < player[i].GetDefenseTokens(); j++) {
                    DefenseTokens[CurrentDToken].setPosition(Vector2f(100 + j * 65, 90));
                    CurrentDToken = (CurrentDToken + 1) % DefenseTokens.size();
                }*/
            }
            
        }
    }

    //Check to see if Attack Phase is completed then move to Resolution
    if (phase == Phase::Attack) {
        std::cout << "Attack Phase\n";
        for (int i = 0; i < player.size(); i++)
            completedTurns += player[i].GetIsDone();
        if (completedTurns == player.size()) {
            phase = Phase::Resolve;
            completedTurns = 0;
            for (int i = 0; i < player.size(); i++)
                player[i].isDone(false);
        }
    }
    //Check to see if Resolve phase is completed, then move to Draw Phase Resetting key components
    if (phase == Phase::Resolve) {
        std::cout << "Resolve Phase\n";
        for (int i = 0; i < player.size(); i++) {
            for (int j = 0; j < player[i].GetHandSize(); j++) {
                bool finishCheck = false;
                finishCheck += (player[i].GetHand()[j].m_style == Card::Style::counter);
                if (!finishCheck) player[i].isDone(true);
            }
            completedTurns += player[i].GetIsDone();
        }
        if (completedTurns == player.size()) {
            for (int i = 0; i < player.size(); i++) {
                for (int j = player[i].GetFieldCards().size() - 1; j > -1; j--) {
                    if (player[i].GetFieldCards()[j].m_style != Card::Style::stance) {
                        player[i].DiscardPlay(j);
                    }
                }
                if (player[i].m_successfulAttack) {
                    for (int i = 0; i < player[i].GetFieldCards().size(); i++) {

                    }
                }
                player[i].ResetToken();
            }
            completedTurns = 0;
            phase = Phase::DrawPhase;
        }
    }
    for (int i = 0; i < player.size(); i++) {
        player[i].isDone(false);
    }
   
    window.clear();
    window.draw(Background);
    
    for (int i = 0; i < boards.size(); i++) {
        boards[i].Draw(window);
    }
    for (unsigned int i = 0; i < player.size(); i++) {
            player[i].Draw(window);
        for (int j = 0; j < player[i].GetFieldCards().size(); j++) {
            window.draw(player[i].GetFieldCards()[j].sprite);
        }
        for (int j = 0; j < player[i].GetHandSize(); j++) {
            
            //window.draw(boards[i].GetSprite());
        }
            
    }


    if (phase != Phase::SetUp || phase != Phase::DrawPhase) {
        window.draw(EndPhaseButton);
    }
    window.draw(ReshuffleButton);
        window.display();
    }
    for (int i = 0; i < player.size(); i++) {
        player[i].Destroy();
    }
    return 0;
}