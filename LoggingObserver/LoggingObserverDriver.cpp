#include "LoggingObserver.h"
#include "GameEngine.h"
#include "commandProcessing.h"
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
    auto *deploy = new Deploy();
    auto *advance = new Advance();
    auto *bomb = new Bomb();
    auto *blockade = new Blockade();
    auto *airlift = new Airlift();
    auto *negotiate = new Negotiate();

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

    deploy->Notify(deploy);
    advance->Notify(advance);
    bomb->Notify(bomb);
    blockade->Notify(blockade);
    airlift->Notify(airlift);
    negotiate->Notify(negotiate);

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

    auto *dummyEngine = new GameEngine();

    auto *commandProcessor = new CommandProcessor();
    commandProcessor->getCommand(*dummyEngine);
    commandProcessor->Attach(observer);
    commandProcessor->Notify(commandProcessor);

    auto *command = new Command();
    command->Attach(observer);
    command->saveEffect(new string("Test explosion"));


    delete dummyEngine;
    delete commandProcessor;


    cout << "Tested Command & CommandProcessor logging" << endl;

    delete observer;
    cout << "Finished, check log file." << endl;
}