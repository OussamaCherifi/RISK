#ifndef CARDS_H
#define CARDS_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Orders.h"
#include "Player.h"
using namespace std;

class Player;

//create Warzone card types

enum CardType {BOMB, BLOCKADE, AIRLIFT, NEGOTIATE, UNKNOWN};
class Deck;

class Cards{
private:
    CardType type;
public:
    Cards(CardType t);
    ~Cards() = default;
    Cards(const Cards& c1);
    void play(Player *player, Deck *deck) const;
    CardType getType() const;
    string getTypeAsString() const;
};

class Deck{
private:
    vector<Cards> cards;
public:
    Deck();
    Deck(const Deck& d1);
    Cards draw();
    int getCardNum();
    void addCard(const Cards& card);
};

class Hand{
private:
    vector <Cards> hands;
public:
    Hand() = default;
    Hand(const Hand& h1);
    void addCard(const Cards& card);
    void removeCard(int index);
    const Cards& getCard(int index);
    int getCardNum();
};
void testCards();

#endif //CARDS_H