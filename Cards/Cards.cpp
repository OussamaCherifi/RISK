#include <iostream>
#include "Cards.h"
#include <cstdlib>
#include <ctime>
#include <random>
using namespace std;

Cards::Cards(CardType type) {
    this->type=type;
}

CardType Cards::getType() const{
    return type;
}
//plays the card, the orders made by different cards will be implemented in future assignment
void Cards::play(){
    cout<<"A "<< getTypeAsString()<<" card was played."<<endl;
}
string Cards::getTypeAsString() const{
    switch(type) {
        case BOMB:
            return "Bomb";
        case REINFORCEMENT:
            return "Reinforcement";
        case BLOCKADE:
            return "Blockade";
        case AIRLIFT:
            return "Airlift";
        case DIPLOMACY:
            return "Diplomacy";
        default:
            return "Not Valid";
    }
}

Deck::Deck(){
    //create and shuffle deck
    for (int i=0; i<5; ++i){
        cards.emplace_back(static_cast<CardType>(i));
    }
    srand(static_cast<unsigned>(time(nullptr)));
    shuffle(cards.begin(), cards.end(), std::mt19937(std::random_device()()));
}
//draw a card from the deck as long as it is not empty
Cards Deck::draw(){
    if (cards.empty()){
        cout<<"The deck is empty"<<endl;
        return {UNKNOWN};
    }
    Cards drawn= cards.back();
    cards.pop_back();
    return drawn;
}
//get number of cards in deck
const int Deck::getCardNum() {
    return cards.size();
}
void Deck::addCard(const Cards& card1){
    cards.push_back(card1);
}
// add a card to your hand
void Hand::addCard(const Cards& card){
    hands.push_back(card);
}
// remove a card from your hand
void Hand::removeCard(int index){
    if (index>=0 && index<hands.size()){
        hands.erase(hands.begin() + index);
    }
}
// get number of cards in hand
const int Hand::getCardNum(){
    return hands.size();
}
//get a card from the hand
const Cards& Hand::getCard(int index){
    return hands[index];
}

void testCards(){
    Deck deck;
    Hand hand;

    //draw cards to add them to the deck
    for(int i=0; i<5;++i){
        Cards card= deck.draw();
        hand.addCard(card);
        cout<<"Drew a "<< card.getTypeAsString()<< " card."<<endl;
        cout<<"Deck size: "<< deck.getCardNum()<<endl;
    }
    //play a card from your hand, then put in back at the bottom of the deck once it is played
    if (hand.getCardNum()>0){
        Cards card = hand.getCard(0);
        card.play();
        deck.addCard(card);
        hand.removeCard(0);
    }
}