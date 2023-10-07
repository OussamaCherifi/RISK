#include "Orders.h"
#include <Vector>
#include <iostream>
using namespace std;

ostream &operator<<(ostream &myOrder, Orders &something);
Orders::Orders() {}

// For OrdersList
OrdersList::OrdersList() {}
OrdersList::~OrdersList() {}

void OrdersList::addList(Orders *O)
{
    listOfOrders.push_back(O);
}
int OrdersList::getSize()
{
    return listOfOrders.size();
}
void OrdersList::remove(int i)
{
    int listSize = this->getSize();

    if (listSize == 0)
    {
        cout << "list is empty\n";
        return;
    }

    if (i < 0 || i >= listSize)
    {
        cout << "out of bounds\n";
        return;
    }

    auto myPtr = listOfOrders.begin();
    for (int j = 0; j < i; j++)
    {
        ++myPtr;
    }

    delete *myPtr;
    listOfOrders.erase(myPtr);
}
void ::OrdersList::move(int start, int end)
{
    int listSize = this->getSize() - 1;
    if (start < 0 || start >= listSize || end < 0 || end >= listSize)
    {
        cout << "out of bounds";
    }
    else if (listSize == 0)
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
    cout << "inside display orderslist";
}

ostream &operator<<(ostream &myOrderList, OrdersList &aList)
{
    return aList.displayOrderList(myOrderList);
    cout << "inside operator";
}
OrdersList &OrdersList::operator=(const OrdersList &somethingCopy)
{
    return *this;
}


// Deploy constructors, destructor and methods
Deploy::Deploy() {}
Deploy::~Deploy() {}
Deploy *Deploy::copy() const { return new Deploy(*this); }
void Deploy::execute()
{
    if (validate() == true)
    {
        cout << "validate Deploy";
    }
}
bool Deploy::validate() {}
Deploy &Deploy::operator=(const Deploy &something) {
    if (this != &something) {this->data = something.data;}
    return *this;
}

ostream &Deploy::displayOrder(ostream &myOrder) const
{
    myOrder << "running deploy";
    return myOrder;
}

// Advance
Advance::Advance() {}
Advance::~Advance() {}
Advance *Advance::copy() const { return new Advance(*this); }
void Advance::execute()
{
    if (validate() == true)
    {
        cout << "validate Advance";
    }
}
bool Advance::validate() {}
Advance &Advance::operator=(const Advance &something) {
    if (this != &something) {this->data = something.data;}
    return *this;
    }
ostream &Advance::displayOrder(ostream &myOrder) const
{
    myOrder << "running advance";
    return myOrder;
}

// Bomb
Bomb::Bomb() {}
Bomb::~Bomb() {}
Bomb *Bomb::copy() const { return new Bomb(*this); }
void Bomb::execute()
{
    if (validate() == true)
    {
        cout << "validate Bomb";
    }
}
bool Bomb::validate() {}
Bomb &Bomb::operator=(const Bomb &something) { 
    if (this != &something) {this->data = something.data;}
    return *this;
}
ostream &Bomb::displayOrder(ostream &myOrder) const
{
    myOrder << "running Bomb";
    return myOrder;
}

// Blockade
Blockade::Blockade() {}
Blockade::~Blockade() {}
Blockade *Blockade::copy() const { return new Blockade(*this); }
void Blockade::execute()
{
    if (validate() == true)
    {
        cout << "validate Blockade";
    }
}
bool Blockade::validate() {}
Blockade &Blockade::operator=(const Blockade &something) { 
    if (this != &something) {this->data = something.data;}
    return *this;
}
ostream &Blockade::displayOrder(ostream &myOrder) const
{
    myOrder << "running Blockade";
    return myOrder;
}

// Airlift
Airlift::Airlift() {}
Airlift::~Airlift() {}
Airlift *Airlift::copy() const { return new Airlift(*this); }
void Airlift::execute()
{
    if (validate() == true)
    {
        cout << "validate Airlift";
    }
}
bool Airlift::validate() {}
Airlift &Airlift::operator=(const Airlift &something) {
    if (this != &something) {this->data = something.data;}
    return *this;
}
ostream &Airlift::displayOrder(ostream &myOrder) const
{
    myOrder << "running Airlift";
    return myOrder;
}

// Negotiate
Negotiate::Negotiate() {}
Negotiate::~Negotiate() {}
Negotiate *Negotiate::copy() const { return new Negotiate(*this); }
void Negotiate::execute()
{
    if (validate() == true)
    {
        cout << "validate Negotiate";
    }
}
bool Negotiate::validate() {}
Negotiate &Negotiate::operator=(const Negotiate &something) { 
    if (this != &something) {this->data = something.data;}
    return *this;
 }
ostream &Negotiate::displayOrder(ostream &myOrder) const
{
    myOrder << "running Negotiate";
    return myOrder;
}