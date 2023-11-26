#ifndef PLAYER_H
#define PLAYER_H
#include<vector>
#include <set>
#include "Cards.h"
#include "Map.h"
#include "Orders.h"

using namespace std;

class Territory;

class Map;

class Hand;

class OrdersList;

class Deck;

//create players
class Player 
{ 
    private:
        static int* nextID;
        int id;
        vector<Territory*> territoryList;
        Hand *hand;
        OrdersList* ordersList;
        string playerName;
        int *reinforcementPool;
        set<Player* > diplomaticRelations;
        Deck *deck;
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
        Deck *getDeck();
        int getID();

        //setters
        void setReinforcementPool(int *num);
        void setID(int num);
        void setDeck(Deck deck);
        //add territories to the collection
        void addTerritory(Territory* t);
        void removeTerritory(Territory *t);

        vector<Territory*> toDefend();
        vector<Territory*> toAttack();
        void printTerritoryList();
        void printToDefend();
        void printToAttack();
        static int getUserNum(int max);
        int getUserTerritoryIndex(vector<Territory *> list);
        void issueOrder();

        //calculate if the player should get bonus reinforcement for owning continents
        int calculateContinentBonus(Map *mapCreated);

        // create diplomatic relation
        void addDiplomaticRelation(Player* player1);
        bool isDiplomaticRelation(Player* attacker) const;

        //comparators to make sure players are the same
        bool operator==(const Player& other) const;
        bool operator!=(const Player& other) const;

        // setters
        void setName(const std::string& newName);
};

void testPlayers();


#endif
