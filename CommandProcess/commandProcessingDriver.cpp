#include "commandProcessing.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
using namespace std;

CommandProcessor::CommandProcessor() {};
Command::Command(){};


//Implementing copy constructor
CommandProcessor::CommandProcessor(CommandProcessor &commandProcessor) {
    this->commandList = commandProcessor.commandList;
}

//Stream operators
ostream &operator << (ostream &output, Command &obj) {
    output << "command processed right now" <<endl;
    return output;
}
ostream &operator << (ostream &output, CommandProcessor &obj) {
    output << "command processer right now" <<endl;
    return output;
}
ostream &operator << (ostream &output, FileCommandProcessorAdapter &obj) {
    output << "file command processor adapter right now" <<endl;
    return output;
}
ostream &operator << (ostream &output, FileLineReader &obj){
    output << "reading file right now" <<endl;
    return output;
}

//Desturctor
CommandProcessor::~CommandProcessor() {
    for (Command* command : commandList) {
        delete command;
    }
    commandList.clear(); // Optionally clear the vector
}

string CommandProcessor::readCommand(){
    string command;
    cout<< "enter command";
    getline(cin,command);
};



