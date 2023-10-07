#ifndef PLAYER_H
#define PLAYER_H
#include "Map\Map.h"
#include "Cards\Cards.h"
#include "Orders\Orders.h"
#include<vector>


//create players
class Player 
{ 
    private:
        vector<Territory*> territoryList;
        Hand *hand;
        OrdersList* ordersList;

    public:
        //constructors
        Player();
        Player(const Player &p);

        //destructor
        ~Player();

        //assignment operator
        Player& operator= (const Player& p);

        //stream insertion operator
        friend std::ostream &operator<<(std::ostream &out, const Player &p);

        //getters
        vector<Territory*> getTerritoryList();
        Hand* getHand();
        OrdersList* getOrdersList();

        //add territories to the collection
        void addTerritory(Territory* t);

        vector<Territory*> toDefend();
        vector<Territory*> toAttack();
        void issueOrder();
};

void testPlayers();


#endif
