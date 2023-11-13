#include "Player.h"
#include "Map.h"
#include <algorithm>
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
    string territoryName;
    int territoryIndex, numUnits;
    bool territoryFound = false, correctNum = false;

    cout << "Let's start by deploying army units from your reinforcement pool. " << endl;

    while (*getReinforcementPool() > 0){
            cout << "You have " << reinforcementPool << " army units in your reinforcement pool." << endl;

            cout << "Here are your territories to defend: " << endl;
            for (Territory *t : toDefend()){
                cout << " - " << t->getName() << endl;
            }

            while(!territoryFound){
                cout << "Enter the name of territory you wish to deploy army units: ";
                cin >> territoryName;

                for(int i = 0; i < territoryList.size(); i++){

                    if (territoryName == territoryList[i]->getName()){
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

                if (numUnits > 0 && numUnits <= *reinforcementPool)
                    correctNum = true;

                cout << "Invalid number. Please enter another number." << endl; 
            }

            cout << "A Deploy Order of " <<  numUnits << " units to " << territoryName << " will be issued." << endl;
            auto *deployOrder = new Deploy(this, territoryList[territoryIndex], numUnits);
            ordersList->addList(deployOrder);

    }

    cout << "Now let's issue Advance orders!" << endl;
    string playerInput, dSourceTerritory, dTargetTerritory;
    int playerChoice, dSourceIndex, dTargetIndex, numArmies;
    bool playerDone = false, defenseDone = false, attackDone = false, validNumChoice = false;

    while(!playerDone){
        cout << "Do you wish to issue Advance orders? Enter \"YES\" or \"NO\"" << endl;
        cout << "Any other input would be considerd as \"NO\"" << endl;
        cin >> playerInput;

        if(playerInput == "YES"){
            cout << "Enter \"1\" to defend and \"2\" to attack" << endl;
            cin >> playerChoice;

            if(playerChoice == 1){
                bool defenseSourceFound = false, defenseTargetFound = false;
                cout << "Here are your territories to defend: " << endl;
                for (Territory *t : toDefend()){
                    cout << " - " << t->getName() << endl;
                }

                while(!defenseSourceFound){
                cout << "Enter the name of the territory you want to move troops from";
                cin >> dSourceTerritory;

                for(int i = 0; i < territoryList.size(); i++){

                    if (dSourceTerritory == territoryList[i]->getName()){
                        defenseSourceFound = true;
                        dSourceIndex = i;
                        break;
                    }
                }
                cout << "Territory not found. Please re-enter the territory name." << endl;
                }

                while(!defenseTargetFound){
                    cout << "Enter the name of the territory you want to move troops to";
                    cin >> dTargetTerritory;

                    for(int i = 0; i < territoryList.size(); i++){

                        if (dTargetTerritory == territoryList[i]->getName()){
                            defenseTargetFound = true;
                            dTargetIndex = i;
                            break;
                        }
                    }
                }

                cout << "How many army units do you want to move?" << endl;
                cin >> numArmies;

                cout << "An Advance Order of " << numArmies << " army units from " << dSourceTerritory << " to " << dTargetTerritory <<  " will be issued." << endl;
                auto *advanceOrder = new Advance(this, territoryList[dSourceIndex], territoryList[dTargetIndex], numArmies);
                ordersList->addList(advanceOrder);
            }

            else if (playerChoice == 2) {
                cout << "Here are your territories to attack: " << endl;
                for (Territory *t : toAttack()){
                    cout << " - " << t->getName() << endl; 
                }
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