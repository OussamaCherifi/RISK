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

    virtual void Attach(Observer *o);

    virtual void Detach(Observer *o);

    virtual void Notify(ILoggable *i);

private:
    list<Observer *> *_observers;
};

class LogObserver : public Observer {
public:
    LogObserver() = default;

    ~LogObserver() = default;

    void Update(ILoggable *i) override;
};

void testLoggingObserver();

#endif
