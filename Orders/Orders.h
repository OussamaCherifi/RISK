#ifndef ORDERS_H
#define ORDERS_H
#include <Vector>
#include <iostream>
#include "LoggingObserver.h"
using namespace std;

class Orders : public Subject, public ILoggable
{
public:
    Orders() = default;
    ~Orders() override = default;
    virtual Orders *copy() const = 0;
    virtual void execute() = 0;
    virtual bool validate() = 0;
    virtual ostream &displayOrder(ostream &currentOrder) const = 0;

    // Assignment 2, Part 5 - Zack
    string stringToLog() override;


private:
    friend ostream &operator<<(ostream &currentOrder, Orders &test);
};

class OrdersList : public Subject, public ILoggable
{
public:
    OrdersList() = default;
    ~OrdersList() override = default;
    int getSize();
    void addList(Orders *something);
    void remove(int i);
    void move(int start, int end);
    ostream &displayOrderList(ostream &myOrderList);
    OrdersList &operator=(const OrdersList &something);
    vector<Orders *> getListOfOrders();

    // Assignment 2, Part 5 - Zack
    string stringToLog() override;

private:
    std::vector<Orders *> listOfOrders;
    friend ostream &operator<<(ostream &myOrderList, OrdersList &something);
};

//Deploy,Advance, Bomb,Blockade,Airlift and Negotiate are all subclasses of Orders
class Deploy : public Orders
{
public:
    int data;
    Deploy() = default;
    ~Deploy() override = default;
    Deploy *copy() const override;
    void execute() override;
    bool validate() override;
    ostream &displayOrder(ostream &currentOrder) const override;
    Deploy &operator=(const Deploy &something);
};

class Advance : public Orders
{
public:
    int data;
    Advance() = default;
    ~Advance() override = default;
    Advance *copy() const override;
    void execute() override;
    bool validate() override;
    ostream &displayOrder(ostream &currentOrder) const override;
    Advance &operator=(const Advance &something);
};
class Bomb : public Orders
{
public:
    int data;
    Bomb() = default;
    ~Bomb() override = default;
    Bomb *copy() const override;
    void execute() override;
    bool validate() override;
    ostream &displayOrder(ostream &currentOrder) const override;
    Bomb &operator=(const Bomb &something);
};

class Blockade : public Orders
{
public:
    int data;
    Blockade() = default;
    ~Blockade() override = default;
    Blockade *copy() const override;
    void execute() override;
    bool validate() override;
    ostream &displayOrder(ostream &currentOrder) const override;
    Blockade &operator=(const Blockade &something);
};

class Airlift : public Orders
{
public:
    int data;
    Airlift() = default;
    ~Airlift() override = default;
    Airlift *copy() const override;
    void execute() override;
    bool validate() override;
    ostream &displayOrder(ostream &currentOrder) const override;
    Airlift &operator=(const Airlift &something);
};

class Negotiate : public Orders
{
public:
    int data;
    Negotiate() = default;
    ~Negotiate() override = default;
    Negotiate *copy() const override;
    void execute() override;
    bool validate() override;
    ostream &displayOrder(ostream &currentOrder) const override;
    Negotiate &operator=(const Negotiate &something);
};

void testOrdersLists();

#endif 