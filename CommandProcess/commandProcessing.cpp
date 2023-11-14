#include <iostream>
#include <fstream>
#include "commandProcessing.h"
#include "../GameUtils/gameutil.h"
using namespace std; 


int FileCommandProcessorAdapter::current = 0;

ostream& operator<<(ostream& os, const Command& command) {
    os << "{Command: " << *(command.command);
    os << ", Effect: " << *(command.effect) << "}";
    return os;
}

ostream& operator<<(ostream& os, const CommandProcessor& processor) {
    os << "Commands: " << endl;
    for(Command* command : *processor.commands) {
        os << "_" << *command << endl;
    }
    return os;
}

ostream& operator<<(ostream& os, const FileLineReader& reader) {
    os << "FileLineReader's Lines: " << endl;
    for(string* line : *reader.lines) {
        os << *line << endl;
    }
    return os;
}

ostream& operator<<(ostream& os, const FileCommandProcessorAdapter& adapter) {
    os << "FileCommandProcessorAdapter: " << endl;
    os << *adapter.flr;
    return os;
}
std::vector<std::string> splitString(const std::string& s);
//Command Class
Command::Command() {
    this->command = new string("empty command");
    this->effect = new string("empty effect");
}

Command::Command(string* command, string* effect) {
    this->command = command;
    this->effect = effect;
}

Command::Command(const Command& other) {
    this->command = other.command;
    this->effect = other.effect;
}

Command::~Command() {
    delete command;
    delete effect;
}

Command* Command::saveEffect(string* effect) {
    this->effect = effect;
    Notify(this);
    return this;
}
string Command::stringToLog()
{
    return string("Effect is: " + *effect);
}
string* Command::getEffect() {
    return effect;
}
string* Command::getCommand() {
    return command;
}

//Command Processor
CommandProcessor::CommandProcessor(){
    this->commands = new vector<Command*>();
}
CommandProcessor::CommandProcessor(const CommandProcessor& something) {
    this->commands = something.commands;
}
CommandProcessor::~CommandProcessor() {
    delete commands;
}
string CommandProcessor::readCommand(){
    cout<< "enter command"<< endl; 
    string command;
    getline(cin,command);
    return command; 
}
Command* CommandProcessor::saveCommand(string* command, string* effect) {
    auto* updatedCommand = new Command(command, effect);
    commands->push_back(updatedCommand);
    Notify(this);
    return updatedCommand;
}

Command* CommandProcessor::getCommand(GameEngine& ge) {
    while(true) {
        string commandString = this->readCommand();
        string effect;
        Command* newCommand = saveCommand(new string(commandString), new string(effect));
        std::vector<std::string> commandTokens = splitString(commandString);
        if(validate(commandTokens.at(0), ge)) return newCommand;
        else {
            cout << "Invalid command. \"" << commandString << "\" Please try again." << endl;
            newCommand->saveEffect(new string("Invalid CommandProcessing \"" + commandString  +"\""));
        }
    }
}

string CommandProcessor::stringToLog()
{
    return string("Added new command: " + *commands->back()->getCommand());
}



FileLineReader::FileLineReader() {
    this->lines = new vector<string*>();
}

FileLineReader::FileLineReader(const FileLineReader& something) {
    this->lines = something.lines;
}

FileLineReader::~FileLineReader() {
    delete lines;
}

void FileLineReader::readLineFromFile(string& fileName) {
    string line;
    ifstream file("../Saves/" + fileName);
      while (getline(file, line)) {
        lines->push_back(new string(line));
        cout << line << endl;
        }
    if (!file.is_open()) {
        cout << "Error opening file: " << fileName << ". Please try again." << endl << endl << endl;
        return;
    }
    file.close();
}

vector<string*>* FileLineReader::getLines() {
    return lines;
}


FileCommandProcessorAdapter::FileCommandProcessorAdapter() {
    this->flr = new FileLineReader();
}

FileLineReader* FileCommandProcessorAdapter::getFileLineReader() {
    return flr;
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter& other) {
    this->flr = other.flr;
}

FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {
    delete flr;
}

string FileCommandProcessorAdapter::readCommand() {
    vector<string*>* lines = flr->getLines();

    // Check if lines is not empty and currentLine is within bounds
    if (lines != nullptr && !lines->empty() && current < lines->size()) {
        string line = *(lines->at(current));
        current++;
        return line;
    } else {
        cout << "no lines left" << endl;
        return "";
    }
}