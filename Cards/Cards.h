#ifndef CARDS_H
#define CARDS_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Define Warzone card types

enum CardType {BOMB, BLOCKADE, REINFORCEMENT, AIRLIFT, DIPLOMACY, UNKNOWN};

class Cards{
private:
    CardType type;
public:
    Cards(CardType type);
    void play();
    CardType getType() const;
    string getTypeAsString() const;
};

class Deck{
private:
    vector<Cards> cards;
public:
    Deck();
    Cards draw();
    const int getCardNum();
    void addCard(const Cards& card);
};

class Hand{
private:
    vector <Cards> hands;
public:
    void addCard(const Cards& card);
    void removeCard(int index);
    const Cards& getCard(int index);
    const int getCardNum();
};

void testCards();
#endif //CARDS_H
