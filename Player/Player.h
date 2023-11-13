#ifndef PLAYER_H
#define PLAYER_H
#include "Map.h"
#include "Cards.h"
#include "Orders.h"
#include<vector>
#include <set>

using namespace std; 

//create players
class Player 
{ 
    private:
        static int* nextID;
        int id;
        vector<Territory*> territoryList;
        Hand *hand;
        OrdersList* ordersList;
        int *reinforcementPool;
        set<Player* > diplomaticRelations;
        Deck deck;
    public:
        //constructors
        Player() : id(*nextID++) {};
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
        Deck& getDeck();

        //setters
        void setReinforcementPool(int *num);

        //add territories to the collection
        void addTerritory(Territory* t);

        vector<Territory*> toDefend();
        vector<Territory*> toAttack();
        void issueOrder();

        // create diplomatic relation
        void addDiplomaticRelation(Player* player1);
        bool isDiplomaticRelation(Player attacker) const;

        //comparators to make sure players are the same
        bool operator==(const Player& other) const;
        bool operator!=(const Player& other) const;

};

void testPlayers();


#endif
