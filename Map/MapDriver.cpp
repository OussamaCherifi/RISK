#include <iostream>
#include "Map.h"
#include "MapDriver.h"
#include "Map.h"
#include <iostream>

using namespace std;



int main() {
    // Create a Map object
    Map map;

    // Test the MapLoader class to load a map from a file
    MapLoader mapLoader;

    // Provide the filename of a map file you want to load
    string mapFileName = "../mapFiles/001_I72_Ghtroc 720.map";  // Replace with your actual map file name

    // Try to load the map from the file
    bool mapLoaded = mapLoader.createMapFromFile(mapFileName, &map);

    if (mapLoaded) {
        cout << "Map loaded successfully!" << endl;

        // Now, you can test various Map and Territory functionalities
        // For example, you can print the map and its territories:
        map.insertInStream();

        // You can also perform other operations on the map and its territories.

    } else {
        cout << "Error: Map loading failed. Please check your map file." << endl;
    }

    return 0;
}