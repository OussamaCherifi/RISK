#ifndef PLAYER_H
#define PLAYER_H
#include "Map.h"
#include "Cards.h"
#include "Orders.h"
#include<vector>

using namespace std; 

//create players
class Player 
{ 
    private:
        vector<Territory*> territoryList;
        Hand *hand;
        OrdersList* ordersList;
        int *reinforcementPool;
        vector<Player*> diplomaticRelations;
    public:
        //constructors
        Player();
        Player(const Player &p);

        //destructor
        ~Player();

        //assignment operator
        Player& operator= (const Player& p);

        //stream insertion operator
        friend ostream &operator<<(ostream &out, const Player &p);

        //getters
        vector<Territory*> getTerritoryList();
        Hand *getHand();
        OrdersList *getOrdersList();
        int *getReinforcementPool();

        //setters
        void setReinforcementPool(int *num);

        //add territories to the collection
        void addTerritory(Territory* t);

        vector<Territory*> toDefend();
        vector<Territory*> toAttack();
        void issueOrder();
        // create diplomatic relation

        void addDiplomaticRelation(Player* player);
        bool canAttack(Player* target) const;
};

void testPlayers();


#endif
