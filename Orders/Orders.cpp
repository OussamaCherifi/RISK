#include "Orders.h"
#include "LoggingObserver.h"
#include <Vector>
#include <iostream>
#include <sstream>
using namespace std;
// Assignment 2, Part 5 - Zack
// Create log string
string Orders::stringToLog() {
    ostringstream oss;
    oss << "[Order]\t\tExecuted " << *this << " order";
    return oss.str();
}


ostream &operator<<(ostream &myOrder, Orders &something){
    return something.displayOrder(myOrder);
}

string OrdersList::stringToLog() {
    ostringstream oss;
    oss << "[OrdersList]\tAdded " << *listOfOrders.back() << " order";
    return oss.str();
}

int OrdersList::getSize()
{
    return listOfOrders.size();
}
void OrdersList::addList(Orders *O)
{
    listOfOrders.push_back(O);
    Notify(this);
}


vector<Orders *> OrdersList::getListOfOrders() {
    return listOfOrders;
}

void OrdersList::remove(int i)
{
    int sizeList = this->getSize();

    if (sizeList == 0)
    {
        cout << "list is empty\n";
        return;
    }

    if (i < 0 || i >= sizeList)
    {
        cout << "out of bounds\n";
        return;
    }

    auto thisPointer = listOfOrders.begin();
    for (int j = 0; j < i; j++)
    {
        ++thisPointer;
    }

    delete *thisPointer;
    listOfOrders.erase(thisPointer);
}
void::OrdersList::move(int start, int end)
{
    int sizeList = this->getSize() - 1;
    if (start < 0 || start >= sizeList || end < 0 || end >= sizeList)
    {
        cout << "out of bounds";
    }
    else if (sizeList == 0)
    {
        cout << "error";
    }
    else
    {
        Orders *temp = listOfOrders[start];
        listOfOrders[start] = listOfOrders[end];
        listOfOrders[end] = temp;
    }
}

void OrdersList::clearList() {
    for (Orders *order : listOfOrders) {
        delete order;
    }
    listOfOrders.clear();
}

ostream &OrdersList::displayOrderList(ostream &myOrderList)
{
    myOrderList << "Orders List: \n";

    for (Orders *orderObject : listOfOrders)
    {
        myOrderList << "/" << *orderObject << '\n';
    }
    return myOrderList;
}

ostream &operator<<(ostream &myOrderList, OrdersList &aList)
{
    return aList.displayOrderList(myOrderList);
}
OrdersList &OrdersList::operator=(const OrdersList &somethingCopy)
{
    return *this;
}


// Deploy constructors, destructor and methods
Deploy::Deploy(Player* player, Territory *target, int armies) : playerDep(player), targetTerritory(target), numOfArmies(new int(armies)){}
Deploy *Deploy::copy() const { return new Deploy(*this); }
void Deploy::execute()
{
    if (validate())
    {
        cout << "Executing Deploy order: " << endl;
        int numofReinforcements= *(playerDep->getReinforcementPool());
        targetTerritory->addArmies(*numOfArmies);
        playerDep->setReinforcementPool(new int(numofReinforcements - *numOfArmies));
        Notify(this);
        cout<<"Deploy done: Armies left :"<<*playerDep->getReinforcementPool()<<endl;
    }
    else{
        cout<<"Could not execute order Deploy"<<endl;
    }
}
bool Deploy::validate() {
    if (targetTerritory->getPlayer()->getID() == playerDep->getID()){
        if(*numOfArmies <= *(playerDep->getReinforcementPool())){
            return true;
        }
        else
            return false;
    }
    else{
        return false;
    }
}
Deploy &Deploy::operator=(const Deploy &something) {
    if (this != &something) {this->data = something.data;}
    return *this;
}

ostream &Deploy::displayOrder(ostream &myOrder) const
{
    myOrder << "Deploy";
    return myOrder;
}

// Advance
Advance::Advance(Player* player, Territory* source, Territory* target, int armies)
        : playerAdv(player), sourceTerritory(source), targetTerritory(target), numOfArmies(new int(armies)) {}
Advance *Advance::copy() const { return new Advance(*this); }
void Advance::execute()
{
    if (validate())
    {
        cout << "Executing Advance order: " << endl;
        if(targetTerritory->getPlayer()->getID()==playerAdv->getID()){
            sourceTerritory->removeArmies(*numOfArmies);
            targetTerritory->addArmies(*numOfArmies);
            cout<<"Advance successful from " << sourceTerritory->getName() << " to " << targetTerritory->getName() <<endl;
        }
        else{
            if (playerAdv->isDiplomaticRelation(targetTerritory->getPlayer())){
                cout<<"Cannot attack this turn, diplomatic relations"<<endl;
            }
            else {
                int attackingArmies = *numOfArmies;
                int defendingArmies = targetTerritory->getArmies();

                cout << sourceTerritory->getName() << " is attacking " << targetTerritory->getName() << endl;

                while (attackingArmies > 0 && defendingArmies > 0) {
                    // Battle simulation
                    for (int i = 0; i < attackingArmies; ++i) {
                        if (rand() % 100 < 60) {
                            // Attacker kills one defending army
                            --defendingArmies;
                        }
                    }

                    for (int i = 0; i < defendingArmies; ++i) {
                        if (rand() % 100 < 70) {
                            // Defender kills one attacking army
                            --attackingArmies;
                        }
                    }
                }

                // Check if the attacker conquered the territory
                if (defendingArmies <= 0) {
                    // Attacker captures the territory
                    targetTerritory->getPlayer()->removeTerritory(targetTerritory); // remove the territory from the attackee
                    targetTerritory->setPlayer(playerAdv); //set the player in the territory
                    playerAdv->addTerritory(targetTerritory); //add this territory to the new player's list
                    targetTerritory->setArmies(new int(attackingArmies));
                    cout << targetTerritory->getName() << " is conquered by " << playerAdv->getPlayerName() << endl;

                    // Player receives a card for conquering a territory
                    if (playerAdv && playerAdv->getHand() && playerAdv->getDeck()) {
                        playerAdv->getHand()->addCard((playerAdv->getDeck())->draw());
                        cout << "Player received a card;" << endl;
                    }
                    else{
                        cout<<"Error with pointer"<<endl;
                    }
                } else {
                    // Attacker did not conquer the territory
                    targetTerritory->setArmies(&defendingArmies);
                    cout << "Attacker did not conquer territory" << endl;
                }
            }
        }
        Notify(this);
    }
    else{
        cout<<"Could not execute order Advance"<<endl;
    }
}
bool Advance::validate() {
    if (sourceTerritory->getPlayer()->getID() == playerAdv->getID()){
        if (sourceTerritory->isAdjacentTo(targetTerritory)){
            return true;
        }
        else{
            cout << "Error: territories are not adjacent" << endl;
            return false;
        }
    }
    else {
        cout << "Error: territory is not yours" << endl;
        return false;
    }
}
Advance &Advance::operator=(const Advance &something) {
    if (this != &something) {this->data = something.data;}
    return *this;
}
ostream &Advance::displayOrder(ostream &myOrder) const
{
    myOrder << "Advance";
    return myOrder;
}

