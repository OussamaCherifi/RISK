#include <vector>
#include "PlayerStrategies.h"
#include "Map.h"
#include "Orders.h"

using namespace std;

HumanPlayerStrategy::HumanPlayerStrategy(Player *player) {
    p = player;
}

vector<Territory *> HumanPlayerStrategy::toAttack() {
    vector<Territory *> attackList;

    for(Territory *t : p->getTerritoryList()){
        for(int i = 0; i < t->getAdjacentTerritories()->size(); i++) {
            Territory *adjacent = t->getAdjacentTerritories()->at(i);

            //check if player owns the territory, if yes break
            if (adjacent->getPlayer()->getID() == p->getID()) {
                continue;
            }
                //check if the territory is already in the attacklist, if yes break
            else {
                bool alreadyInList = false;
                for (Territory *terr: attackList) {
                    if (terr->getName() == adjacent->getName()) {
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

vector<Territory *> HumanPlayerStrategy::toDefend() {
    return p->getTerritoryList();
}

void HumanPlayerStrategy::issueOrder() {
    //deploy phase
    int territoryIndex, numUnits;

    int tempNum = *(p->getReinforcementPool());

    cout << "Let's start by deploying army units from your reinforcement pool. " << endl;

    while (tempNum > 0){
        cout << "You have " << tempNum << " army units in your reinforcement pool." << endl;

        //print the player's list of territories
        p->printTerritoryList();

        //get user input for which territory they want to deploy armies to
        cout << "Enter the index of territory you wish to deploy army units:";
        territoryIndex = p->getUserTerritoryIndex(toDefend());

        //get user input for num of armies to deploy
        numUnits = p->getUserNum(tempNum);

        tempNum -= numUnits;
        cout << "A Deploy Order of " <<  numUnits << " unit(s) to " << p->getTerritoryList()[territoryIndex]->getName() << " will be issued." << endl;
        auto *deployOrder = new Deploy(p, p->getTerritoryList()[territoryIndex], numUnits);
        p->getOrdersList()->addList(deployOrder);
    }

    cout << "\nGreat, all your reinforcement troops have been deployed." << endl;

    // advance phase
    cout << "Now let's issue Advance orders!" << endl;

    bool playerDone = false;

    while(!playerDone) {
        string playerInput;
        int playerChoice, sourceIndex, targetIndex;

        cout << "Do you wish to issue Advance orders? Enter \"YES\" or \"NO\"" << endl;
        cout << "Any other input would be considerd as \"NO\"" << endl;
        cin >> playerInput;

        if (playerInput == "YES") {
            cout << "Enter \"1\" to defend and \"2\" to attack" << endl;
            cin >> playerChoice;

            if (playerChoice == 1) {
                //print toDefend list
                p->printToDefend();

                //get user source territory
                cout << "Enter the index of the territory you want to move troops from";
                sourceIndex = p->getUserTerritoryIndex(toDefend());

                //get user target territory
                cout << "Enter the index of the territory you want to move troops to";
                targetIndex = p->getUserTerritoryIndex(toDefend());

                //get num of armies to move
                numUnits = p->getUserNum(toDefend()[sourceIndex]->getArmies());

                cout << "An Advance Order of " << numUnits << " army units from " << toDefend()[sourceIndex]->getName() << " to "
                     << toDefend()[targetIndex]->getName() << " will be issued." << endl;
                auto *advanceOrder = new Advance(p, p->toDefend()[sourceIndex], p->toDefend()[targetIndex], numUnits);
                p->getOrdersList()->addList(advanceOrder);

            } else if (playerChoice == 2) {
                p->printTerritoryList();
                p->printToAttack();

                cout << "Enter the index of the territory you want to move troops from";
                sourceIndex = p->getUserTerritoryIndex(toDefend());

                cout << "Enter the index of the territory you want to move troops to";
                targetIndex = p->getUserTerritoryIndex(toAttack());

                numUnits = p->getUserNum(toDefend()[sourceIndex]->getArmies());


                cout << "An Advance Order of " << numUnits << " army units from " << p->getTerritoryList()[sourceIndex]->getName()
                     << " to " << toAttack()[targetIndex]->getName() << " will be issued." << endl;
                auto *advanceOrder = new Advance(p, p->toDefend()[sourceIndex], p->toAttack()[targetIndex], numUnits);
                p->getOrdersList()->addList(advanceOrder);
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
    string cardInput;
    bool correctIndex = false;
    if(p->getHand()->getCardNum() == 0) cout << "You do not own any cards" << endl;
    else {
        //Print cards
        cout << "Here are the cards in your hand: " << endl;
        for (int i = 0; i < p->getHand()->getCardNum(); i++) {
            cout << i << "- " << p->getHand()->getCard(i).getTypeAsString() << endl;
        }

        cout << "Do you wish to play a card? Enter \"YES\" or \"NO\"" << endl;
        cout << "Any other input would be considerd as \"NO\"" << endl;
        cin >> cardInput;

        if (cardInput == "YES") {
            while(!correctIndex){
                cout << "Enter the index of the player you want to negotiate with:";
                cin >> cardIndex;

                if (cardIndex >= 0 && cardIndex <= p->getHand()->getCardNum())
                    correctIndex = true;
                else {
                    cout << "Invalid index. Please enter another number." << endl;
                }
            }

            p->getHand()->getCard(cardIndex).play(p, p->getDeck());
            p->getDeck()->addCard(p->getHand()->getCard(cardIndex)); //puts it back to the deck
            p->getHand()->removeCard(cardIndex); //removes it from player's hand
        }

    }
}

string HumanPlayerStrategy::getType() {
    return "HUMAN";
}

NeutralPlayerStrategy::NeutralPlayerStrategy(Player *player) {
    p = player;
}

vector<Territory *> NeutralPlayerStrategy::toAttack() {
    vector<Territory *> attacklist;
    return attacklist; //returns an empty list since cannot attack
}

vector<Territory *> NeutralPlayerStrategy::toDefend() {
    return p->getTerritoryList();
}

void NeutralPlayerStrategy::issueOrder() {
    cout << "Neutral players do not issue orders or play cards" << endl;
}

string NeutralPlayerStrategy::getType() {
    return "NEUTRAL";
}