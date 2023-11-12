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
Deploy::Deploy(Player* player, Territory *target, int armies) : targetTerritory(target), numOfArmies(new int(armies)){}
Deploy *Deploy::copy() const { return new Deploy(*this); }
void Deploy::execute()
{
    if (validate())
    {
        targetTerritory->addArmies(*numOfArmies);
        Notify(this);
    }
}
bool Deploy::validate() {
    if (targetTerritory->getPlayer() == *player){
    return true;
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
Advance *Advance::copy() const { return new Advance(*this); }
void Advance::execute()
{
    if (validate())
    {
        Notify(this);
    }
}
bool Advance::validate() {return true;}
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
Bomb *Bomb::copy() const { return new Bomb(*this); }
void Bomb::execute()
{
    if (validate())
    {
        Notify(this);
    }
}
bool Bomb::validate() {return true;}
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
Blockade *Blockade::copy() const { return new Blockade(*this); }
void Blockade::execute()
{
    if (validate())
    {
        Notify(this);
    }
}
bool Blockade::validate() {return true;}
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
Airlift *Airlift::copy() const { return new Airlift(*this); }
void Airlift::execute()
{
    if (validate())
    {
        Notify(this);
    }
}
bool Airlift::validate() {return true;}
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
Negotiate *Negotiate::copy() const { return new Negotiate(*this); }
void Negotiate::execute()
{
    if (validate())
    {
        Notify(this);
    }
}
bool Negotiate::validate() {
    if()
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