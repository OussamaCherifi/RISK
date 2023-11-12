#include <iostream>
#include "commandProcessing.h"
using namespace std; 


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
    return this;
}

string* Command::getEffect() {
    return effect;
}
string* Command::getCommand() {
    return command;
}
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
    return updatedCommand;
}

// Command* CommandProcessor::getCommand(GameEngine& ge) {
//     while(true) {
//         string commandString = this->readCommand();
//         string effect;
//         Command* newCommand = saveCommand(new string(commandString), new string(effect));
//         std::vector<std::string> commandTokens = splitString(commandString);
//         if(validate(commandTokens.at(0), ge)) return newCommand;
//         else {
//             cout << "Invalid command. \"" << commandString << "\" Please try again." << endl;
//             newCommand->saveEffect(new string("Invalid CommandProcessing \"" + commandString  +"\""));
//         }
//     }
// }

// bool CommandProcessor::validate(const string& commandString, GameEngine& ge) {
//     return ge.validateInput(commandString);
// }
