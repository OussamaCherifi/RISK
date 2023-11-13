#include "Map.h"
#include <algorithm>
#include <fstream>



using namespace std; // Adding this to use the 'std' namespace

    // Parameterized constructor
    Territory::Territory(string name, string cont, int x, int y) :
            territoryName(new string(name)),
            continent(new string(cont)), xCoordinate(new int(x)),
            yCoordinate(new int(y)), visited(new bool(false)),
            numberOfArmies(new int(0)),
            adjacentTerritories(new vector<Territory *>()) {
    }

// Copy constructor
    Territory::Territory(Territory* copy) {
        territoryName = new std::string(copy->getName());
        continent = new std::string(copy->getContinent());
        xCoordinate = new int(copy->getxCoordinate());
        yCoordinate = new int(copy->getYCoordinate());
        player = new Player(*copy->getPlayer());
        visited = new bool(false);
        numberOfArmies = new int(0);
        adjacentTerritories = copy->adjacentTerritories;
    }

Territory::~Territory() {
    //deallocates all variables to not have memory leaks or dangling pointers
    delete player;
    player = nullptr;
    delete territoryName;
    territoryName = nullptr;
    delete continent;
    continent = nullptr;
    delete xCoordinate;
    xCoordinate = nullptr;
    delete yCoordinate;
    yCoordinate = nullptr;
    delete numberOfArmies;
    numberOfArmies = nullptr;
    for (auto ptr : *adjacentTerritories)
        delete ptr;  // Free the memory allocated for each Territory object
    adjacentTerritories->clear();  // Clear the vector
}

    // Add an adjacent territory to the vector
    void Territory::addAdjacent(Territory* adjacent) {
        adjacentTerritories->push_back(adjacent);
    }
    //checks if two territories are adjacent
    bool Territory::isAdjacentTo(Territory* otherTerritory) {
        for (Territory* adjacent : *adjacentTerritories) {
            if (adjacent == otherTerritory) {
                return true;
            }
        }
        return false;
    }
    //checks if the adjacent territory is owned by the same player
    bool Territory::isAdjacentToOwnedTerritory(Player* player) {
        for(Territory* adjacentTerritory : *adjacentTerritories){
            if (adjacentTerritory->getPlayer() == player){
                return true;
            }
        }
        return false;
    }

    // Define a stream insertion operator as a friend function
    void Territory::insertInStream() {
        cout << "Territory name: " << *territoryName << "; Position: " << *xCoordinate << ", " << *yCoordinate
             << "; Continent " << *continent << ". Owned by: " << *player << ", with " << *numberOfArmies
             << " armies." << endl;
    }

    //Adding getters and setters for territory class variables
    string Territory::getName() const {
        return *territoryName;
    }
    string Territory::getContinent() const {
        return *continent;
    }
    bool Territory::getVisited() const {
        return visited;
    }
    void Territory::setVisited(bool value) {
        visited = value;
    }
    vector<Territory *> *Territory::getAdjacentTerritories() const {
        return adjacentTerritories;
    }
    int Territory::getxCoordinate() const {
        return *xCoordinate; }

    int Territory::getYCoordinate() const {
        return *yCoordinate; }

    void Territory::setXCoordinate(int* newX) {
        delete xCoordinate;
        xCoordinate = newX;
    }
    Player *Territory::getPlayer() const {
        return player;
    }

    void Territory::setYCoordinate(int* newY) {
        delete yCoordinate;
        yCoordinate = newY;
    }
    void Territory::setPlayer(Player* newPlayer) {
        player = new Player;
    }
    //making the army change methods
    void Territory::addArmies(int num){
        *numberOfArmies+=num;
    }
    void Territory::doubleArmies() {
        *numberOfArmies *= 2;
    }
    void Territory::removeHalfArmies() {
        *numberOfArmies /=2;
    }
    void Territory::removeArmies(int num) {
        *numberOfArmies -= num;
        if (*numberOfArmies<0){
            *numberOfArmies =0;
        }
    }
    void Territory::setArmies(int* newArmies) {
        *numberOfArmies = *newArmies;
    }
    int Territory::getArmies() const {
        return *numberOfArmies;
    }

//map constructors
    Map::Map() {
        territories = new vector<Territory*>;
    }

    Map::Map(const Map& copy) {
    // Perform a deep copy of the territories vector
    territories = new vector<Territory*>(*copy.territories);
    }

    void Map::insertInStream() {
    std::cout << "Territories: [" << std::endl;
    for (Territory* var : *territories) {
        var->insertInStream();
    }
    std::cout << "]" << std::endl;
}

bool Map::isMapConnected() {
    if (territories->empty()) {
        return false;
    }

    // Reset visited flag for all territories
    for (Territory* node : *territories) {
        node->setVisited(false);
    }

    std::stack<Territory*> stack;
    stack.push((*territories)[0]);

    while (!stack.empty()) {
        Territory* node = stack.top();
        stack.pop();

        if (!node->getVisited()) {
            node->setVisited(true);
            for (Territory* neighbor : *node->getAdjacentTerritories()) {
                stack.push(neighbor);
            }
        }
    }

    // Check if all territories have been visited
    for (Territory* node : *territories) {
        if (!node->getVisited()) {
            return false;
        }
    }

    return true;
}


