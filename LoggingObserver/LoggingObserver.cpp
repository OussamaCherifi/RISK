#include "LoggingObserver.h"
#include <fstream>
#include <iostream>

using namespace std;

// Default constructor, creates observer list
Subject::Subject() : _observers(new list<Observer *>) {};

// De-constructor, deletes observer list
Subject::~Subject() {
    delete _observers;
}

// Add observer to observers list
void Subject::Attach(Observer *o) {
    _observers->push_back(o);
}

// Remove observer from observers list
void Subject::Detach(Observer *o) {
    _observers->remove(o);
}

// Update all subscribed observers, passing loggable data object
void Subject::Notify(ILoggable *loggable) {
    auto i = _observers->begin();
    for (; i != _observers->end(); ++i)
        (*i)->Update(loggable);
}

// Update function for an observer, appends loggable object log string to log file
void LogObserver::Update(ILoggable *i) {
    // open game log file
    ofstream file("../gamelog.txt", std::ios::app);
    // Write logString to game log text file
    if (file.is_open()) {
        file << i->stringToLog() << endl;  // write object's log string
        file.close();
    }
}