#include "Cards.h"
#include <random>
#include <chrono>
using namespace std;

//copy constructor for cards
Cards::Cards(const Cards& c1):type(c1.type){}

//constructor for Cards
Cards::Cards(CardType t) {
    this->type=t;
}
CardType Cards::getType() const{
    return type;
}
//plays the card, the orders made by different cards will be implemented in future assignment
void Cards::play() const{
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
//copy constructor for Deck
Deck::Deck(const Deck& d1):cards(d1.cards){}

Deck::Deck(){
    //create and shuffle deck
    for (int i=0; i<5; ++i){
        cards.emplace_back(static_cast<CardType>(i));
    }
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(cards.begin(), cards.end(), default_random_engine(seed));
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
int Deck::getCardNum() {
    return cards.size();
}
//add a card to your hand
void Deck::addCard(const Cards& card1){
    cards.push_back(card1);
}
//copy constructor for Hand
Hand::Hand(const Hand&h1):hands(h1.hands){}
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
int Hand::getCardNum(){
    return hands.size();
}
//get a card from the hand
const Cards& Hand::getCard(int index){
    return hands[index];
}

