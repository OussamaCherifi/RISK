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
    GameEngine* game = new GameEngine();
    MapLoader driver = MapLoader();
    Map *mapTest = new Map();
    Deck deck;
    Hand hand;

    // Create a vector to store Player objects that are created
    std::vector<Player*> playerList;

    while(true) {

        // Display the menu
        std::cout << "Command Menu:\n";
        std::cout << "1. loadmap <filename>\n";
        std::cout << "2. validateMap\n";
        std::cout << "3. addplayer\n";
        std::cout << "4. gamestart\n";
        std::cout << "5. press 5 to exit\n";
        std::cout << "Enter your choice: ";

        // Get input from the user
        std::cout << "Enter a command: ";
        std::string userInput;
        std::getline(std::cin, userInput);

        // Remove spaces from the input
        userInput.erase(std::remove_if(userInput.begin(), userInput.end(), ::isspace), userInput.end());

        // Check if the input has the format "loadmap<someFile>"
        std::string expected_prefix_loadmap = "loadmap";
        std::string expected_prefix_addplayer = "addplayer";
        size_t open_bracket = userInput.find('<');
        size_t close_bracket = userInput.find('>');

        if (userInput.compare(0, expected_prefix_loadmap.size(), expected_prefix_loadmap) == 0 &&
            userInput.size() > expected_prefix_loadmap.size() &&
            userInput[userInput.size() - 1] == '>') {

            if (open_bracket != std::string::npos && close_bracket != std::string::npos &&
                open_bracket < close_bracket) {
                std::string filename = userInput.substr(open_bracket + 1, close_bracket - open_bracket - 1);
                std::cout << "Loading map with filename: " << filename << std::endl;

                std::string filepath = generateAbsolutePath(filename);
                bool loadResult = driver.createMapFromFile(filepath, mapTest);
                if (loadResult) {
                    cout << "Successful creation of a map from " << mapTest << endl;
                }
                else {
                    cout << "Unsuccessful creation of a map from " << mapTest << endl;
                }

            }

        }

        //user chooses to validate the current loaded map
        else if (userInput == "validateMap") {
                std::cout << "Validating map\n";
                    if (mapTest->validate()) {
                        cout << "Map from " << mapTest << " is valid!" << endl;
                    } else {
                        cout << "Map from " << mapTest << " is invalid!" << endl;
            }


        }

        //user chooses to add a player into the game
        else if (userInput.compare(0, expected_prefix_addplayer.size(), expected_prefix_addplayer) == 0 &&
                       userInput.size() > expected_prefix_addplayer.size() &&
                       userInput[userInput.size() - 1] == '>') {
            if (open_bracket != std::string::npos && close_bracket != std::string::npos &&
                open_bracket < close_bracket) {

                string playerName = userInput.substr(open_bracket + 1, close_bracket - open_bracket - 1);


                if (playerList.size() < 6) {
                    cout << "Loading player with name: " << playerName << std::endl;
                    // Dynamically allocate a new Player object
                    auto* player1 = new Player();
                    player1->setName(playerName);

                    // Store the pointer in playerList
                    playerList.push_back(player1);

                    cout << "You have successfully added player " << playerName << " into the game" <<std::endl;
                    cout << "Current player count: " << playerList.size() << "\n"<<std::endl;

                }

                 if(playerList.size() >= 6){

                     cout << "You have reached the maximum capacity of players allowed in the game. "<< "\nCurrent player count: " << playerList.size() << "\n"<<std::endl;

                }
                }

            }

        else if (userInput == "gamestart") {

                if(playerList.size() < 2){
                    std::cout << "Add another player name. A minimum of 2 players are required :\n";

                }

                else if(playerList.size() >= 2 ){

                    // Distribute territories to players as well as give them 50 armies in their reinforcement pool
                    int currentPlayerIndex = 0;
                    for (Territory* territory : *mapTest->territories) {

                        Player* currentPlayer = playerList[currentPlayerIndex];

                        vector<Territory*>& playerTerritories = currentPlayer->getTerritoryList();

                        playerTerritories.push_back(territory);

                        int armies = 50;

                        //give armies
                        currentPlayer->setReinforcementPool(&armies);

                        // Move to the next player to add his territory
                        currentPlayerIndex = (currentPlayerIndex + 1) % playerList.size();
                    }

                    // Loop over players
                    for (Player* currentPlayer : playerList) {
                        //players draw cards
                        for (int i = 0; i < 2; ++i) {
                            Cards card = deck.draw();
                            currentPlayer->getHand()->addCard(card);
//                            cout << "Drew a " << card.getTypeAsString() << " card." << endl;
//                            cout << "Deck size: " << deck.getCardNum() << endl;
                        }
                    }

                    // Display the result
                    for (Player* player : playerList) {
                        cout << "Player " << player->getPlayerName()<< " owns territories: ";
                        cout << "Number of armies " << *(player->getReinforcementPool()) <<" ";
                        cout << "cards " << player->getHand()->getCardNum() <<" ";
                        cout << "Deck size: " << deck.getCardNum() << endl;

                        for (Territory* territory : player->getTerritoryList()) {
                            std::cout << territory->getName() << ", ";
                        }
                        std::cout << std::endl;
                    }



                }

                //play();

        }

        else if (userInput == "5") {
                    mapTest->territories->clear();
                    delete mapTest;
                    std::cout << "Exiting\n";



        }

        else {
                std::cout << "Invalid choice. Please enter a valid option.\n";

        }

        continue;
        }

    }



