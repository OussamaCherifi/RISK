#include "Player.h"

#include<iostream>
#include<vector>

using namespace std;

//default constructor
Player::Player() {
    //territorylist remains empty by default
    this->hand = new Hand(); //empty hand
    this->ordersList = new OrdersList(); //empty orderslist
    this->playerName = "";
    this->reinforcementPool;
}

//copy constructor
Player::Player(const Player &p){
    this->territoryList = p.territoryList;
    this->hand = p.hand;
    this->ordersList = p.ordersList;
    this->playerName = p.playerName;
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
    delete reinforcementPool;
}

//assignment operator
 Player& Player::operator=(const Player& p){
    this->territoryList = p.territoryList;
    this->hand = p.hand;
    this->ordersList = p.ordersList;
    this->playerName = p.playerName;
    this->reinforcementPool = p.reinforcementPool;
    return *this;
 }

//setter
void Player::setName(const std::string& newName) {
    playerName = newName;
}
void Player::setReinforcementPool(int *num){
    this->reinforcementPool = num;
}

//getter
string Player::getPlayerName() {
    return playerName;
}

int *Player::getReinforcementPool(){
    return reinforcementPool;
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
    string territoryName;
    int territoryIndex, numUnits;
    bool territoryFound = false, correctNum = false;

    cout << "Let's start by deploying army units from your reinforcement pool. " << endl;

    while (getReinforcementPool() > 0){
            cout << "You have " << getReinforcementPool() << " army units in your reinforcement pool." << endl;

            cout << "Here are your territories to defend: " << endl;
            for (Territory *t : toDefend()){
                cout << " - " << t->getName() << endl;
            }

            while(!territoryFound){
                cout << "Enter the name of territory you wish to deploy army units: ";
                cin >> territoryName;

                for(int i = 0; i < getTerritoryList().size(); i++){

                    if (territoryName == getTerritoryList()[i]->getName()){
                        territoryFound = true;
                        territoryIndex = i;
                        break;
                    }
                }
                cout << "Territory not found. Please re-enter the territory name." << endl;
            }

            while(!correctNum){
                cout << "How many army units do you wish to deploy?";
                cin >> numUnits;

                if (numUnits > 0 && numUnits <= *p->getReinforcementPool())
                    correctNum = true;

                cout << "Invalid number. Please enter another number." << endl; 
            }

            cout << "A Deploy Order of " <<  numUnits << " units to " << territoryName << endl;
            Deploy *deployOrder = new Deploy(this, getTerritoryList()[territoryIndex], numUnits);

    }
    
}
// tiffany