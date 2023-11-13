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
    cout << "Tested GameEngine logging" << endl;

    auto *dummyPlayer = new Player();
    auto *dummyTarget = new Territory("dummy", "dummy", 0, 0);

    auto *deploy = new Deploy(dummyPlayer, dummyTarget, 0);
    auto *advance = new Advance(dummyPlayer, dummyTarget, dummyTarget, 0);
    auto *bomb = new Bomb(dummyPlayer, dummyTarget);
    auto *blockade = new Blockade(dummyPlayer, dummyTarget);
    auto *airlift = new Airlift(dummyPlayer, dummyTarget, dummyTarget, 0);
    auto *negotiate = new Negotiate(dummyPlayer, dummyPlayer);
    deploy->Attach(observer);
    advance->Attach(observer);
    bomb->Attach(observer);
    blockade->Attach(observer);
    airlift->Attach(observer);
    negotiate->Attach(observer);


    auto *ordersList = new OrdersList;
    ordersList->Attach(observer);

    ordersList->addList(deploy);
    ordersList->addList(advance);
    ordersList->addList(bomb);
    ordersList->addList(blockade);
    ordersList->addList(airlift);
    ordersList->addList(negotiate);


    auto listOfOrders = ordersList->getListOfOrders();
    auto i = listOfOrders.begin();
    for (; i != listOfOrders.end(); ++i) {
        cout << "executing " << **i << " order" << endl;
        (*i)->execute();
    }

    deploy->Detach(observer);
    delete deploy;
    advance->Detach(observer);
    delete advance;
    bomb->Detach(observer);
    delete bomb;
    blockade->Detach(observer);
    delete blockade;
    airlift->Detach(observer);
    delete airlift;
    negotiate->Detach(observer);
    delete negotiate;

    ordersList->Detach(observer);
    delete ordersList;
    cout << "Tested Orders & OrdersList logging" << endl;

    delete observer;
    cout << "Finished, check log file." << endl;
}