#ifndef ORDERS_H
#define ORDERS_H
#include <vector>
#include <iostream>
#include "Map.h"
#include "Cards.h"
#include "LoggingObserver.h"
#include "Player.h"

using namespace std;

class Territory;

class Player;

class Orders : public Subject, public ILoggable {
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

class OrdersList : public Subject, public ILoggable {
public:
    OrdersList() = default;
    int getSize();
    void addList(Orders *something);
    void remove(int i);
    void move(int start, int end);

    string stringToLog() override;
    ostream &displayOrderList(ostream &myOrderList);
    OrdersList &operator=(const OrdersList &something);

    vector<Orders *> getListOfOrders();

    ~OrdersList() override = default;
    // OrdersList::OrdersList(){};

private:
    std::vector<Orders *> listOfOrders;
    friend ostream &operator<<(ostream &myOrderList, OrdersList &something);
};

//Deploy,Advance, Bomb,Blockade,Airlift and Negotiate are all subclasses of Orders
class Deploy : public Orders
{
private:
    Territory *targetTerritory;
    int *numOfArmies;
    Player *playerDep;
public:
    int data;

    Deploy(Player *player, Territory *target, int armies);

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
private:
    Player *playerAdv;
    Territory *sourceTerritory;
    Territory *targetTerritory;
    int *numOfArmies;
public:
    int data;

    Advance(Player *player, Territory *source, Territory *target, int armies);

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
private:
    Player *playerBom;
    Territory *targetTerritory;
public:
    int data;

    Bomb(Player *player, Territory *target);

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
private:
    Player *playerBlo;
    Territory *targetTerritory;
public:
    int data;

    Blockade(Player *player, Territory *target);

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
private:
    Player *playerAir;
    Territory *sourceT;
    Territory *targetT;
    int *numOfArmies;
public:
    int data;

    Airlift(Player *player, Territory *source, Territory *target, int armies);

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
private:
    Player *playerNeg;
    Player *targetP;
public:
    int data;

    Negotiate(Player *player, Player *target);

    Negotiate() = default;

    ~Negotiate() override = default;
    Negotiate *copy() const override;
    void execute() override;
    bool validate() override;
    ostream &displayOrder(ostream &currentOrder) const override;
    Negotiate &operator=(const Negotiate &something);
};

#endif 