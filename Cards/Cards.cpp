#include "Cards.h"
#include <random>
#include <chrono>
using namespace std;

//copy constructor for cards
Cards::Cards(const Cards& c1):type(new CardType(*(c1.type))){}

//constructor for Cards
Cards::Cards(CardType t) : type(new CardType(t)) {}

CardType *Cards::getType() const{
    return type;
}
//plays the card, the orders made by different cards will be implemented in future assignment
void Cards::play(Player& player, Deck& deck) const{
    Orders* order = nullptr;
    switch(*type) {
        case BOMB:
            break;
        case BLOCKADE:;
            break;
        case AIRLIFT:
            break;
        case DIPLOMACY:
            break;
        default:
            cout<<"Unknown card type played"<<endl;
            return;
    }
    player.getOrdersList()->addList(order);
    player.getHand().removeCard(*this);
    deck.addCard(*this);
    cout<<"A "<< getTypeAsString()<<" card was played."<<endl;
}
string Cards::getTypeAsString() const{
    switch(*type) {
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
Deck::Deck(const Deck& d1){
    for (const auto &card : d1.cards){
        cards.push_back(new Cards(*card));
    }
}

Deck::Deck(){
    //create and shuffle deck
    for (int i=0; i<5; ++i){
        cards.push_back(new Cards(static_cast<CardType>(i)));
    }
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(cards.begin(), cards.end(), default_random_engine(seed));
}
//draw a card from the deck as long as it is not empty
Cards *Deck::draw(){
    if (cards.empty()){
        cout<<"The deck is empty"<<endl;
        return new Cards{UNKNOWN};
    }
    Cards *drawn= cards.back();
    cards.pop_back();
    return drawn;
}
//get number of cards in deck
int Deck::getCardNum() {
    return cards.size();
}
//add a card to the deck
void Deck::addCard(const Cards& card1){
    cards.push_back(new Cards(card1));
}

//destructor for Deck
Deck::~Deck(){
    for (const auto &card : cards){
        delete card;
    }
    cards.clear();
}

//copy constructor for Hand
Hand::Hand(const Hand&h1) {
    for (const auto &card :h1.hands){
        hands.push_back(new Cards(*card));
    }
}

// add a card to your hand
void* Hand::addCard(const Cards& card){
    hands.push_back(new Cards(card));
}
void* Hand::addCard(const Cards *card) {
    hands.push_back(new Cards(*card));
}
// remove a card from your hand
void Hand::removeCard(const Cards &card){
    auto it = std::remove_if(hands.begin(), hands.end(),
                             [&card](Cards* c) { return *c->getType() == *card.getType(); });

    // Ensure proper cleanup of the removed cards
    for (auto removed = it; removed != hands.end(); ++removed) {
        delete *removed;
    }

    // Erase the removed cards from the vector
    hands.erase(it, hands.end());
}

// get number of cards in hand
int Hand::getCardNum(){
    return hands.size();
}
//get a card from the hand
const Cards& Hand::getCard(int index){
    return *hands[index];
}
Hand::~Hand(){
    for (const auto &card : hands){
        delete card;
    }
    hands.clear();
}

