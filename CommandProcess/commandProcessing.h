#pragma once
#include "LoggingObserver.h"
#include "GameEngine.h"
#include <string>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class Command : public ILoggable, public Subject{
    public:
    //Default constructor
    Command();
    //Constructor
    Command(string *command, string *effect);
    Command(Command &command);
    ~Command();
    Command* save(string *effect);
    string stringToLog() override; 
    void Notify(); 
    friend ostream &operator << (ostream &output, Command &obj);
    enum class commandType { loadmap, validatemap, addplayer, gamestart, replay, quit, gameend,tournament};
    private:
    string* command; 
    string* effect;
    static LogObserver* obs;
};

class CommandProcessor : public ILoggable, public Subject {
    public:
        friend ostream &operator << (ostream &output, CommandProcessor &obj);
        CommandProcessor& operator=(const CommandProcessor &commandProcessor); //dom changed
    CommandProcessor();
    ~CommandProcessor();
    CommandProcessor(CommandProcessor &commandProcessor);
    Command* getCommand();
    bool validate(string command);
    void Notify();
    

    private:
    vector <Command*> commandList;
    static LogObserver* observ;

    protected:
    virtual string readCommand();
    Command* saveCommand(string* command, string* effect);

};

class FileCommandProcessorAdapter : public CommandProcessor{
    public: 
        friend ostream &operator << (ostream &output, FileCommandProcessorAdapter &obj);
        FileCommandProcessorAdapter &operator=(const FileCommandProcessorAdapter &t);
        FileCommandProcessorAdapter();
        ~FileCommandProcessorAdapter();
        string readCommand();
        Command* passCommand();
    private:
    FileLineReader* reader; 
};

class FileLineReader{
public: 
    friend ostream &operator << (ostream &output, FileLineReader &obj);
    FileLineReader &operator=(const FileLineReader &t); //dom changed
    FileLineReader();
    FileLineReader(FileLineReader &lineReader);
    ~FileLineReader();
};