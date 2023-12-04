#ifndef RISK_COMMANDPROCESSING_H
#define RISK_COMMANDPROCESSING_H
#include <string>
#include <vector>
#include "../GameEngine/GameEngine.h"
#include "Map.h"
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
    static bool validate(const std::string& command, GameEngine& gameEngine);

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

class Tournament{

private:
    vector<PlayerStrategy*> playerStrategies;
    vector<string*> maps;
    int* totalGames;
    int* turns;
    string tournametInfo;


public:
    Tournament(vector<string> Info);
    vector<PlayerStrategy*> getStrategies();
    vector<string*> getMaps();
    int* getTurns();
    int* getTotalGames();

    void setMaps(vector<string*> maps);
    void setStrategies(vector<PlayerStrategy*> strategy);
    void setTurns(int numberOfturns);
    void setTotalGames(int numberOfGames);

    void printTournamentResult();
    void processMaps(const vector<string>& gameInfo);
    void porcessStrategy(const vector<string>& gameInfo);
    string validateTournament(vector<string> inputArr);

    void printDataToFile();


};




#endif 
