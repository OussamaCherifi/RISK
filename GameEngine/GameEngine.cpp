#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>
#include <GameEngine.h>

using namespace std;

// GameEngine
GameEngine::GameEngine() : mCurrentState(GameEngine::setup()) {}

GameEngine::GameEngine(const GameEngine &other) {
    string currentStateName = mCurrentState->getStateName();
    for (State *s: other.mStates) {
        auto *newState = new State(*s);
        this->mStates.push_back(newState);
        if (newState->getStateName() == currentStateName) {
            this->mCurrentState = newState;
        }
    }
}

State *GameEngine::setup() {
    auto *start = new State("start", "startup");
    auto *mapLoaded = new State("map-loaded", "startup");
    auto *mapValidated = new State("map-validated", "startup");
    auto *playersAdded = new State("players-added", "startup");
    auto *assignReinforcement = new State("assign-reinforcement", "play");
    auto *issueOrders = new State("issue-orders", "play");
    auto *executeOrders = new State("execute-orders", "play");
    auto *win = new State("win", "play");
    auto *end = new State("end");

    start->addTransition("loadmap", mapLoaded);
    this->addState(start);

    mapLoaded->addTransition("loadmap", mapLoaded);
    mapLoaded->addTransition("validatemap", mapValidated);
    this->addState(mapLoaded);

    mapValidated->addTransition("addplayer", playersAdded);
    this->addState(mapValidated);

    playersAdded->addTransition("addplayer", playersAdded);
    playersAdded->addTransition("assigncountries", assignReinforcement);
    this->addState(playersAdded);

    assignReinforcement->addTransition("issueorder", issueOrders);
    this->addState(assignReinforcement);

    issueOrders->addTransition("issueorder", issueOrders);
    issueOrders->addTransition("endissueorders", executeOrders);
    this->addState(issueOrders);

    executeOrders->addTransition("execorder", executeOrders);
    executeOrders->addTransition("endexecorders", assignReinforcement);
    executeOrders->addTransition("win", win);
    this->addState(executeOrders);

    win->addTransition("play", start);
    win->addTransition("end", end);
    this->addState(win);

    return start;
}

void GameEngine::addState(State *state) {
    mStates.emplace_back(state);
}

void GameEngine::handle(const string &command) {
    State *newState = mCurrentState->handle(command);
    if (newState->getStateName() == "fail") {
        cout << "Invalid command: " << command << endl;
        return;
    }
    mCurrentState = newState;
}

State *GameEngine::getCurrentState() { return mCurrentState; }

// State
State::State(string name, string phaseName) : mName(std::move(name)), mPhaseName(std::move(phaseName)) {}

State::State(const State &other) : mName(other.mName), mPhaseName(other.mPhaseName) {
    for (Transition *t: other.mTransitions) {
        mTransitions.push_back(new Transition(*t));
    }
}

void State::addTransition(string command, State *targetPhase) {
    auto *newTransition = new Transition(targetPhase, std::move(command));
    mTransitions.emplace_back(newTransition);
}

vector<Transition *> State::getTransitions() { return mTransitions; }

State *State::handle(const string &command) {
    for (Transition *t: mTransitions) {
        if (t->getTriggerCommand() == command)
            return t->getTargetState();
    }
    return new State("fail");
}

string State::getStateName() { return mName; }

string State::getPhaseName() { return mPhaseName; }

//For Assignment 2, Part 3 - Tiffany
void GameEngine::mainGameLoop(){
    int numTerr = 0;
    if (map != nullptr) numTerr = map->territories->size();

    bool playerHasAllTerritories = false;

    while(!playerHasAllTerritories){
        for (int i = 0; i < players.size(); i++){
            if (players[i]->getTerritoryList().size() == numTerr){
                //player wins
            }
            else if (players[i]->getTerritoryList().empty()){
                cout << "player has no more territories! Removing player from the game." << endl;
                delete players[i];
                players.erase(players.begin() + i);
            }
            else{
                reinforcementPhase();
                issueOrdersPhase();
                executeOrdersPhase();
            }
        }

    }
    
}

void GameEngine::reinforcementPhase(){

}

void GameEngine::issueOrdersPhase(){

}

void GameEngine::executeOrdersPhase(){

}

// Transition
Transition::Transition(State *to, string command) :
        mToState(to), mTriggerCommand(std::move(command)) {}

Transition::Transition(const Transition &other) {
    this->mToState = other.mToState;
    this->mTriggerCommand = other.mTriggerCommand;
}

State *Transition::getTargetState() { return mToState; }

string Transition::getTriggerCommand() { return mTriggerCommand; }

ostream &operator<<(ostream &os, State *s) {
    os << "STATE: " << s->getStateName() << "\t\t[" << s->getPhaseName() << "]" << endl;
    // add all transitions
    for (Transition *t: s->getTransitions()) {
        os << "\t - " << t << endl;
    }
    return os;
}

ostream &operator<<(ostream &os, Transition *t) {
    os << " " << t->getTriggerCommand() << " -> " << t->getTargetState()->getStateName();
    return os;
}

ostream &operator<<(ostream &os, GameEngine *gameEngine) {
    os << gameEngine->getCurrentState();

    return os;
}