#include <iostream>
#include <fstream>
#include "commandProcessing.h"
#include "../extraMethods/extraMethods.h"

using namespace std;

int FileCommandProcessorAdapter::current = 0;
class Tournament;
class PlayerStrategy;
class Player;




ostream &operator<<(ostream &os, const Command &command)
{
    os << "{Command: " << *(command.command);
    os << ", Effect: " << *(command.effect) << "}";
    return os;
}

ostream &operator<<(ostream &os, const CommandProcessor &processor)
{
    os << "Commands: " << endl;
    for (Command *command : *processor.commands)
    {
        os << "_" << *command << endl;
    }
    return os;
}

ostream &operator<<(ostream &os, const FileLineReader &reader)
{
    os << "FileLineReader's Lines: " << endl;
    for (string *line : *reader.lines)
    {
        os << *line << endl;
    }
    return os;
}

ostream &operator<<(ostream &os, const FileCommandProcessorAdapter &adapter)
{
    os << "FileCommandProcessorAdapter: " << endl;
    os << *adapter.flr;
    return os;
}
std::vector<std::string> splitString(const std::string &s);
// Command Class
Command::Command()
{
    this->command = new string("empty command");
    this->effect = new string("empty effect");
}

Command::Command(string *command, string *effect)
{
    this->command = command;
    this->effect = effect;
}

Command::Command(const Command &other)
{
    this->command = other.command;
    this->effect = other.effect;
}

Command::~Command()
{
    delete command;
    delete effect;
}

Command *Command::saveEffect(string *effect)
{
    this->effect = effect;
    Notify(this);
    return this;
}
string Command::stringToLog()
{
    return string("[Command]\tEffect is: " + *effect);
}
string *Command::getEffect()
{
    return effect;
}
string *Command::getCommand()
{
    return command;
}

// Command Processor
CommandProcessor::CommandProcessor()
{
    this->commands = new vector<Command *>();
}
CommandProcessor::CommandProcessor(const CommandProcessor &something)
{
    this->commands = something.commands;
}
CommandProcessor::~CommandProcessor()
{
    delete commands;
}

string CommandProcessor::readCommand()
{
    cout << "enter command" << endl;
    string command;
    getline(cin, command);
    return command;
}

Command *CommandProcessor::saveCommand(string *command, string *effect)
{
    auto *updatedCommand = new Command(command, effect);
    commands->push_back(updatedCommand);
    Notify(this);
    return updatedCommand;
}

Command *CommandProcessor::getCommand(GameEngine &ge)
{
    while (true)
    {
        string commandString = this->readCommand();
        string effect;
        Command *newCommand = saveCommand(new string(commandString), new string(effect));
        std::vector<std::string> commandTokens = splitString(commandString);
        return newCommand;
        if (validate(commandTokens.at(0), ge))
            return newCommand;
        else
        {
            cout << "Invalid command. \"" << commandString << "\" Please try again." << endl;
            newCommand->saveEffect(new string("Invalid CommandProcessing \"" + commandString + "\""));
        }
    }
}

bool CommandProcessor::validate(const string &commandString, GameEngine &gameEngine)
{
    return gameEngine.handle(commandString);
}

string CommandProcessor::stringToLog()
{
    return string("[CommandProcessor]\tAdded new command: " + *commands->back()->getCommand());
}

FileLineReader::FileLineReader()
{
    this->lines = new vector<string *>();
}

FileLineReader::FileLineReader(const FileLineReader &something)
{
    this->lines = something.lines;
}

FileLineReader::~FileLineReader()
{
    delete lines;
}

void FileLineReader::readLineFromFile(string &fileName)
{
    string line;
    ifstream file("../Saves/" + fileName);
    while (getline(file, line))
    {
        lines->push_back(new string(line));
        cout << line << endl;
    }
    if (!file.is_open())
    {
        cout << "Error opening file: " << fileName << ". Please try again." << endl
             << endl
             << endl;
        return;
    }
    file.close();
}

