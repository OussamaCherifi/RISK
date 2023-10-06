#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <exception>
#include "Map.h"

using namespace std;

class Continent
{
private:
    int continentIndex;
    int armies;
    string name;

public:
    // Default constructor
    Continent() : continentIndex(0), armies(0), name("") {}

    // constructor with parameters
    Continent(int index, const string &continentName, int bonusArmies)
        : continentIndex(index), armies(bonusArmies), name(continentName) {}

    // Copy constructor
    Continent(const Continent &other)
        : continentIndex(other.continentIndex), armies(other.armies), name(other.name) {}

    // Getter methods
    int getIndex() const { return continentIndex; }
    int getArmies() const { return armies; }
    const string &getName() const { return name; }

    // Assignment operator overload
    Continent &operator=(const Continent &other)
    {
        if (this != &other)
        {
            continentIndex = other.continentIndex;
            armies = other.armies;
            name = other.name;
        }
        return *this;
    }

    friend ostream &operator<<(ostream &out, const Continent &c)
    {
        out << "Continent " << c.name << " with index " << c.continentIndex
            << " applies an army bonus of " << c.armies << " when a player controls all of its countries." << endl;
        return out;
    }
};

class Territory
{
private:
    Player *owner;
    int numberOfArmies;
    int countryIndex;
    vector<Territory *> adjacentCountries;
    string name;
    int parent;
    int x;
    int y;

public:
    // Constructors
    Territory() : owner(nullptr), numberOfArmies(0), countryIndex(0), name(""), parent(0), x(0), y(0) {}

    Territory(const Territory &t) : owner(t.owner), numberOfArmies(t.numberOfArmies),
                                    countryIndex(t.countryIndex), adjacentCountries(t.adjacentCountries),
                                    name(t.name), parent(t.parent), x(t.x), y(t.y) {}
    Territory(Player *owner, int numberOfArmies, int countryIndex, string name, int parent, int x, int y)
        : owner(owner), numberOfArmies(numberOfArmies), countryIndex(countryIndex), name(name),
          parent(parent), x(x), y(y) {}
    Territory(Player *owner, int numberOfArmies, int countryIndex, string name, int parent,
              vector<Territory *> adjacentCountries, int x, int y)
        : owner(owner), numberOfArmies(numberOfArmies), countryIndex(countryIndex), name(name),
          parent(parent), adjacentCountries(adjacentCountries), x(x), y(y) {}
    Territory(int numberOfArmies, int countryIndex, string name, int parent, int x, int y)
        : owner(nullptr), numberOfArmies(numberOfArmies), countryIndex(countryIndex), name(name),
          parent(parent), x(x), y(y) {}
    Territory(int countryIndex, string name, int parent, int x, int y)
        : owner(nullptr), numberOfArmies(0), countryIndex(countryIndex), name(name),
          parent(parent), x(x), y(y) {}

    Territory &operator=(const Territory &t)
    {
        if (this != &t)
        {
            owner = t.owner;
            numberOfArmies = t.numberOfArmies;
            countryIndex = t.countryIndex;
            adjacentCountries = t.adjacentCountries;
            name = t.name;
            parent = t.parent;
            x = t.x;
            y = t.y;
        }
        return *this;
    }

    // Getters
    int getIndex()
    {
        return countryIndex;
    }
    Player *getOwner()
    {
        return owner;
    }
    int getNumberOfArmies()
    {
        return numberOfArmies;
    }
    string getName()
    {
        return name;
    }
    int getContinent()
    {
        return parent;
    }
    vector<Territory *> getAdjacentTerritories()
    {
        return adjacentCountries;
    }
    int getX()
    {
        return x;
    }
    int getY()
    {
        return y;
    }

    // Output operator
    friend ostream &operator<<(ostream &out, const Territory &t)
    {
        out << t.name << " is the country with index " << t.countryIndex
            << " and is located at position (" << t.x << ", " << t.y << ")." << endl;
        return out;
    }

    // Comparison operator
    friend bool operator==(const Territory &lhs, const Territory &rhs)
    {
        return lhs.countryIndex == rhs.countryIndex;
    }

    // Setters
    void setOwner(Player *player)
    {
        owner = player;
    }
    void setNumberOfArmies(int numArmies)
    {
        numberOfArmies = numArmies;
    }
    void setName(string newName)
    {
        name = newName;
    }
    void setAdjacentTerritories(vector<Territory *> territories)
    {
        adjacentCountries = territories;
    }
    void setX(int newX)
    {
        x = newX;
    }
    void setY(int newY)
    {
        y = newY;
    }
    void addAdjacentCountry(Territory *territory)
    {
        adjacentCountries.push_back(territory);
    }
    bool isAdjacent(Territory *territory)
    {
        for (auto t : adjacentCountries)
        {
            if (t == territory)
            {
                return true;
            }
        }
        return false;
    }

