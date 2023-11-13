#include "Player.h"

#include<iostream>
#include<vector>

using namespace std;

//copy constructor
Player::Player(const Player &p){
    this->territoryList = p.territoryList;
    this->hand = p.hand;
    this->ordersList = p.ordersList;
    this->reinforcementPool = p.reinforcementPool;
}

//destructor
Player::~Player() {
    for (Territory *t : territoryList){
                delete t;
    }
    territoryList.clear();

    delete reinforcementPool;

    delete hand;
    delete ordersList;
}

//assignment operator
 Player& Player::operator=(const Player& p){
    this->territoryList = p.territoryList;
    this->hand = p.hand;
    this->ordersList = p.ordersList;
    this->reinforcementPool = p.reinforcementPool;
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
    
void Player::addDiplomaticRelation(Player *player1) {
    diplomaticRelations.insert(player1);
}
bool Player::isDiplomaticRelation(Player attacker) const {
    return diplomaticRelations.find(&attacker) != diplomaticRelations.end();
}
bool Player::operator==(const Player &other) const {
    return this->id == other.id;
}
bool Player::operator!=(const Player &other) const {
    return !(*this == other);
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
int *Player::getReinforcementPool(){
    return reinforcementPool;
}
Deck& Player::getDeck(){
    return deck;
}

//setters
void Player::setReinforcementPool(int *num){
    this->reinforcementPool = num;
}

//adds territories owned by the player to their collection
void Player::addTerritory(Territory* t){
    territoryList.push_back(t);
}

vector<Territory*> Player::toDefend(){
    return territoryList;
}

vector<Territory*> Player::toAttack(){
    vector<Territory*> attackList;
    // get adjacent territories
    return attackList;
}

void Player::issueOrder(){
    cout << "Issuing Orders" << endl;
    
}
// tiffany