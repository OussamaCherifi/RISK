#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include "Player/Player.h"

class Player;

//The territory class represents a node in the graph
class Territory {

private:
    Player* owner;
    int numberOfArmies;
    int countryIndex;
    std::string name;
    int parent;

    int x;
    int y;

    std::vector<Territory*> adjacentCountries;

public:
    Territory();
    Territory(const Territory& t);
    Territory(Player* owner, int numberOfArmies, int countryIndex, const std::string& name, int parent, int x, int y);
    Territory(Player* owner, int numberOfArmies, int countryIndex, const std::string& name, int parent, const std::vector<Territory*>& adjacentCountries, int x, int y);
    Territory(int numberOfArmies, int countryIndex, const std::string& name, int parent, int x, int y);
    Territory(int countryIndex, const std::string& name, int parent, int x, int y);

    Territory& operator=(const Territory& t);

    friend std::ostream& operator<<(std::ostream& out, const Territory& t);

    bool operator==(const Territory& other) const;

    int getIndex() const;
    Player* getOwner() const;
    int getNumberOfArmies() const;
    const std::string& getName() const;
    int getContinent() const;
    const std::vector<Territory*>& getAdjacentTerritories() const;
    int getX() const;
    int getY() const;

    void setOwner(Player* player);
    void setNumberOfArmies(int numArmies);
    void setName(const std::string& newName);
    void setAdjacentTerritories(const std::vector<Territory*>& territories);
    void setX(int newX);
    void setY(int newY);

    void addAdjacentCountry(Territory* territory);
    bool isAdjacent(const Territory* territory) const;
};

class MapLoader {
public:
    static Map* createMapFromFile(const std::string& fileName);
};

//This class is used to represent a continent in Warzone, storing the details in the game's map file.
class Continent {

private:
    int continentIndex;
    int armies;
    std::string name;

public:
    Continent();
    Continent(int continentIndex, const std::string & name, int armies);
    Continent(const Continent& c);

    Continent& operator=(const Continent& c);

    friend std::ostream& operator<<(std::ostream& out, const Continent& c);

    int getIndex() const;
    int getArmies() const;
    const std::string& getName() const;
};

class Map {
private:
    std::vector<Continent*> continents;
    std::vector<Territory*> territories;
    std::vector<std::tuple<int, int>> borders;
    bool valid;

public:
    Map();
    Map(const Map& m);
    Map(const std::vector<Continent*>& continents, const std::vector<Territory*>& territories, const std::vector<std::tuple<int, int>>& borders);

    Map& operator=(const Map& m);

    friend std::ostream& operator<<(std::ostream& out, const Map& m);

    const std::vector<Continent*>& getContinents() const;
    const std::vector<Territory*>& getTerritories() const;
    const std::vector<std::tuple<int, int>>& getBorders() const;
    bool isValid() const;

    std::vector<std::tuple<int, int>> getBordersByCountry(const Territory& country) const;
    std::vector<Territory*> getTerritoriesByContinent(int continent) const;

    void setContinents(const std::vector<Continent*>& continents);
    void setTerritories(const std::vector<Territory*>& territories);
    void setBorders(const std::vector<std::tuple<int, int>>& borders);

    void addContinent(Continent* continent);
    void addTerritory(Territory* territory);
    void addBorder(const std::tuple<int, int>& border);

    bool borderExists(const std::vector<Territory*>& toCheck, const Territory& destination, std::vector<Territory>& checked) const;
    void validate();

    int calculateContinentBonus(Player* player) const;

    static bool territoryExists(const std::vector<Territory>& collection, const Territory& toFind);

    Territory* getTerritoryByIndex(int index);

    ~Map();
};

