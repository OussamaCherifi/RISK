#include <iostream>
#include "GameEngine.h"

using namespace std;

Command::Command(string *commandName) : mCommandName(commandName) {}

State::State(string *commandName) : mStateName(commandName) {}

void State::addTransition(Command *command, State *targetPhase) {
    // todo add transitions
}

void State::handle(Command *command) {
    cout << "State : " << command << endl;
}

void GameEngine::setup() {

}

void GameEngine::handle(Command *command) {
    if (mCurrentState) {
        mCurrentState->handle(command);
    }
}

Transition::Transition(State *from, State *to, Command *command) :
        mFromState(from), mToState(to), mTriggerCommand(command) {}

//class Transition {
//public:
//    Transition(State* from, State* to, Command* command):
//            mFromState(from), mToState(to), mTriggerCommand(command)
//    {}
//
//    bool isValid(Command* command) const {
//        return command == mTriggerCommand;
//    }
//
//    State* getTargetState() const {
//        return mToState;
//    }
//
//private:
//    State* mFromState;
//    State* mToState;
//    Command* mTriggerCommand;
//};
//
//class Command {
//public:
//    virtual ~Command() {};
//};
//
//class State : public State {
//public:
//    void addTransition(Command* command, State* targetPhase) {
//        mTransitions.push_back(new Transition(this, targetPhase, command));
//    }
//
//    void handle(Command* command) override {
//        for (Transition* transition : mTransitions) {
//            if (transition->isValid(command)) {
//                mCurrentState = transition->getTargetState();
//                return;
//            }
//        }
//    }
//
//private:
//    std::vector<Transition*> mTransitions;
//    State* mCurrentState = nullptr;
//};
//
//class GameEngine {
//public:
//    void setInitialState(State* initialState) { mCurrentState = initialState; }
//
//    void handle(Command* command) {
//        if (mCurrentState) {
//            mCurrentState->handle(command);
//        }
//    }
//
//private:
//    State* mCurrentState = nullptr;
//};
