#include <GameEngine.h>
#include "../extraMethods/extraMethods.h"

void testTournament(){

    auto *engine = new GameEngine();

    cout << "Startup Phase..." << endl << endl;

    cout << "write '-console' to read from console" << endl;
    cout << "write '-file <filename>' to read from file" << endl;

    string input;
    cout << "Enter command:";
    getline(cin, input);

    // Tokenize input
    std::vector<std::string> inputTokens = splitString(input);
    std::string userInput = inputTokens.at(0);

    engine->startupPhase(engine, userInput);

}