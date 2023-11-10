#ifndef LOGGING_OBSERVER_H
#define LOGGING_OBSERVER_H

#include <list>
#include <string>

using namespace std;

// ILoggable interface class (only pure virtual functions)
class ILoggable {
public:
    virtual ~ILoggable() = default;

    virtual string stringToLog() = 0;
};


// Observer abstract class
class Observer {
public:
    ~Observer() = default;

    virtual void Update(ILoggable *) = 0;

protected:
    Observer() = default;
};

// Subject abstract class
class Subject {
public:
    Subject();

    ~Subject();

    virtual void Attach(Observer *o);  // attach an observer to subject

    virtual void Detach(Observer *o);  // detach an observer from subject

    virtual void Notify(ILoggable *i);  // notify all observers, pass Loggable object

private:
    list<Observer *> *_observers;
};

// LogObserver class
class LogObserver : public Observer {
public:
    LogObserver() = default;

    ~LogObserver() = default;

    void Update(ILoggable *i) override;
};

// free function to test Observer pattern implementation
void testLoggingObserver();

#endif
