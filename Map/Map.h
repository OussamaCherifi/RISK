#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include "Player\Player.h"



class Territory {
public:
    Territory(const std::string& name, const std::string& cont, int x, int y)
        : playerOwner(name), territoryName(name), continent(cont), xCoord(x), yCoord(y), visited(false) {
        neighbors = new std::vector<Territory*>;
        numArmies = new int;
        *numArmies = 0;
    }

    Territory(const Territory& copy) {
        playerOwner = copy.playerOwner;
        territoryName = copy.territoryName;
        continent = copy.continent;
        xCoord = copy.xCoord;
        yCoord = copy.yCoord;
        visited = copy.visited;
        neighbors = new std::vector<Territory*>(*copy.neighbors);
        numArmies = new int(*copy.numArmies);
    }

    ~Territory() {
        delete neighbors;
        delete numArmies;
    }

    int getXCoord() const { return xCoord; }
    int getYCoord() const { return yCoord; }
    void setXCoord(int newX) { xCoord = newX; }
    void setYCoord(int newY) { yCoord = newY; }
    const std::string& getPlayer() const { return *playerOwner; }
    void setPlayer(const std::string& newName) { *playerOwner = newName; }
    const std::string& getName() const { return *territoryName; }
    const std::string& getContinent() const { return *continent; }

    void addNeighbor(Territory* neighbor) {
        neighbors->push_back(neighbor);
    }

    void deleteVariables() {
        delete playerOwner;
        delete territoryName;
        delete continent;
    }

    void streamInsertion() {
        std::cout << "Territory name: " << *territoryName << "; Position: " << xCoord << ", " << yCoord
            << "; Continent " << *continent << ". Owned by: " << *playerOwner << ", with " << *numArmies
            << " armies." << std::endl;
    }

private:
    std::string* playerOwner;
    std::string* territoryName;
    std::string* continent;
    int xCoord;
    int yCoord;
    bool visited;
    std::vector<Territory*>* neighbors;
    int* numArmies;
};


class Map
{
private:
    std::string *pName; // name/title of a given map
public:
    Map();                                        // default constructor
    Map(const Map &orig);                         // Copy constructor
    virtual ~Map();                               // destructor
    std::vector<Continent *> Continents;          // Vector containing pointers to continents
    std::vector<Territory *> Territories;         // Vector containing pointers to territories
    bool validate();                              // method that validates a given map
    bool isMapConnected();                        // method that checks if a map is a connected graph
    void setName(std::string title);              // set the name of a given map
    std::string getName();                        // get the name of a given map
    Territory *getTerritoryById(int territoryID); // get a territory by id
   
};
