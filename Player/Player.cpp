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

    for(Territory t : territoryList){
        for(int i = 0; i < t.getAdjacentTerritories()->size(); i++){
            Territory *adjacent = t.getAdjacentTerritories()->at(i);
            //check if player owns the territory, if yes break
            if(adjacent->getPlayer() == this)
                break;
            //check if the territory is already in the attacklist, if yes break
            else if(*find(attackList.begin(), attackList.end(), adjacent) != *attackList.end()) {
                break;
            }
            else {
                attackList.push_back(adjacent);
            }
        }
    }
    return attackList;
}

void Player::issueOrder(){
    int deployIndex, territoryIndex, numUnits;
    bool territoryFound = false, correctNum = false;

    cout << "Let's start by deploying army units from your reinforcement pool. " << endl;

    while (*getReinforcementPool() > 0){
        cout << "You have " << *reinforcementPool << " army units in your reinforcement pool." << endl;

        cout << "Here are your territories to defend: " << endl;
        for (int i = 0; i < toDefend().size(); i++){
            cout << i << "- " << toDefend()[i]->getName() << endl;
        }

        while(!territoryFound){
            cout << "Enter the index of territory you wish to deploy army units:";
            cin >> deployIndex;

            if(deployIndex >= 0 && deployIndex < toDefend().size()){
                territoryFound = true;
                territoryIndex = deployIndex;
            }
            else {
                cout << "Territory not found. Please re-enter the valid territory index." << endl;
            }
        }

        while(!correctNum){
            cout << "How many army units do you wish to deploy?";
            cin >> numUnits;

            if (numUnits > 0 && numUnits <= *reinforcementPool)
                correctNum = true;
            else {
                cout << "Invalid number. Please enter another number." << endl;
            }
        }

        territoryFound = false; correctNum = false;
        int *ptrNum = new int(*reinforcementPool - numUnits);
        setReinforcementPool(ptrNum);
        cout << "A Deploy Order of " <<  numUnits << " unit(s) to " << toDefend()[territoryIndex]->getName() << " will be issued." << endl;
        auto *deployOrder = new Deploy(this, toDefend()[territoryIndex], numUnits);
        ordersList->addList(deployOrder);
    }

    cout << "\nGreat, all your reinforcement troops have been deployed." << endl;
    cout << "Now let's issue Advance orders!" << endl;

    bool playerDone = false;

    while(!playerDone){
        string playerInput, sourceTerritory, targetTerritory;
        int playerChoice, sourceIndex, targetIndex, numArmies;
        bool sourceFound = false, targetFound = false;

        cout << "Do you wish to issue Advance orders? Enter \"YES\" or \"NO\"" << endl;
        cout << "Any other input would be considerd as \"NO\"" << endl;
        cin >> playerInput;

        if(playerInput == "YES"){
            cout << "Enter \"1\" to defend and \"2\" to attack" << endl;
            cin >> playerChoice;

            if(playerChoice == 1){
                cout << "Here are your territories to defend: " << endl;
                for (Territory *t : toDefend()){
                    cout << " - " << t->getName() << endl;
                }

                while(!sourceFound){
                cout << "Enter the name of the territory you want to move troops from";
                cin >> sourceTerritory;

                for(int i = 0; i < toDefend().size(); i++){

                    if (sourceTerritory == toDefend()[i]->getName()){
                        sourceFound = true;
                        sourceIndex = i;
                        break;
                    }
                }
                cout << "Territory not found." << endl;
                }

                while(!targetFound){
                    cout << "Enter the name of the territory you want to move troops to";
                    cin >> targetTerritory;

                    for(int i = 0; i < toDefend().size(); i++){

                        if (targetTerritory == territoryList[i]->getName()){
                            targetFound = true;
                            targetIndex = i;
                            break;
                        }
                    }

                    cout << "Territory not found." << endl;
                }

                cout << "How many army units do you want to move?" << endl;
                cin >> numArmies;

                cout << "An Advance Order of " << numArmies << " army units from " << sourceTerritory << " to " << targetTerritory <<  " will be issued." << endl;
                auto *advanceOrder = new Advance(this, toDefend()[sourceIndex], toDefend()[targetIndex], numArmies);
                ordersList->addList(advanceOrder);
            }

            else if (playerChoice == 2) {
                cout << "Here are your territories to attack: " << endl;
                for (Territory *t : toAttack()){
                    cout << " - " << t->getName() << endl; 
                }

                while(!sourceFound){
                    cout << "Here are the territories you own: " << endl;
                    for (Territory *t : territoryList){
                        cout << " - " << t->getName() << endl;
                    }
                    cout << "Enter the name of the territory you want to move troops from";
                    cin >> sourceTerritory;

                    for(int i = 0; i < territoryList.size(); i++){

                        if (sourceTerritory == territoryList[i]->getName()){
                            sourceFound = true;
                            sourceIndex = i;
                            break;
                        }
                    }
                    cout << "Territory not found." << endl;
                }

                while(!targetFound){
                    cout << "Enter the name of the territory you want to move troops to";
                    cin >> targetTerritory;

                    for(int i = 0; i < toAttack().size(); i++){

                        if (targetTerritory == toAttack()[i]->getName()){
                            targetFound = true;
                            targetIndex = i;
                            break;
                        }
                    }

                    cout << "Territory not found." << endl;
                }

                cout << "How many army units do you want to move?" << endl;
                cin >> numArmies;

                cout << "An Advance Order of " << numArmies << " army units from " << sourceTerritory << " to " << targetTerritory <<  " will be issued." << endl;
                auto *advanceOrder = new Advance(this, territoryList[sourceIndex], territoryList[targetIndex], numArmies);
                ordersList->addList(advanceOrder);

            }
            else{
                cout << "Invalid choice. Please enter \"1\" to defend or \"2\" to attack." << endl;
            }
        }

        else{
            playerDone = true;
        }

    }

    int cardIndex;
    cout << "You can now play one card from your hand." << endl;
    cout << "Here are the cards in your hand: " << endl;
    for (int i = 0; i < hand->getCardNum(); i++){
        cout << i << "- " << hand->getCard(i).getTypeAsString() << endl;
    }

    cout << "Enter the index of the card you want to play"<< endl;
    cin >> cardIndex;

    hand->getCard(cardIndex).play(this, deck);
    
}
// tiffany