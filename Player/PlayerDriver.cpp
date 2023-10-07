#include "Player.h"

#include<iostream>
#include<vector>

using namespace std;

void testPlayers(){
    cout << "Testing Players";

    Player *p1 = new Player();

    //create territory objects with the imoplementation of Territory and addTerritory() to each player

    //arbitrary territories
    Territory* t1 = new Territory(0, "Canada", 2, 1, 1);
    Territory* t2 = new Territory(1, "US", 3, 2, 2);

    p1->addTerritory(t1);
    p1->addTerritory(t2);

    //use stream insertion to show that a player has list of territories, hand of cards, orders list
    cout << p1;

    // print the territories to attack and defend
    cout << "Territories to defend: ";

    vector<Territory*> attackList = p1->toAttack();
    for(Territory* t : attackList){
        cout << *t;
    }
    
    vector<Territory*> defendList = p1->toDefend();
    for(Territory* t : defendList){
        cout << *t;
    }

    p1->issueOrder();
    //output player to show that there is an order in the player's orderslist
    cout << p1;

    cout << "\n End of Testing Players";


}