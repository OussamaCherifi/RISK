#ifndef CARDS_H
#define CARDS_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Orders.h"
#include "Player.h"
using namespace std;

//create Warzone card types
enum CardType {BOMB, BLOCKADE, REINFORCEMENT, AIRLIFT, DIPLOMACY, UNKNOWN};
class Deck;

class Cards{
private:
    CardType* type;
public:
    Cards(CardType t);
    Cards(const Cards& c1);
    void play(Player& player, Deck& deck) const;
    CardType* getType() const;
    string getTypeAsString() const;
};

class Deck{
private:
    vector<Cards*> cards;
public:
    Deck();
    ~Deck();
    Deck(const Deck& d1);
    Cards *draw();
    int getCardNum();
    void addCard(const Cards& card);
};

class Hand{
private:
    vector <Cards*> hands;
public:
    Hand() = default;
    ~Hand();
    Hand(const Hand& h1);
    void* addCard(const Cards& card);
    void * addCard(const Cards* card);
    void removeCard(const Cards &card);
    const Cards& getCard(int index);
    int getCardNum();
};
void testCards();

#endif //CARDS_H