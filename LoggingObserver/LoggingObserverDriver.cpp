#include "LoggingObserver.h"
#include "GameEngine.h"
#include <iostream>
#include <fstream>

using namespace std;

void testLoggingObserver() {
    cout << ">>> Testing LoggingObserver <<<" << endl;

    auto *logObserver = new LogObserver();  // create log observer

    auto *engine = new GameEngine();  // create game engine
    engine->Attach(logObserver);

    engine->Notify(engine);
}