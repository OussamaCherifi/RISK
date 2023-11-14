#ifndef RISK_COMMANDPROCESSING_H
#define RISK_COMMANDPROCESSING_H
#include <string>
#include <vector>
#include "../GameEngine/GameEngine.h"
#include "../Map/Map.h"
#include "../LoggingObserver/LoggingObserver.h"
using namespace std;
class GameEngine;

class Command : public Subject, public ILoggable {

    public:
    Command();//Constructors
    Command(std::string* command, std::string* effect);
    Command(const Command& something);
    ~Command(); //Destructor

    Command* saveEffect(std::string* effect);
    friend std::ostream& operator<<(std::ostream& os, const Command& command);
    string stringToLog();

    //Getters & Setters
    std::string* getEffect();
    std::string* getCommand();

    private:
    std::string* effect;
    std::string* command;
};

class CommandProcessor : public Subject, public ILoggable{
    public:
     CommandProcessor();
    CommandProcessor(const CommandProcessor& something);
    ~CommandProcessor();
    string stringToLog();
    Command * getCommand(GameEngine& ge);
    friend std::ostream& operator<<(std::ostream& os, const CommandProcessor& processor);

    private:
    std::vector<Command*>* commands; 

    protected:
    virtual std::string readCommand();
    Command* saveCommand(std::string* command, std::string* effect);
};

class FileLineReader  {
    public:
    FileLineReader();
    FileLineReader(const FileLineReader& something);
    ~FileLineReader();
    void readLineFromFile(std::string& fileName);
    friend std::ostream& operator<<(std::ostream& os, const FileLineReader& reader);
    std::vector<std::string*>* getLines();

    private:
    std::vector <std::string*>* lines; 
};
class FileCommandProcessorAdapter : public CommandProcessor {
    public : 
    FileCommandProcessorAdapter();
    FileCommandProcessorAdapter(const FileCommandProcessorAdapter& something);
    ~FileCommandProcessorAdapter();
     std::string readCommand() override;
    friend std::ostream& operator<<(std::ostream& os, const FileCommandProcessorAdapter& adapter);
    FileLineReader* getFileLineReader();

    private:
    static int current; 
    FileLineReader* flr;
};


#endif 
