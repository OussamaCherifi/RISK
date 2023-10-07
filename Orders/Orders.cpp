#include "Orders.h"
#include <Vector>
#include <iostream>
using namespace std;

ostream &operator<<(ostream &myOrder, Orders &other);

void Deploy::execute()
{
    if (validate() == true)
    {
        cout << "Run Deploy";
    }
}
bool Deploy::validate() {}

void Advance::execute()
{
    if (validate())
    {
        cout << "Run Advance";
    }
}

bool Advance::validate()
{
    return true;
}

void Bomb::execute()
{
    if (validate())
    {
        cout << "Run Bomb";
    }
}

bool Bomb::validate()
{
    return true;
}

void Blockade::execute()
{
    if (validate())
    {
        cout << "Run Blockade";
    }
}

bool Blockade::validate()
{
    return true;
}

void Airlift::execute()
{
    if (validate())
    {
        cout << "Run Airlift";
    }
}

bool Airlift::validate()
{
    return true;
}

void Negotiate::execute()
{
    if (validate())
    {
        cout << "Run Negotiate";
    }
}

bool Negotiate::validate()
{
    return true;
}

//For OrdersList
void OrdersList::remove(int i) {
    int listSize = this->getSize();

    if (listSize == 0) {
        cout << "list is empty\n";
        return;
    }

    if (i < 0 || i >= listSize) {
        cout << "out of bounds\n";
        return;
    }

    auto myPtr = listOfOrders.begin();
    for (int j = 0; j < i; j++) {
        ++myPtr;
    }

    delete *myPtr;
    listOfOrders.erase(myPtr);
}
void::OrdersList::move(int start, int end){
    int listSize = this->getSize() - 1;
    if(start < 0 || start>= listSize || end < 0 || end>=listSize){
         cout<<"out of bounds";
         }
    else if(listSize==0){
        cout<<"error";
    }
    else{
        Orders* temp = listOfOrders[start];
        listOfOrders[start] = listOfOrders[end];
        listOfOrders[end] = temp;
    }
}
ostream& OrdersList::displayOrderList(ostream& myOrdersList) {
    myOrderList << "Orders List: \n";

    for (const Orders* order : listOfOrders) {
        myOrdersList << "- " << Orders.getName() << '\n';
    }
    return myOrdersList;
}



ostream& operator<<(ostream& myOrdersList, const OrdersList& otherList) {
    return otherList.displayOrderList(myOrdersList);
}
OrdersList& OrdersList::operator=(const OrdersList& otherCopy) {
    return *this;
}