// Bomb
Bomb::Bomb(Player* player, Territory* target) : playerBom(player), targetTerritory(target) {}
Bomb *Bomb::copy() const { return new Bomb(*this); }
void Bomb::execute()
{
    if (validate())
    {
        cout << "Executing Bomb order: " << endl;
        targetTerritory->removeHalfArmies();
        cout << targetTerritory->getName() << " has been bombed!"<<endl;
        Notify(this);
    }
    else{
        cout<<"Could not execute order Bomb"<<endl;
    }
}
bool Bomb::validate() {
    if(targetTerritory->getPlayer()->getID() != playerBom->getID() && targetTerritory->isAdjacentToOwnedTerritory(playerBom)){
        return true;
    }
    else
        return false;
}
Bomb &Bomb::operator=(const Bomb &something) {
    if (this != &something) {this->data = something.data;}
    return *this;
}
ostream &Bomb::displayOrder(ostream &myOrder) const
{
    myOrder << "Bomb";
    return myOrder;
}

// Blockade
Blockade::Blockade(Player* player, Territory* target) : playerBlo(player), targetTerritory(target) {}
Blockade *Blockade::copy() const { return new Blockade(*this); }
void Blockade::execute()
{
    if (validate())
    {
        cout << "Executing Blockade order: " << endl;
        targetTerritory->doubleArmies();
        //give the ownership of territory to the neutral player
        Notify(this);
        cout<<"A Blockade has been put on " << targetTerritory->getName() << endl;
    }
    else{
        cout<<"Could not execute order Blockade"<<endl;
    }
}
bool Blockade::validate() {
    if(targetTerritory->getPlayer()->getID() == playerBlo->getID()){
        return true;
    }
    else{
        return false;
    }
}
Blockade &Blockade::operator=(const Blockade &something) {
    if (this != &something) {this->data = something.data;}
    return *this;
}
ostream &Blockade::displayOrder(ostream &myOrder) const
{
    myOrder << "Blockade";
    return myOrder;
}

// Airlift
Airlift::Airlift(Player* player, Territory* source, Territory* target, int armies)
        : playerAir(player), sourceT(source), targetT(target), numOfArmies(new int(armies)) {}
Airlift *Airlift::copy() const { return new Airlift(*this); }
void Airlift::execute()
{
    if (validate())
    {
        cout << "Executing Airlift order: " << endl;
        sourceT->removeArmies(*numOfArmies);
        targetT->addArmies(*numOfArmies);
        cout<<"Airlift Successful from " << sourceT->getName() << " to " << targetT->getName() <<endl;
        Notify(this);
    }
    else{
        cout<<"Could not execute order Airlift"<<endl;
    }
}
bool Airlift::validate() {
    if (sourceT->getPlayer()->getID() == playerAir->getID() && targetT->getPlayer()->getID() == playerAir->getID()) {
        return true;
    }
    else
        return false;
}
Airlift &Airlift::operator=(const Airlift &something) {
    if (this != &something) {this->data = something.data;}
    return *this;
}
ostream &Airlift::displayOrder(ostream &myOrder) const
{
    myOrder << "Airlift";
    return myOrder;
}

// Negotiate
Negotiate::Negotiate(Player* player, Player* target) : playerNeg(player), targetP(target) {}
Negotiate *Negotiate::copy() const { return new Negotiate(*this); }
void Negotiate::execute()
{
    if (validate())
    {
        cout << "Executing Negotiate order: " << endl;
        playerNeg->addDiplomaticRelation(targetP);
        targetP->addDiplomaticRelation(playerNeg);
        cout<<"Negotiation successful"<<endl;
        Notify(this);
    }
    else{
        cout<<"Could not execute order"<<endl;
    }
}
bool Negotiate::validate() {
    if(*targetP == *playerNeg){
        return false;
    }
    else{
        return true;
    }
}
Negotiate &Negotiate::operator=(const Negotiate &something) {
    if (this != &something) {this->data = something.data;}
    return *this;
}
ostream &Negotiate::displayOrder(ostream &myOrder) const
{
    myOrder << "Negotiate";
    return myOrder;
}