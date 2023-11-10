#include "LoggingObserver.h"
#include "GameEngine.h"
#include <iostream>

using namespace std;

void testLoggingObserver() {
    cout << ">>> Testing LoggingObserver <<<" << endl;

    auto *observer = new LogObserver();  // create log observer

    auto *engine = new GameEngine();  // create game engine

    engine->Attach(observer);  // attach observer

    // handle some transitions
    engine->handle("loadmap");
    engine->handle("validatemap");
    engine->handle("addplayer");
    engine->handle("addplayer");
    engine->handle("assigncountries");


    engine->Detach(observer);
    delete engine;
    delete observer;

    cout << "Finished, check log file." << endl;
}