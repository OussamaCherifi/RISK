#include "Player.h";

#include<iostream>
#include<vector>

using namespace std;

void testPlayers(){
    Player *p1 = new Player();

    //create territory objects with the imoplementation of Territory and addTerritory() to each player

    //use stream insertion to show that a player has list of territories, hand of cards, orders list

    // print the territories to attack and defend
    p1->toAttack();
    p1->toDefend();

    //issueOrder(), use stream insertion to show that an order was placed in the player's orderslist

    //


}