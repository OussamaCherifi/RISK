#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <exception>
#include "Map.h"
#include <sstream>

using namespace std;

class Territory {
public:
    Territory(const std::string& name, const std::string& cont, int x, int y)
        : name(name), continent(cont), xCoord(x), yCoord(y), visited(false) {}

    int getXCoord() const { return xCoord; }
    int getYCoord() const { return yCoord; }
    const std::string& getPlayer() const { return name; }
    const std::string& getName() const { return name; }
    const std::string& getContinent() const { return continent; }

    void addNeighbor(Territory* neighbor) {
        neighbors.push_back(neighbor);
    }

private:
    std::string name;
    std::string continent;
    int xCoord;
    int yCoord;
    bool visited;
    std::vector<Territory*> neighbors;
};

class Map {
public:
    Map() {}

    bool loadMapFromFile(const std::string& fileName) {
        std::ifstream inputFileStream(fileName);
        if (!inputFileStream.is_open()) {
            std::cerr << "Error: Could not open file." << std::endl;
            return false;
        }

        if (!skipLinesUntil(inputFileStream, "[Map]")) {
            inputFileStream.close();
            return false;
        }

        std::map<std::string, int> continents;
        if (!readContinents(inputFileStream, continents)) {
            inputFileStream.close();
            return false;
        }

        if (!readTerritories(inputFileStream)) {
            inputFileStream.close();
            return false;
        }

        if (!connectTerritories()) {
            inputFileStream.close();
            return false;
        }

        inputFileStream.close();
        return true;
    }

    bool validate() {
        if (territories.empty() || !isConnected()) {
            return false;
        }

        std::map<std::string, Map> continentGraphs;
        if (!createContinentGraphs(continentGraphs)) {
            return false;
        }

        for (const auto& continentMap : continentGraphs) {
            if (!continentMap.second.isConnected()) {
                return false;
            }
        }

        if (!checkTerritoriesBelongToOneContinent()) {
            return false;
        }

        return true;
    }

    void displayMap() {
        std::cout << "Territories: [" << std::endl;
        for (const Territory& territory : territories) {
            std::cout << "Territory Name: " << territory.getName() << "\n";
        }
        std::cout << "]" << std::endl;
    }

private:
    std::vector<Territory> territories;

    bool skipLinesUntil(std::ifstream& fileStream, const std::string& target) {
        std::string line;
        while (getline(fileStream, line)) {
            if (line == target) {
                return true;
            }
        }
        return false;
    }

    bool readContinents(std::ifstream& fileStream, std::map<std::string, int>& continents) {
        std::string line;
        while (getline(fileStream, line) && line != "[Territories]") {
            size_t index = line.find("=");
            if (index == std::string::npos) {
                return false;
            }
            std::string continentName = line.substr(0, index);
            continents[continentName] = std::stoi(line.substr(index + 1));
        }
        return true;
    }

    bool readTerritories(std::ifstream& fileStream) {
        std::string line;
        while (getline(fileStream, line)) {
            if (!line.empty()) {
                if (!parseTerritoryLine(line)) {
                    return false;
                }
            }
        }
        return true;
    }

    bool parseTerritoryLine(const std::string& line) {
        std::vector<std::string> elements;
        size_t start = 0, end;
        std::string cleanedLine = line;
        cleanedLine.erase(
            std::remove_if(cleanedLine.begin(), cleanedLine.end(), ::isspace),
            cleanedLine.end()
        );

        while ((end = cleanedLine.find(',', start)) != std::string::npos) {
            elements.push_back(cleanedLine.substr(start, end - start));
            start = end + 1;
        }
        elements.push_back(cleanedLine.substr(start));

        if (elements.size() < 7) {
            return false;
        }

        territories.push_back(Territory(
            elements[0], elements[3], std::stoi(elements[1]), std::stoi(elements[2])
        ));

        return true;
    }

    bool connectTerritories() {
        for (const auto& territory : territories) {
            if (!parseTerritoryNeighbors(territory)) {
                return false;
            }
        }
        return true;
    }

    bool parseTerritoryNeighbors(const Territory& territory) {
        std::string territoryName = territory.getName();
        std::ifstream inputFileStream;
        inputFileStream.open("your_map_file.txt");

        std::string line;
        while (getline(inputFileStream, line)) {
            if (line.empty()) {
                continue;
            }

            if (line.find(territoryName) == 0) {
                size_t index = line.find_first_of('=');
                if (index == std::string::npos) {
                    inputFileStream.close();
                    return false;
                }

                std::string territoryInfo = line.substr(index + 1);
                size_t start = 0, end;
                std::vector<std::string> neighborNames;

                while ((end = territoryInfo.find(',', start)) != std::string::npos) {
                    neighborNames.push_back(territoryInfo.substr(start, end - start));
                    start = end + 1;
                }
                neighborNames.push_back(territoryInfo.substr(start));

                for (const auto& neighborName : neighborNames) {
                    auto neighbor = findTerritoryByName(neighborName);
                    if (neighbor != nullptr) {
                        territory.addNeighbor(neighbor);
                    } else {
                        inputFileStream.close();
                        return false;
                    }
                }
            }
        }

        inputFileStream.close();
        return true;
    }

    Territory* findTerritoryByName(const std::string& name) {
        for (auto& territory : territories) {
            if (territory.getName() == name) {
                return &territory;
            }
        }
        return nullptr;
    }

    bool createContinentGraphs(std::map<std::string, Map>& continentGraphs) {
        for (const auto& territory : territories) {
            const std::string& continentName = territory.getContinent();
            if (continentGraphs.find(continentName) == continentGraphs.end()) {
                continentGraphs[continentName] = Map();
            }
            continentGraphs[continentName].territories.push_back(territory);
        }
        return true;
    }

    bool isConnected() {
        if (territories.empty()) {
            return true;
        }

        std::stack<Territory*> stack;
        stack.push(&territories[0]);

        while (!stack.empty()) {
            Territory* node = stack.top();
            stack.pop();

            if (!node->visited
