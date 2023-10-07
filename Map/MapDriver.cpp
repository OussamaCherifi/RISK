#include <iostream>
#include "Map.h"
#include "Player/Player.h"

using namespace std;


class MapDriver {
public:
    static void testLoadMaps() {
        MapLoader mapDriver;

        std::string mapFile1 = "../MapFiles/001_I72_Ghtroc 720.map";
        Map mapTest1;

        if (mapDriver.createMapFromFile(mapFile1, mapTest1)) {
            std::cout << "Successful creation of a map from " << mapFile1 << std::endl;
            if (mapTest1.validate()) {
                std::cout << "Map from " << mapFile1 << " is valid!" << std::endl;
            } else {
                std::cout << "Map from " << mapFile1 << " is invalid!" << std::endl;
            }
        } else {
            std::cout << "Unsuccessful creation of a map from " << mapFile1 << std::endl;
        }
    }
};

int main() {
    MapDriver::testLoadMaps();
    return 0;
}