#ifndef ORDERS_H
#define ORDERS_H
#include <Vector>
#include <iostream>
#include "Map.h"
#include "Player.h"
#include "Cards.h"

using namespace std;

class Orders
{
public:
    Orders();
    virtual Orders *copy() const = 0;
    virtual void execute() = 0;
    virtual bool validate() = 0;
    virtual ostream &displayOrder(ostream &currentOrder) const = 0;
    virtual ~Orders() = default;
    string stringToLog();

private:
    friend ostream &operator<<(ostream &currentOrder, Orders &test);
};
class OrdersList
{
public:
    OrdersList();
    int getSize();
    void addList(Orders *something);
    void remove(int i);
    void move(int start, int end);
    string stringToLog();
    ostream &displayOrderList(ostream &myOrderList);
    OrdersList &operator=(const OrdersList &something);
    vector<Orders *> getListofOrders();
    ~OrdersList();
    // OrdersList::OrdersList(){};

private:
    std::vector<Orders *> listOfOrders;
    friend ostream &operator<<(ostream &myOrderList, OrdersList &something);
};

//Deploy,Advance, Bomb,Blockade,Airlift and Negotiate are all subclasses of Orders
class Deploy : public Orders
{
private:
    Territory* targetTerritory;
    int* numOfArmies;
    Player* playerDep;
public:
    int data;
    Deploy(Player* player, Territory* target, int armies);
    ~Deploy() override;
    Deploy *copy() const override;
    void execute() override;
    bool validate() override;
    ostream &displayOrder(ostream &currentOrder) const override;
    Deploy &operator=(const Deploy &something);
};

class Advance : public Orders
{
private:
    Player* playerAdv;
    Territory* sourceTerritory;
    Territory* targetTerritory;
    int* numOfArmies;
public:
    int data;
    Advance(Player* player, Territory* source, Territory* target, int armies);
    ~Advance() override;
    Advance *copy() const override;
    void execute() override;
    bool validate() override;
    ostream &displayOrder(ostream &currentOrder) const override;
    Advance &operator=(const Advance &something);
};
class Bomb : public Orders
{
private:
    Player* playerBom;
    Territory* targetTerritory;
public:
    int data;
    Bomb(Player* player, Territory* target);
    ~Bomb() override;
    Bomb *copy() const override;
    void execute() override;
    bool validate() override;
    ostream &displayOrder(ostream &currentOrder) const override;
    Bomb &operator=(const Bomb &something);
};

class Blockade : public Orders
{
private:
    Player* playerBlo;
    Territory* targetTerritory;
public:
    int data;
    Blockade(Player* player, Territory* target);
    ~Blockade() override;
    Blockade *copy() const override;
    void execute() override;
    bool validate() override;
    ostream &displayOrder(ostream &currentOrder) const override;
    Blockade &operator=(const Blockade &something);
};

class Airlift : public Orders
{
private:
    Player* playerAir;
    Territory* sourceT;
    Territory* targetT;
    int* numOfArmies;
public:
    int data;
    Airlift(Player* player, Territory* source, Territory* target, int armies);
    ~Airlift() override;
    Airlift *copy() const override;
    void execute() override;
    bool validate() override;
    ostream &displayOrder(ostream &currentOrder) const override;
    Airlift &operator=(const Airlift &something);
};

class Negotiate : public Orders
{
    Player* playerNeg;
    Player* targetP;
public:
    int data;
    Negotiate(Player* player, Player* target);
    ~Negotiate() override;
    Negotiate *copy() const override;
    void execute() override;
    bool validate() override;
    ostream &displayOrder(ostream &currentOrder) const override;
    Negotiate &operator=(const Negotiate &something);
};

#endif 