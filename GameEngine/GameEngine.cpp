#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>
#include <math.h>
#include <GameEngine.h>

using namespace std;

// GameEngine
GameEngine::GameEngine() : mCurrentState(GameEngine::setup()) {}

GameEngine::GameEngine(const GameEngine &other) {
    string currentStateName = mCurrentState->getStateName();
    for (State *s: *other.mStates) {
        auto *newState = new State(*s);
        this->addState(newState);
        if (newState->getStateName() == currentStateName) {
            this->mCurrentState = newState;
        }
    }
}

State *GameEngine::setup() {
    mStates =  new list<State *>;
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
    mStates->push_back(state);
}

void GameEngine::handle(const string &command) {
    State *newState = mCurrentState->handle(command);
    if (newState->getStateName() == "fail") {
        cout << "Invalid command: " << command << endl;
        return;
    }
    mCurrentState = newState;
    Notify(this);
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

// For Assignment 2, Part 5 - Zack
string GameEngine::stringToLog() {
    State *currentState = this->getCurrentState();
    return "[GameEngine]\tTransition to state: " + currentState->getStateName() +
           "\tPhase: " + currentState->getPhaseName();
}

//For Assignment 2, Part 3 - Tiffany
void GameEngine::mainGameLoop(){
    int numTerr = 0;
    if (map != nullptr) numTerr = map->territories->size();

    bool playerHasAllTerritories = false;

    while(!playerHasAllTerritories){
        for (int i = 0; i < players.size(); i++){
            if (players[i]->getTerritoryList().size() == numTerr){
                cout << "player has won!" << endl;
                // set state to win?
            }
            else if (players[i]->getTerritoryList().empty()){
                cout << "player has no more territories! Removing player from the game." << endl;
                delete players[i];
                players.erase(players.begin() + i);
            }
        }
            reinforcementPhase();
            issueOrdersPhase();
            executeOrdersPhase();
    }

}

void GameEngine::reinforcementPhase(){
    for (Player *p : players){
        int numReinforcement = floor(p->getTerritoryList().size() / 3);
        // if (p.ownsContinent()) numReinforcement += 5;

        //make sure the minimum number is 3
        if (numReinforcement < 3) numReinforcement = 3;

        cout << "player is receiving " << numReinforcement << " reinforcements." << endl;

        int *ptrNumReinforcement = &numReinforcement;

        p->setReinforcementPool(ptrNumReinforcement);
    }
}

void GameEngine::issueOrdersPhase(){
    for (Player *p : players){
        string territoryName;
        int numUnits, territoryIndex;
        bool territoryFound = false;
        bool correctNum = false;

        cout << "Let's start by deploying army units from your reinforcement pool. " << endl;

        while (p->getReinforcementPool() > 0){
            cout << "You have " << p->getReinforcementPool() << " army units in your reinforcement pool." << endl;

            while(!territoryFound){
                cout << "Enter the name of territory you wish to deploy army units: ";
                cin >> territoryName;

                for(int i = 0; i < p->getTerritoryList().size(); i++){

                    if (territoryName == p->getTerritoryList()[i]->getName()){
                        territoryFound = true;
                        territoryIndex = i;
                        break;
                    }
                }

                cout << "Territory not found. Please re-enter the territory name." << endl;
            }

            while(!correctNum){
                cout << "How many army units do you wish to deploy?";
                cin >> numUnits;

                if (numUnits > 0 && numUnits <= *p->getReinforcementPool())
                    correctNum = true;

                cout << "Invalid number. Please enter another number." << endl; 
            }

            // p.getTerritoryList()[territoryIndex].deploy(numUnits);

        }

        cout << "Great! All your reinforcement army units are deployed!" << endl;

        p->issueOrder();
    }
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

void startupPhase() {

    std::string choice;
    bool running = true;

    MapLoader driver = MapLoader();
    Map *mapTest = new Map();

    while(running) {

        // Display the menu
        std::cout << "Command Menu:\n";
        std::cout << "1. loadmap <filename>\n";
        std::cout << "2. validateMap\n";
        std::cout << "3. addplayer\n";
        std::cout << "4. gamestart\n";
        std::cout << "Enter your choice: ";

        // Get user's choice as a string
        std::cin >> choice;


        if (choice == "1") {
            std::cout << "Enter the Name of the map you wish to load: ";
            std::string mapChoice;

            // Get user's choice of map
            std::cin >> mapChoice;

            std::string filepath = generateAbsolutePath(mapChoice);
            driver.createMapFromFile(filepath, mapTest);

        } else if (choice == "2") {
            std::cout << "You selected Option 2\n";
            mapTest->validate();

        } else if (choice == "3") {
            std::cout << "You selected Option 3\n";
        } else if (choice == "4") {
            std::cout << "Goodbye!\n";
            // Exit the loop to end the program
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }

    }
    }
