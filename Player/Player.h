#ifndef PLAYER_H
#define PLAYER_H
#include "Map.h";
#include "Cards.h";
#include "Orders.h";
#include<vector>

using namespace std;

//create players

class Player 
{ 
    private:
        vector<Territory*> territoryList;
        Hand *ptr_hand;
        OrdersList* ptr_ordersList;

    public:
        //constructors
        Player();
        Player(const Player &p);

        //assignment operator
        Player& operator= (const Player& p);

        //stream insertion operator
        friend ostream& operator<<(ostream& os, const Player& p);

        //getters
        vector<Territory*> getTerritoryList();
        Hand* getPtrHand();
        OrdersList* getPtrOrdersList();

        //add territories to the collection
        void addTerritory(Territory* t);

        vector<Territory*> toDefend();
        vector<Territory*> toAttack();
        void issueOrder();

};


#endif
