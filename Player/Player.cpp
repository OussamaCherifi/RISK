#include "Player.h"

#include<iostream>
#include<vector>

using namespace std;

//default constructor
Player::Player() {
    //territorylist remains empty by default
    this->ptr_hand = new Hand(); //empty hand
    this->ptr_ordersList = new OrdersList(); //empty orderslist
}

//copy constructor
Player::Player(const Player &p){
    this->territoryList = p.territoryList;
    this->ptr_hand = p.ptr_hand;
    this->ptr_ordersList = p.ptr_ordersList;
}

//assignment operator
 Player& Player::operator=(const Player& p){
    this->territoryList = p.territoryList;
    this->ptr_hand = p.ptr_hand;
    this->ptr_ordersList = p.ptr_ordersList;
    return *this;
 }

 //stream insertion operator
// ostream& Player::operator<<(ostream& os, const Player& p){
//     os << "Territories owned by player";
//     for(Territory* territory : p.territoryList){
//         os << territory; //might need to use the getter of the territory class
//     }
//     os << "\n Player's hand: " << *p.ptr_hand << "\n"; // need to use << of Hand
//     os << "Player's orders list: " << *p.ptr_ordersList; // need to use << of orderslist class

// }

//getters
vector<Territory*> Player::getTerritoryList(){
    return territoryList;
}
Hand* Player::getPtrHand(){
    return ptr_hand;
}
OrdersList* Player::getPtrOrdersList(){
    return ptr_ordersList;
}

//adds territories owned by the player to their collection
void Player::addTerritory(Territory* t){
    territoryList.push_back(t);
}

vector<Territory*> Player::toDefend(){
    vector<Territory*> defendList;

    //arbitrary list of territories
    defendList.push_back(territoryList[0]);
    defendList.push_back(territoryList[1]);
    
    return defendList;
}

vector<Territory*> Player::toAttack(){
    vector<Territory*> attackList;

    //arbitrary list of territories
    attackList.push_back(territoryList[2]);
    attackList.push_back(territoryList[3]);

    return attackList;
}

void Player::issueOrder(){
    //new Order();
    //OrdersList has its own add order to be implemented 
    
}
// tiffany