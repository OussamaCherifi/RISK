#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <map>
#include <iterator>
#include <stack>
#pragma once
#include "Player.h"

using namespace std;

class Territory {
    //declare variables
private:
    int *xCoordinate;
    int *yCoordinate;
    Player *player;
    string *territoryName;
    string *continent;

    int* numberOfArmies;

public:
    bool* visited;
    //delcare constructor with parameters and copy constructor
    Territory(string name, string cont, int x, int y);
    Territory(Territory *copy);

    //delcare getters
    int getxCoordinate() const;
    int getYCoordinate() const;
    Player getPlayer() const;
    string getContinent() const;
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

    vector<Territory *> *adjacentTerritories;
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
    void insertInStream();

    vector<Territory*>* territories;
};

class MapLoader {
public:
    bool createMapFromFile(string& fileName, Map* map2make);

};

std::string generateAbsolutePath(std::string mapName);


