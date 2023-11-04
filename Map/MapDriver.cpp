#include <iostream>
#include "Map.h"
#include <iostream>

using namespace std;

int main() {
    MapDriver::testLoadMaps();
    return 0;
}

void MapDriver::testLoadMaps(){

    MapLoader driver = MapLoader();

    string MapName = "../mapFiles/Roman Empire.map";
//    string MapName2 = "../mapFiles/Roman Empire.map";
    // Create and test a map
        Map* mapTest = new Map();

        bool testResult = driver.createMapFromFile(MapName, mapTest);

        if (testResult) {
            cout << "Successful creation of a map from " << mapTest << endl;
            if (mapTest->validate()) {
                cout << "Map from " << mapTest << " is valid!" << endl;
            } else {
                cout << "Map from " << mapTest << " is invalid!" << endl;
            }
        } else {
            cout << "Unsuccessful creation of a map from " << mapTest << endl;
        }
    mapTest->territories->clear();
    delete mapTest;
}
