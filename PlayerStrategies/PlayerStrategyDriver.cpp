#include "PlayerStrategies.h"
#include "GameEngine.h"

void testPlayerStrategies() {
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

    //Create the deck of cards
    Deck *deck = new Deck();

    //create players and manually assign territories
    Player *p1 = new Player();
    p1->setName("Player 1");
    p1->setID(1);
    p1->setDeck(deck);
    p1->setPS(new BenevolentPlayerStrategy(p1));
    p1->getHand()->addCard(p1->getDeck()->draw());
    p1->getHand()->addCard(p1->getDeck()->draw());
    Player *p2 = new Player();
    p2->setName("Player 2");
    p2->setID(2);
    p2->setDeck(deck);
    p2->setPS(new NeutralPlayerStrategy(p2));
    p2->getHand()->addCard(p2->getDeck()->draw());
    p2->getHand()->addCard(p2->getDeck()->draw());
    Player *p3 = new Player();
    p3->setName("Player 3");
    p3->setID(3);
    p3->setDeck(deck);
    p3->setPS(new AggressivePlayerStrategy(p3));
    p3->getHand()->addCard(p3->getDeck()->draw());
    p3->getHand()->addCard(p3->getDeck()->draw());
//    Player *p4 = new Player();
//    p1->setName("Player 4");
//    p1->setID(4);
//    p1->setDeck(deck);
//    p1->setPS(new AggressivePlayerStrategy(p4));
//    p1->getHand()->addCard(p4->getDeck()->draw());
//    p1->getHand()->addCard(p4->getDeck()->draw());
//    Player *p5 = new Player();
//    p1->setName("Player 5");
//    p1->setID(5);
//    p1->setDeck(deck);
//    p1->setPS(new CheaterPlayerStrategy(p5));
//    p1->getHand()->addCard(p5->getDeck()->draw());
//    p1->getHand()->addCard(p5->getDeck()->draw());

    //assign players and armies to territories
    p1->addTerritory(t1);
    t1->setPlayer(p1);
    t1->setArmies(new int(3));

    p2->addTerritory(t2);
    t2->setPlayer(p2);
    t2->setArmies(new int(3));

    p1->addTerritory(t3);
    t3->setPlayer(p1);
    t3->setArmies(new int(3));

    p2->addTerritory(t4);
    t4->setPlayer(p2);
    t4->setArmies(new int(3));

    p1->addTerritory(t5);
    t5->setPlayer(p1);
    t5->setArmies(new int(3));

    p1->addTerritory(t6);
    t6->setPlayer(p1);
    t6->setArmies(new int(3));

    p3->addTerritory(t7);
    t7->setPlayer(p3);
    t7->setArmies(new int(1));

    p3->addTerritory(t8);
    t8->setPlayer(p3);
    t8->setArmies(new int(1));

    //create a vector of players and add the players
    vector<Player *> players;

    players.push_back(p1);
    players.push_back(p2);
    players.push_back(p3);
//    players.push_back(p4);
//    players.push_back(p5);

    //create the GameEngine
    GameEngine *gameEngine = new GameEngine(players, map);

    gameEngine->mainGameLoop();
}