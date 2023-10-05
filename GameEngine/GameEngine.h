#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H


#include <vector>

class Command;

class Transition;

class State;

class GameEngine;

class Command {
public:
    Command(std::string *commandName);
    virtual ~Command() = default;
    std::string *getCommandName();
    std::string *setCommandName(std::string *commandName);

private:
    std::string *mCommandName;
};

class State {
public:
    State(std::string *commandName);
    void addTransition(Command *command, State *targetPhase);
    void handle(Command *command);
    std::string *getStateName();
    std::string *setStateName(std::string *stateName);

private:
    std::string *mStateName;
    std::vector<Transition *> mTransitions;
};

class Transition {
public:
    Transition(State *from, State *to, Command *command);
    bool isValid(Command *command) const;
    State *getTargetState() const;

private:
    State *mFromState;
    State *mToState;
    Command *mTriggerCommand;
};

class GameEngine {
public:
    void setup();

    void handle(Command *command);

private:
    State *mCurrentState;
};

void testGameStates();

#endif //GAME_ENGINE_H
