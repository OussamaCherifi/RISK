#include <iostream>
#include "Map.h"
#include <iostream>
#include <filesystem>

using namespace std;

std::string generateAbsolutePath(string mapName){

    // Get the current working directory, which is typically the directory of the C++ project
    std::filesystem::path projectPath = std::filesystem::current_path();

    // Directory to remove from the path
    std::string directoryToRemove = "cmake-build-debug";

    // Remove the directory from the path if it exists
    if (projectPath.filename() == directoryToRemove) {
        projectPath = projectPath.parent_path();
    }

    // Append the desired path to it
    projectPath /= "Map\\mapFiles";

    projectPath /= mapName;

    // Convert the path to a string
    std::string absolutePathStr = projectPath.string();

    // Print the absolute path
    std::cout << "Absolute Path: " << absolutePathStr << std::endl;

    return absolutePathStr;


}

//testLoadMap
void testLoadMaps(){

    auto* driver = new MapLoader();

    string fileName = generateAbsolutePath("mapFileTest.txt");

    // Print the absolute path
    std::cout << "Absolute Path: " << fileName << std::endl;

      // Create and test a map
        Map* mapTest = new Map();



//    if (driver != nullptr && mapTest != nullptr) {
//        std::string filepath = generateAbsolutePath(fileName);
//        driver->createMapFromFile(filepath, mapTest);
//    }

    bool testResult = driver->createMapFromFile(fileName, mapTest);

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


