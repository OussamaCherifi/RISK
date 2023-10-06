#include <iostream>
#include "Map.h"
#include "Player/Player.h"

using namespace std;

int main()
{
    // Load a valid map from a file
    string fileName = "mapFiles/001_I72_Ghtroc 720.map";
    Map *testMap = MapLoader::createMapfromFile(fileName);

    // Display map properties
    cout << "Map properties" << endl;
    cout << "===" << endl;
    cout << *testMap << endl;

    // Display continents
    cout << "Continents" << endl;
    cout << "==========" << endl;

    for (Continent *c : testMap->getContinents())
    {
        cout << *c << endl;
    }

    // Display countries
    cout << "Territories" << endl;
    cout << "===========" << endl;

    for (Territory *t : testMap->getTerritories())
    {
        cout << *t << endl;
    }

    cout << "Map successfully generated from the map file!" << endl;

    // Additional functionality (if needed)
    testMap->validate();

    // Clean up allocated memory
    delete testMap;

    return 0;
}
