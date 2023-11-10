#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <vector>
#include "Map.h"
#include "Player.h"
#include "LoggingObserver.h"


using namespace std;

class Transition;

class State;

class GameEngine;

class Transition {
public:
    // constructor
    Transition(State *to, string command);

    // copy constructor
    Transition(const Transition &other);

    // destructor
    ~Transition() = default;

    string getTriggerCommand();

    State *getTargetState();

    friend ostream &operator<<(ostream &os, Transition *transition);

private:
    State *mToState;
    string mTriggerCommand;
};

class State {
public:
    // constructor
    explicit State(string name, string phaseName = "N/A");

    // copy constructor
    State(const State &other);

    // destructor
    ~State() {
        // delete all transitions
        for (Transition *t: mTransitions) {
            delete t;
        }

    }

    State *handle(const string &command);

    void addTransition(string, State *toState);

    vector<Transition *> getTransitions();

    string getStateName();

    string getPhaseName();

    friend ostream &operator<<(ostream &os, State *state);

private:
    string mName;
    string mPhaseName;
    vector<Transition *> mTransitions;
};

class GameEngine : public Subject, public ILoggable {
public:
    GameEngine();

    GameEngine(const GameEngine &other);

    ~GameEngine() override {
        // delete all states
        for (State *s: *mStates) {
            delete s;
        }
    }


    State *setup();

    void addState(State *state);

    void handle(const string &command);

    State *getCurrentState();

    friend ostream &operator<<(ostream &os, GameEngine *gameEngine);

    // A2, Part 5 - Zack
    string stringToLog() override;

    //for Assignment 2, Part 3 - Tiffany
    void mainGameLoop();
    void reinforcementPhase();
    void issueOrdersPhase();
    void executeOrdersPhase();

private:
    State *mCurrentState;
    list<State *> *mStates;
    vector<Player*> players; // players in the game
    Map *map; // pointer to the map
};

void testGameStates();

void startupPhase();

#endif //GAME_ENGINE_H
