#include "LoggingObserver.h"
#include <fstream>

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
    string logString = i->stringToLog();

    ofstream file;

    // Write logString to game log text file
    file.open("../gamelog.txt", std::ios::out);
    if (file.is_open()) {
        file << logString << endl;
        file.close();
    }

}