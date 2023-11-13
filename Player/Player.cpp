#include "Player.h"

#include<iostream>
#include<vector>

using namespace std;

//default constructor
Player::Player() {
    //territorylist remains empty by default
    this->hand = new Hand(); //empty hand
    this->ordersList = new OrdersList(); //empty orderslist
}

//copy constructor
Player::Player(const Player &p){
    this->territoryList = p.territoryList;
    this->hand = p.hand;
    this->ordersList = p.ordersList;
}

//destructor
Player::~Player() {}

//assignment operator
 Player& Player::operator=(const Player& p){
    this->territoryList = p.territoryList;
    this->hand = p.hand;
    this->ordersList = p.ordersList;
    return *this;
 }

 //stream insertion operator
ostream &operator<<(ostream &out, const Player &p){
    out << "Territories owned by player";
    for(Territory* territory : p.territoryList){
        out << "territory" << ", "; 
    }
    out << "Player's hand has " << p.hand->getCardNum() << " cards";
    out << "\n Player's Orderslist has " << p.ordersList->getSize() << " orders";
    return out;
}
    

//getters
vector<Territory*> Player::getTerritoryList(){
    return territoryList;
}
Hand *Player::getHand(){
    return hand;
}
OrdersList *Player::getOrdersList(){
    return ordersList;
}

//adds territories owned by the player to their collection
void Player::addTerritory(Territory* t){
    territoryList.push_back(t);
}

vector<Territory*> Player::toDefend(){
    vector<Territory*> defendList;

    //arbitrary list of territories
    defendList.push_back(territoryList[0]);
    return defendList;
}

vector<Territory*> Player::toAttack(){
    vector<Territory*> attackList;

    //arbitrary list of territories
    attackList.push_back(territoryList[1]);

    return attackList;
}

void Player::issueOrder(){
    //arbitrary order for now
    Deploy* o1 = new Deploy();
    ordersList->addList(o1);
}
// tiffany