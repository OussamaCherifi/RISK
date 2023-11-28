#include "Player.h"
#include "Map.h"
#include <algorithm>
#include<iostream>
#include<vector>
#include <map>

using namespace std;

//default constructor
Player::Player() {
    //territorylist remains empty by default
    this->hand = new Hand(); //empty hand
    this->ordersList = new OrdersList(); //empty orderslist
    this->playerName = "";
    this->reinforcementPool = new int (0);
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
    reinforcementPool = num;
}

void Player::setID(int num) {
    this->id = num;
}
void Player::setDeck(Deck *deck) {
    this->deck = deck;
}

void Player::setPS(PlayerStrategy *playerStrategy){
    ps = playerStrategy;
}
//getter
string Player::getPlayerName() {
    return playerName;
}

int *Player::getReinforcementPool(){
    return reinforcementPool;
}

int Player::getID() {
    return id;
}

set<Player *> Player::getDiplomaticRelations() {
    return diplomaticRelations;
}

PlayerStrategy *Player::getPS() {
    return ps;
}

void Player::clearDiplomaticRelations(){
    diplomaticRelations.clear();
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
bool Player::isDiplomaticRelation(Player *attacker) const {
    return diplomaticRelations.find(attacker) != diplomaticRelations.end();
}
bool Player::operator==(const Player &other) const {
    return this->id == other.id;
}
bool Player::operator!=(const Player &other) const {
    return !(*this == other);
}

//getters
vector<Territory*> &Player::getTerritoryList(){
    return territoryList;
}

Hand *Player::getHand(){
    return hand;
}
OrdersList *Player::getOrdersList(){
    return ordersList;
}
Deck *Player::getDeck(){
    return deck;
}

//setters

//adds territories owned by the player to their collection
void Player::addTerritory(Territory* t){
    territoryList.push_back(t);
}

void Player::removeTerritory(Territory *t) {
    int index = -1;
    for(int i = 0; i < territoryList.size(); i++){
        if(t->getName() == territoryList[i]->getName()){
            index = i;
            break;
        }
    }
    if(index != -1)
        territoryList.erase(territoryList.begin() + index);
    else
        cout << "Error: could not remove territory" << endl;
}

int Player::calculateContinentBonus(Map *mapCreated){
    int bonus = 0;

    //storing the number of territories per continent
    vector<int> tPerContinents;

    for(auto it : mapCreated->getContinentNameAndNum()){
        tPerContinents.push_back(it.second);
    }

    //storing the number of the player's territories per continent
    vector<int> playerTPerContinents(tPerContinents.size(), 0);

    for(int i = 0; i < territoryList.size(); i++){
        bool found = false;
        int continentIndex = 0;

        for(auto it : mapCreated->getContinentNameAndNum()){
            if(territoryList[i]->getContinent() == it.first) {
                found = true;
                break;
            }
            continentIndex++;
        }

        if (found) {
            playerTPerContinents[continentIndex]++;
        }
    }

    //comparing both vector and array, if there is an equal value, then the player owns a continent and gets a bonus
    for (int i = 0; i < tPerContinents.size(); i++){
        if (tPerContinents[i] == playerTPerContinents[i]) {
            bonus++;
        }
    }

    return bonus*5;
}

void Player::printTerritoryList(){
    cout << "Here are your territories you own: " << endl;
    for (int i = 0; i < territoryList.size(); i++) {
        cout << i << "- " << territoryList[i]->getName() << " - " << territoryList[i]->getArmies() << " troop(s)"<< endl;
    }
}

void Player::printToDefend(){
    cout << "Here are your territories to defend: " << endl;
    for (int i = 0; i < toDefend().size(); i++){
        cout << i << "- " << toDefend()[i]->getName()  << " - " << toDefend()[i]->getArmies() << " troop(s)" << endl;
    }
}

void Player::printToAttack() {
    cout << "Here are the territories to attack: " << endl;
    for (int i = 0; i < toAttack().size(); i++) {
        cout << i << "- " << toAttack()[i]->getName() << " - " << toAttack()[i]->getArmies() << " troop(s)"<< endl;
    }
}

int Player::getUserNum(int max){
    bool correctNum = false;
    int numUnits;
    while(!correctNum){
        cout << "How many army units do you wish to deploy?";
        cin >> numUnits;

        if (numUnits > 0 && numUnits <= max)
            correctNum = true;
        else {
            cout << "Invalid number. Please enter another number." << endl;
        }
    }

    return numUnits;
}

int Player::getUserTerritoryIndex(vector<Territory *> list){
    bool territoryFound = false;
    int index;
    while(!territoryFound){
        cin >> index;

        if(index >= 0 && index < list.size()){
            territoryFound = true;
        }
        else {
            cout << "Territory not found. Please re-enter the valid territory index." << endl;
        }
    }

    return index;
}

vector<Territory*> Player::toDefend(){
    return ps->toDefend();
}

vector<Territory*> Player::toAttack(){
    return ps->toAttack();
}

void Player::issueOrder(){
    ps->issueOrder();
}
// tiffany