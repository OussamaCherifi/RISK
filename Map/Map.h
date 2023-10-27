#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <map>
#include <iterator>
#include <stack>


using namespace std;

class Territory {
    //declare variables
private:
    int *xCoordinate;
    int *yCoordinate;
    string *player;
    string *territoryName;
    string *continent;
    bool* visited;
    int* numberOfArmies;

public:
    //delcare constructor with parameters and copy constructor
    Territory(string name, string cont, int x, int y);
    Territory(Territory *copy);

    //delcare getters
    int getxCoordinate() const;
    int getYCoordinate() const;
    string getPlayer() const;
    string getContinent() const;
    string getName() const;

    //declare setters
    void setXCoordinate(int *newX);
    void setYCoordinate(int *newY);
    void setPlayer(string *newName);

    vector<Territory *> *adjacentTerritories;

    void insertInStream();

    //declare destructor
    ~Territory();

    //declare add adjacent territory function
    void addAdjacent(Territory* neighbor);
};



class Map{
    //delcare constructors
public:
    Map();
    Map(const Map& copy);

    //declare methods
    bool validate();
    bool isTerritoryConnected();
    void insertInStream();

    vector<Territory*>* territories;
};

class MapLoader {
public:
    bool createMapFromFile(string& fileName, Map* mapToLoad);
};


