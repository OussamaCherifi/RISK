#include <iostream>
#include <map>
#include <vector>
#include <GameEngine.h>
#include <Map.h>


using namespace std;

void testGameStates() {

    cout << ">>> Testing GameEngine <<<" << endl;
    auto *engine = new GameEngine();
    do {
        cout << engine;

        string input;
        cin >> input;

        engine->handle(input);
    } while (engine->getCurrentState()->getStateName() != "end");
    cout << "The game has ended." << endl;


}

void testMainGameLoop(){
    //manually create territories
    Territory *t1 = new Territory("Alaska", "North America");
    Territory *t2 = new Territory("Northwest Territory", "North America");
    Territory *t3 = new Territory("Ontario", "North America");
    Territory *t4 = new Territory("Quebec", "North America");
    Territory *t5 = new Territory("Western US", "North America");
    Territory *t6 = new Territory("Eastern US", "North America");
    Territory *t7 = new Territory("Central America", "North America");
    Territory *t8 = new Territory("Mexico", "South America");

    //set their adjacent territories manually
    t1->addAdjacent(t2);
    t1->addAdjacent(t3);
    t1->addAdjacent(t5);

    t2->addAdjacent(t1);
    t2->addAdjacent(t3);
    t2->addAdjacent(t4);

    t3->addAdjacent(t1);
    t3->addAdjacent(t2);
    t3->addAdjacent(t4);
    t3->addAdjacent(t5);
    t3->addAdjacent(t6);

    t4->addAdjacent(t2);
    t4->addAdjacent(t3);
    t4->addAdjacent(t6);

    t5->addAdjacent(t3);
    t5->addAdjacent(t6);
    t5->addAdjacent(t7);

    t6->addAdjacent(t5);
    t6->addAdjacent(t3);
    t6->addAdjacent(t4);
    t6->addAdjacent(t7);

    t7->addAdjacent(t5);
    t7->addAdjacent(t6);
    t7->addAdjacent(t8);

    t8->addAdjacent(t7);

    //create the mapping of each continent with the number of its territories
    map<string, int> cNumAndName;
    cNumAndName["North America"] = 7;
    cNumAndName["South America"] = 1;

    //create the map and push all territories to the territorylist
    Map *map = new Map(cNumAndName);
    map->territories->push_back(t1);
    map->territories->push_back(t2);
    map->territories->push_back(t3);
    map->territories->push_back(t4);
    map->territories->push_back(t5);
    map->territories->push_back(t6);
    map->territories->push_back(t7);
    map->territories->push_back(t8);

    //create players and manually assign territories
    Player *p1 = new Player();
    p1->setName("Player 1");
    Player *p2 = new Player();
    p2->setName("Player 2");
    Player *p3 = new Player();
    p3->setName("Player 3");

    p1->addTerritory(t1);
    p1->addTerritory(t2);
    p1->addTerritory(t3);
    p1->addTerritory(t4);
    p1->addTerritory(t5);
    p1->addTerritory(t6);
    p1->addTerritory(t7);
    p3->addTerritory(t8);

    //create a vector of players and add the players
    vector<Player *> players;

    players.push_back(p1);
    players.push_back(p2);
    players.push_back(p3);

    //create the GameEngine
    GameEngine *gameEngine = new GameEngine(players, map);

    gameEngine->mainGameLoop();







}


