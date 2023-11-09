#include <iostream>
#include "Map.h"
#include <iostream>
#include <filesystem>

using namespace std;

int main() {
    MapDriver::testLoadMaps();
    return 0;
}

void MapDriver::testLoadMaps(){
    MapLoader driver = MapLoader();

    // Get the current working directory, which is typically the directory of the C++ project
    std::filesystem::path projectPath = std::filesystem::current_path();

    // Directory to remove from the path
    std::string directoryToRemove = "cmake-build-default-mingw";

    // Remove the directory from the path if it exists
    if (projectPath.filename() == directoryToRemove) {
        projectPath = projectPath.parent_path();
    }

    // Append the desired path to it
    projectPath /= "Map\\mapFiles\\mapFileTest.txt";

    // Convert the path to a string
    std::string absolutePathStr = projectPath.string();

    // Print the absolute path
    std::cout << "Absolute Path: " << absolutePathStr << std::endl;

      // Create and test a map
        Map* mapTest = new Map();

        bool testResult = driver.createMapFromFile(absolutePathStr, mapTest);
//    C:\Users\oussa\OneDrive\Bureau\fall 2023\comp345\risk_a2\Map\mapFiles\mapFileTest.txt
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
