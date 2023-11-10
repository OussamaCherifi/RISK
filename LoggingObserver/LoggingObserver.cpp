#include "LoggingObserver.h"
#include <fstream>
#include <iostream>

using namespace std;

Subject::Subject() : _observers(new list<Observer *>) {};

Subject::~Subject() {
    delete _observers;
}

void Subject::Attach(Observer *o) {
    _observers->push_back(o);
}

void Subject::Detach(Observer *o) {
    _observers->remove(o);
}

void Subject::Notify(ILoggable *loggable) {
    auto i = _observers->begin();
    for (; i != _observers->end(); ++i)
        (*i)->Update(loggable);
}

void LogObserver::Update(ILoggable *i) {
    // open game log file
    ofstream file("../gamelog.txt", std::ios::app);
    // Write logString to game log text file
    if (file.is_open()) {
        file << i->stringToLog() << endl;
        file.close();
    }

}