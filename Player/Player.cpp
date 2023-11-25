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
void Player::setDeck(Deck deck) {
    this->deck = &deck;
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

vector<Territory*> Player::toDefend(){
    return territoryList;
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

vector<Territory*> Player::toAttack(){
    vector<Territory *> attackList;

    for(Territory *t : territoryList){
        for(int i = 0; i < t->getAdjacentTerritories()->size(); i++) {
            Territory *adjacent = t->getAdjacentTerritories()->at(i);

            //check if player owns the territory, if yes break
            if (adjacent->getPlayer()->getID() == id) {
                continue;
            }
                //check if the territory is already in the attacklist, if yes break
            else {
                bool alreadyInList = false;
                for (Territory *t: attackList) {
                    if (t->getName() == adjacent->getName()) {
                        alreadyInList = true;
                        break;
                    }
                }
                if (alreadyInList) {
                    continue;
                } else {
                    attackList.push_back(adjacent);
                }
            }
        }
    }
    return attackList;
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

void Player::issueOrder(){
    //deploy phase
    int territoryIndex, numUnits;

    int tempNum = *reinforcementPool;

    cout << "\nIt is " << playerName << "'s turn to issue Orders!" << endl;
    cout << "Let's start by deploying army units from your reinforcement pool. " << endl;

    while (tempNum > 0){
        cout << "You have " << tempNum << " army units in your reinforcement pool." << endl;

        //print the player's list of territories
        printTerritoryList();

        //get user input for which territory they want to deploy armies to
        cout << "Enter the index of territory you wish to deploy army units:";
        territoryIndex = getUserTerritoryIndex(toDefend());

        //get user input for num of armies to deploy
        numUnits = getUserNum(tempNum);

        tempNum -= numUnits;
        cout << "A Deploy Order of " <<  numUnits << " unit(s) to " << territoryList[territoryIndex]->getName() << " will be issued." << endl;
        auto *deployOrder = new Deploy(this, territoryList[territoryIndex], numUnits);
        ordersList->addList(deployOrder);
    }

    cout << "\nGreat, all your reinforcement troops have been deployed." << endl;

    // advance phase
    cout << "Now let's issue Advance orders!" << endl;

    bool playerDone = false;

    while(!playerDone) {
        string playerInput;
        int playerChoice, sourceIndex, targetIndex, numArmies;

        cout << "Do you wish to issue Advance orders? Enter \"YES\" or \"NO\"" << endl;
        cout << "Any other input would be considerd as \"NO\"" << endl;
        cin >> playerInput;

        if (playerInput == "YES") {
            cout << "Enter \"1\" to defend and \"2\" to attack" << endl;
            cin >> playerChoice;

            if (playerChoice == 1) {
                //print toDefend list
                printToDefend();

                //get user source territory
                cout << "Enter the index of the territory you want to move troops from";
                sourceIndex = getUserTerritoryIndex(toDefend());

                //get user target territory
                cout << "Enter the index of the territory you want to move troops to";
                targetIndex = getUserTerritoryIndex(toDefend());

                //get num of armies to move
                numUnits = getUserNum(toDefend()[sourceIndex]->getArmies());

                cout << "An Advance Order of " << numUnits << " army units from " << toDefend()[sourceIndex]->getName() << " to "
                     << toDefend()[targetIndex]->getName() << " will be issued." << endl;
                auto *advanceOrder = new Advance(this, toDefend()[sourceIndex], toDefend()[targetIndex], numArmies);
                ordersList->addList(advanceOrder);

            } else if (playerChoice == 2) {
                printTerritoryList();
                printToAttack();

                cout << "Enter the index of the territory you want to move troops from";
                sourceIndex = getUserTerritoryIndex(toDefend());

                cout << "Enter the index of the territory you want to move troops to";
                targetIndex = getUserTerritoryIndex(toAttack());

                numUnits = getUserNum(toDefend()[sourceIndex]->getArmies());

                cout << "An Advance Order of " << numUnits << " army units from " << territoryList[sourceIndex]->getName()
                     << " to " << toAttack()[targetIndex]->getName() << " will be issued." << endl;
                auto *advanceOrder = new Advance(this, toDefend()[sourceIndex], toAttack()[targetIndex], numArmies);
                ordersList->addList(advanceOrder);
            }


            else{
                cout << "Invalid choice." << endl;
            }
        }

        else{
            playerDone = true;
        }

    }

    int cardIndex;
    cout << "\nYou can now play one card from your hand." << endl;
    if(hand->getCardNum() == 0) cout << "You do not own any cards" << endl;
    else {

        //For testing purposes
        Cards *testCard = new Cards(static_cast<CardType>(3));
        hand->addCard(*testCard);

        //Print cards
        cout << "Here are the cards in your hand: " << endl;
        for (int i = 0; i < hand->getCardNum(); i++) {
            cout << i << "- " << hand->getCard(i).getTypeAsString() << endl;
        }

//        cout << "Enter the index of the card you want to play" << endl;
//        cin >> cardIndex;
//
//        //For Testing Purposes
//        cardIndex = 1;
//        cout << "An Airlift order will be played!" << endl;
//        cout << "Here are your territories you own: " << endl;
//        for (int i = 0; i < toDefend().size(); i++) {
//            cout << i << "- " << territoryList[i]->getName() << endl;
//        }
//        bool sourceFound = false, targetFound = false, validNum = false;
//        int sourceIndex, targetIndex, numCardUnits;
//        while (!sourceFound) {
//            cout << "Enter the index of the territory you want to move troops from";
//            cin >> sourceIndex;
//
//            if (sourceIndex >= 0 && sourceIndex < toDefend().size()) {
//                sourceFound = true;
//            } else {
//                cout << "Territory not found." << endl;
//            }
//        }
//
//        while (!targetFound) {
//            cout << "Enter the index of the territory you want to move troops to";
//            cin >> targetIndex;
//
//            if (targetIndex >= 0 && targetIndex < toDefend().size()) {
//                targetFound = true;
//            } else {
//                cout << "Territory not found." << endl;
//            }
//        }
//
//        while (!validNum) {
//            cout << "How many army units do you wish to move?";
//            cin >> numCardUnits;
//
//            if (numCardUnits > 0 && numCardUnits <= toDefend()[sourceIndex]->getArmies())
//                validNum = true;
//            else {
//                cout << "Invalid number. Please enter another number." << endl;
//            }
//        }
//
//        cout << "An Airlift Order of " << numCardUnits << " army units from " << territoryList[sourceIndex]->getName()
//             << " to " << toDefend()[targetIndex]->getName() << " will be issued." << endl;
//        Airlift *airlift = new Airlift(this, territoryList[sourceIndex], territoryList[targetIndex], numCardUnits);
//        ordersList->addList(airlift);

//        hand->getCard(cardIndex).play(this, deck);
    }
    
}
// tiffany