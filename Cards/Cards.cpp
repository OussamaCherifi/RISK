#include "Cards.h"
#include "GameEngine.h"
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
void Cards::play(Player *player, Deck *deck) const{
    Orders* order;
    int terrIndex, sourceIndex, targetIndex, numArmies, userIndex;
    bool alreadyInList = false, correctNum = false;
    vector<Player *> enemies;
    switch(type) {
        case BOMB:
            player->printToAttack();
            cout << "Enter the index of the territory you want to bomb" << endl;
            terrIndex = player->getUserTerritoryIndex(player->toAttack());
            cout << "A Bomb Order of to " << player->toAttack()[terrIndex]->getName() << " will be issued." << endl;
            order= new Bomb(player, player->toAttack()[terrIndex]);
            break;
        case BLOCKADE:
            player->printTerritoryList();
            cout << "Enter the index of the territory you want to blockade" << endl;
            terrIndex = player->getUserTerritoryIndex(player->getTerritoryList());
            cout << "A Blockade Order of to " << player->getTerritoryList()[terrIndex]->getName() << " will be issued." << endl;
            order = new Blockade(player, player->getTerritoryList()[terrIndex]);
            break;
        case AIRLIFT:
            player->printTerritoryList();
            cout << "Enter the index of the territory you want to move troops from";
            sourceIndex = player->getUserTerritoryIndex(player->getTerritoryList());
            cout << "Enter the index of the territory you want to move troops to";
            targetIndex = player->getUserTerritoryIndex(player->getTerritoryList());
            numArmies = Player::getUserNum(player->getTerritoryList()[sourceIndex]->getArmies());
            cout << "An Airlift Order of " <<  numArmies << " unit(s) from " << player->getTerritoryList()[targetIndex]->getName() << " to " << player->getTerritoryList()[sourceIndex]->getName() << " will be issued." << endl;
            order= new Airlift(player, player->getTerritoryList()[sourceIndex], player->getTerritoryList()[targetIndex], numArmies);
            break;
        case NEGOTIATE:
            //run through to attack territories and create a vector of enemy players
            for(Territory *t : player->toAttack()){
                Player *enemy = t->getPlayer();
                for(Player *p : enemies){
                    if(enemy->getID() == p->getID()){
                        alreadyInList = true;
                        break;
                    }

                }
                if(alreadyInList) continue;
                else enemies.push_back(enemy);
            }

            //print the list with their index
            cout << "Here are the players in the game:" << endl;
            for (int i = 0; i < enemies.size(); i++){
                cout << i << "- " << enemies[i]->getPlayerName() << endl;
            }

            //get userindex
            while(!correctNum){
                cout << "How many army units do you wish to deploy?";
                cin >> userIndex;

                if (userIndex > 0 && userIndex <= enemies.size() - 1)
                    correctNum = true;
                else {
                    cout << "Invalid index. Please enter another number." << endl;
                }
            }
            //create Negotiate order
            cout << "A Negotiate Order to " << enemies[userIndex]->getPlayerName() << " will be issued" << endl;
            order = new Negotiate(player, enemies[userIndex]);
            break;
        default:
            cout<<"Unknown card type played"<<endl;
            return;
    }
    player->getOrdersList()->addList(order);
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
        case NEGOTIATE:
            return "Negotiate";
        default:
            return "Not Valid";
    }
}
//copy constructor for Deck
Deck::Deck(const Deck& d1):cards(d1.cards){}

Deck::Deck(){
    cards = vector<Cards>();
    //create and shuffle deck
    for (int j=0; j<5; j++) {
        for (int i = 0; i < 5; ++i) {
            cards.emplace_back(static_cast<CardType>(i));
        }
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
//add a card to the deck
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
//        delete hands[index];
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

