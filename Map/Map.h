#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <map>
#include <iterator>
#include <stack>
#include "Player.h"

using namespace std;

class Player;

class Territory {
    //declare variables
private:
    int *xCoordinate;
    int *yCoordinate;
    Player *player;
    string *territoryName;
    string *continent;
    bool visited;
    vector<Territory *> *adjacentTerritories;
    int* numberOfArmies;

public:
    //delcare constructor with parameters and copy constructor
    Territory(string name, string cont, int x, int y);
    Territory(Territory *copy);

    //delcare getters
    int getxCoordinate() const;
    int getYCoordinate() const;
    Player *getPlayer() const;
    string getContinent() const;
    bool getVisited() const;
    void setVisited(bool visited);
    vector<Territory *> *getAdjacentTerritories() const;
    string getName() const;

    //declare setters
    void setXCoordinate(int *newX);
    void setYCoordinate(int *newY);
    void setPlayer(Player* newPlayer);

    //army methods

    void addArmies(int num);
    void removeArmies(int num);
    void removeHalfArmies();
    void doubleArmies();
    void setArmies(int* newArmies);
    int getArmies() const;
    bool isAdjacentTo(Territory* otherTerritory);
    bool isAdjacentToOwnedTerritory(Player* player);
    void insertInStream();

    //declare destructor
    ~Territory();

    //declare add adjacent territory function
    void addAdjacent(Territory* neighbor);
};

void testLoadMaps();


class Map{
    //delcare constructors
public:
    Map();
    Map(const Map& copy);
    //declare methods
    bool validate();
    bool isMapConnected();
    map<string, int> getContinentNameAndNum();
    void insertInStream();

    vector<Territory*>* territories;
private:
    map<string, int> continentNameAndNum;
};

class MapLoader {
public:
    bool createMapFromFile(string& fileName, Map* map2make);

};

std::string generateAbsolutePath(std::string mapName);

#endif