bool Map::validate() {
    //Ensure that all territories are connected.
    if (!isMapConnected()) {
        return false;
    }
    std::map<std::string, Map> continentGraphs;

    //Allocate nodes to their respective continent graphs.
    for (Territory* node : *territories) {
        // Check if a graph already exists.
        if (continentGraphs.find(node->getContinent()) == continentGraphs.end()) {
            continentGraphs[node->getContinent()] = Map();
        }
        continentGraphs[node->getContinent()].territories->push_back(node);
    }

    // Check the connectivity of each continent graph.
    for (auto& continentEntry : continentGraphs) {
        Map& continentMap = continentEntry.second;
        if (!continentMap.isMapConnected()) {
            return false;
        }
    }

    // Ensure that all territories belong to at least one continent.
    for (Territory* territory : *territories) {
        if (territory->getContinent().empty()) {
            return false;
        }
    }

    // If all checks pass, the map is valid.
    return true;
}

map<string, int> Map::getContinentNameAndNum() {return continentNameAndNum;}


bool MapLoader::createMapFromFile(string& fileName, Map* mapToCreate) {
    std::ifstream inputFile;
    inputFile.open(fileName);

    // the following conditions reject the file
    // Reject if we cant open the file
    if (!inputFile.is_open()) {
        cout << "There was an error opening this file" << endl;
        //        std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
        return false;  // Return an error code
    }

    //return error if the first line of the file is not "[Map]"
    string nextLine;
    if (!getline(inputFile, nextLine) || nextLine != "[Map]") {
        inputFile.close();
        return false;
    }

    // Skip all the lines until we reach "[Continents]", and reject the file if we cannot reach it
    while (nextLine != "[Continents]") {
        if (!getline(inputFile, nextLine)) {
            inputFile.close();
            return false;
        }
    }
    //here the document wasn't rejected YET so we can start processing the data

    // Parse the continent data until we reach an empty line or the "[Territories]" section.
    // Create associations between continent names and their corresponding territory counts
    map<string, int> continentInfo;
    while (nextLine != "[Territories]") {
        if (!getline(inputFile, nextLine)) {
            //reject the file if we find no [territory] line
            inputFile.close();
            return false;
        }
        try{

            if (!nextLine.empty() && nextLine != "[Territories]") {
                int index = nextLine.find("=");
                // Remove spaces and add continent to the list
                string substring = nextLine.substr(0, index);
                substring.erase(remove(substring.begin(), substring.end(), ' '), substring.end());
                continentInfo.insert(make_pair(substring, stoi(nextLine.substr(index + 1))));

                //made a copy of continentInfo to access it from continentNameAndNum, instance of Map
                mapToCreate->getContinentNameAndNum().insert(make_pair(substring, stoi(nextLine.substr(index + 1))));
            }
        }
        catch (const exception& e) {
            inputFile.close();
            return false;
        }
    }

    // Reach the "[Territories]" line and begin looping until the end of the file and reject the file if there is no "[Territories]" line
    map<string, Territory*> territoryList;
    vector<vector<string>> adjacentListInfo;

    while (!inputFile.eof()) {
        //assign territories their name, coordinates, and continent and skip over the empty lines
        if (getline(inputFile, nextLine) && !nextLine.empty()) {
            try {
                // Remove spaces
                nextLine.erase(remove_if(nextLine.begin(), nextLine.end(), ::isspace), nextLine.end());
                // Split the string using commas
                vector<string> elements;
                size_t start = 0, end;

                while ((end = nextLine.find(',', start)) != string::npos) {
                    elements.push_back(nextLine.substr(start, end - start));
                    start = end + 1;
                }
                elements.push_back(nextLine.substr(start));
                // Create a territory from the initial elements and add it to the map list
                Territory* newTerritory = new Territory(elements[0], elements[3], stoi(elements[1]), stoi(elements[2]));
                mapToCreate->territories->push_back(newTerritory);
                territoryList.insert(make_pair(newTerritory->getName(), newTerritory));

                // If the continent number is negative or the continent cannot be found we need to reject the file
                continentInfo[elements[3]] -= 1;
                if (continentInfo[elements[3]] < 0) {
                    inputFile.close();
                    return false;
                }

                // Add the remaining adjacent territories to the adjacent list
                elements.erase(elements.begin(), elements.begin() + 4);
                adjacentListInfo.push_back(elements);
            }
            catch (const exception& e) {
                inputFile.close();
                return false;
            }
        }
    }

    //Link territories with their adjacent territories; File rejection occurs
    // if a territory lacks neighbors which means an incomplete connection.
    if (mapToCreate->territories->size() == adjacentListInfo.size() && mapToCreate->territories->size() > 0) {
        for (int i = 0; i < adjacentListInfo.size(); i++) {
            if (adjacentListInfo[i].size() > 0) {
                for (const string &neighbor: adjacentListInfo[i]) {
                    mapToCreate->territories->at(i)->addAdjacent(territoryList[neighbor]);
                }
            }
        }
    }
    return false;
}