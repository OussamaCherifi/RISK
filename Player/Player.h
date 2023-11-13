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
        string playerName;
        int *reinforcementPool;

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
//        vector<Territory*> getTerritoryList();
        vector<Territory*>& getTerritoryList();
        string getPlayerName(); // New getter for playerName
        Hand *getHand();
        OrdersList *getOrdersList();
        int *getReinforcementPool();

        //add territories to the collection
        void addTerritory(Territory* t);

        vector<Territory*> toDefend();
        vector<Territory*> toAttack();
        void issueOrder();


    // setters
    void setName(const std::string& newName);
    void setReinforcementPool(int *num);


};

void testPlayers();


#endif