vector<string *> *FileLineReader::getLines()
{
    return lines;
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter()
{
    this->flr = new FileLineReader();
}

FileLineReader *FileCommandProcessorAdapter::getFileLineReader()
{
    return flr;
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter &other)
{
    this->flr = other.flr;
}

FileCommandProcessorAdapter::~FileCommandProcessorAdapter()
{
    delete flr;
}

string FileCommandProcessorAdapter::readCommand()
{
    vector<string *> *lines = flr->getLines();

    // Check if lines is not empty and currentLine is within bounds
    if (lines != nullptr && !lines->empty() && current < lines->size())
    {
        string line = *(lines->at(current));
        current++;
        return line;
    }
    else
    {
        cout << "no lines left" << endl;
        return "";
    }
}

void Tournament::processMaps(const vector<std::string>& info) {

    vector<string> m = tokenize(info[2], ',');
    vector<string*> mapsNames;
    for(string s : m) {
        mapsNames.push_back(new string(s));
    }
    this->maps = mapsNames;
    string toPrint = "Tournament Mode : \nM: ";
    for(int i = 0; i < m.size(); i++) {
        toPrint += m[i] + ", ";
    }
    this->tournametInfo += toPrint + "\n";

}

void Tournament::porcessStrategy(const vector<std::string>& info){

    string toPrint = "";
    vector<string> players = tokenize(info[4], ',');

    toPrint += "P: ";

    vector<PlayerStrategy*> playerStrategies;
    for(int i = 0; i < players.size(); i++) {
//        string name = players[i] + to_string(i);
        string name = players[i];
        Player* p = new Player();
        p->setName(name);

        if (players[i] == "AGGRESSIVE") {
            playerStrategies.push_back(new AggressivePlayerStrategy(p));
        }
        else if (players[i] == "NEUTRAL") {
            playerStrategies.push_back(new NeutralPlayerStrategy(p));
        }
        else if (players[i] == "BENEVOLENT") {
            playerStrategies.push_back(new BenevolentPlayerStrategy(p));
        }
        else if (players[i] == "CHEATER") {
            playerStrategies.push_back(new CheaterPlayerStrategy(p));
        }

        toPrint += name + ", ";
    }
    this->playerStrategies = playerStrategies;

    this->tournametInfo += toPrint;


}

Tournament::Tournament(vector<string> info){

    //process maps and strategies:
    processMaps(info);
    porcessStrategy(info);

    //setnumGames
    int numG = stoi(info[6]);
    this->totalGames = new int(numG);
    this->tournametInfo += "\nG: " + info[6];

    //set turns
    int numT = stoi(info[8]);
    this->turns = new int(numT);
    this->tournametInfo += "\nD: " + info[8] + "\n";

    cout<<tournametInfo<<"\n"<< endl;

    printDataToFile();

}
string Tournament::validateTournament(vector<string> input) {
    vector<string> players = tokenize(input[4], ',');

    //assessing size of our input command
    if(input.size() != 9) {
        return "invalid user input";

    }

    //assessing input command
    if(input[1] != "-M" || input[3] != "-P" || input[5] != "-G" || input[7] != "-D") {
        return "invalid user input";

    }

    //assesing number of maps
    vector<string> maps = tokenize(input[2], ',');
    if (maps.size() < 1 || maps.size() > 5) {
        return "invalid number of maps";

    }

    //assessing number of players (2-4)
    if (players.size() < 2 || players.size() > 4) {
        return "invalid number of players";

    }

    //checking player types
    for(int i = 0; i < players.size(); i++) {
        if (players[i] != "AGGRESSIVE" && players[i] != "BENEVOLENT" && players[i] != "CHEATER" && players[i] != "NEUTRAL") {
            return "invalid player types";
        }
    }

    //number of games is between 1 and 5
    try {
        int numOfGames = stoi(input[6]);
        if(numOfGames < 1 || numOfGames > 5) {
            return "Invalid number of tournament";

        }
    }
    catch(int n) {
        return "invalid number of games";
    }

    //Number of turns is between 10 and 50
    try {
        int numOfTurns = stoi(input[8]);
        if (numOfTurns < 10 || numOfTurns > 50) {
            return "invalid number of game turns";
        }
    }
    catch (int n) {
        return "invalid input for number of game turns";
    }

    return "valid";

}


void Tournament::printDataToFile() {

    ofstream f;
    f.open("C:\\Users\\mack\\Desktop\\fall 2023\\345\\A3-COMP345\\Tournament\\tournamentResult.txt");

    f << this->tournametInfo;
    f.close();
}

int* Tournament::getTotalGames(){
    return this->totalGames;
}

int* Tournament::getTurns(){
    return this->turns;
}


vector<string*> Tournament::getMaps(){
    return this->maps;
}

vector<PlayerStrategy*> Tournament::getStrategies() {
    return this->playerStrategies;
}

void Tournament::setMaps(vector<string*> maps){
    this->maps = maps;
}

void Tournament::setStrategies(vector<PlayerStrategy*> playerStrat){
    this->playerStrategies = playerStrat;
}


void Tournament::setTurns(int num){
    this->turns = new int(num);
}

void Tournament::setTotalGames(int num){
    this->totalGames = new int(num);
}




