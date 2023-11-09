#ifndef LOGGING_OBSERVER_H
#define LOGGING_OBSERVER_H

#include <list>
#include <string>

using namespace std;

class LogObserver;

class Subject;

class ILoggable;

class Subject {
public:
    virtual void Attach(LogObserver* o);
    virtual void Detach(LogObserver* o);
    virtual void Notify();
    Subject();
    ~Subject();
private:
    list<LogObserver*> *_observers;
};

class ILoggable {
public:
    ~ILoggable() = default;
    virtual void stringToLog(string s) = 0;
protected:
    ILoggable() = default;
};

void testLoggingObserver();

#endif
