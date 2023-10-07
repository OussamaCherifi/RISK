#include <iostream>
#include <GameEngine.h>

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