    // Destructor
    ~Territory()
    {
        adjacentCountries.clear();
    }
};

class Map
{
private:
    vector<Continent *> continents;
    vector<Territory *> countries;
    vector<tuple<int, int>> borders;
    bool valid;

public:
    Map() {}
    Map(const Map &m) : continents(m.continents), countries(m.countries), borders(m.borders), valid(m.valid) {}
    Map(vector<Continent *> continents, vector<Territory *> countries, vector<tuple<int, int>> borders)
        : continents(continents), countries(countries), borders(borders), valid(false) {}

    Map &operator=(const Map &m)
    {
        if (this != &m)
        {
            continents = m.continents;
            countries = m.countries;
            borders = m.borders;
            valid = m.valid;
        }
        return *this;
    }

    friend ostream &operator<<(ostream &out, const Map &m)
    {
        out << "MAP PROPERTIES: # of continents=" << m.continents.size() << ", # of countries=" << m.countries.size() << endl;
        return out;
    }

    vector<Continent *> getContinents()
    {
        return continents;
    }
    vector<Territory *> getTerritories()
    {
        return countries;
    }
    vector<tuple<int, int>> getBorders()
    {
        return borders;
    }
    bool isValid()
    {
        return valid;
    }

    vector<tuple<int, int>> getBordersByCountry(Territory country)
    {
        vector<tuple<int, int>> bordersByCountry;
        for (tuple<int, int> border : borders)
        {
            if (get<0>(border) == country.getIndex())
            {
                bordersByCountry.push_back(border);
            }
        }
        return bordersByCountry;
    }

    vector<Territory *> getTerritoriesByContinent(int continent)
    {
        vector<Territory *> continentCountries;
        for (Territory *t : countries)
        {
            if (t->getContinent() == continent)
            {
                continentCountries.push_back(t);
            }
        }
        return continentCountries;
    }

    void setContinents(vector<Continent *> continents)
    {
        this->continents = continents;
    }
    void setTerritories(vector<Territory *> territories)
    {
        countries = territories;
    }
    void setBorders(vector<tuple<int, int>> borders)
    {
        this->borders = borders;
    }

    void addContinent(Continent *continent)
    {
        continents.push_back(continent);
    }
    void addTerritory(Territory *territory)
    {
        countries.push_back(territory);
    }
    void addBorder(tuple<int, int> border)
    {
        borders.push_back(border);
    }
};

Map *MapLoader::createMapfromFile(const string &mapFileName)
{
    ifstream mapFile(mapFileName);
    if (!mapFile.is_open())
    {
        cerr << "Error: Unable to open map file " << mapFileName << endl;
        return nullptr;
    }

    string currentLine;
    string delimiter = " ";
    int currentContinent = 0;

    vector<Continent *> tempContinents;
    vector<Territory *> tempCountries;
    vector<tuple<int, int>> tempBorders;

    try
    {
        while (getline(mapFile, currentLine))
        {
            if (currentLine == "[continents]")
            {
                while (getline(mapFile, currentLine))
                {
                    if (currentLine.empty())
                    {
                        break;
                    }
                    else
                    {
                        istringstream lineStream(currentLine);
                        string name;
                        int armyValue;
                        lineStream >> name >> armyValue;
                        Continent *c = new Continent(++currentContinent, name, armyValue);
                        tempContinents.push_back(c);
                    }
                }
            }
            else if (currentLine == "[countries]")
            {
                while (getline(mapFile, currentLine))
                {
                    if (currentLine.empty())
                    {
                        break;
                    }
                    else
                    {
                        istringstream lineStream(currentLine);
                        int countryNumber;
                        string countryName;
                        int continent, x, y;
                        lineStream >> countryNumber >> countryName >> continent >> x >> y;
                        Territory *t = new Territory(countryNumber, countryName, continent, x, y);
                        tempCountries.push_back(t);
                    }
                }
            }
            else if (currentLine == "[borders]")
            {
                while (getline(mapFile, currentLine))
                {
                    if (currentLine.empty())
                    {
                        break;
                    }
                    else
                    {
                        istringstream lineStream(currentLine);
                        int countryNumber;
                        lineStream >> countryNumber;

                        vector<int> adjCountries;
                        int sharedBorder;
                        while (lineStream >> sharedBorder)
                        {
                            adjCountries.push_back(sharedBorder);

                            // Add edge tuple to the map
                            tempBorders.emplace_back(countryNumber, sharedBorder);

                            // Add territory pointer to the current node
                            tempCountries[countryNumber - 1]->addAdjacentCountry(tempCountries[sharedBorder - 1]);
                        }
                    }
                }
            }
        }

        mapFile.close();
        Map *m = new Map(tempContinents, tempCountries, tempBorders);
        return m;
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
        return nullptr;
    }
}
