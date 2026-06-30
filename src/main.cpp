#include <stdio.h>
#include "guessnumber/version.h"
#include "guessnumber/core/io_interface.hpp"
#include "guessnumber/core/console_io.hpp"
#include "guessnumber/core/model/Config.hpp"
#include "guessnumber/core/game.hpp"
#include "guessnumber/core/history.hpp"
#include "guessnumber/base/Logger.hpp"

int main(){
    const char* home = std::getenv("HOME");
    std::string logDir = home ? std::string(home) + "/.guessNumber" : "./.guessNumber";
    std::system(("mkdir -p " + logDir).c_str());
    Logger::Instance().setMinLevel(LogLevel::INFO);
    Logger::Instance().setShowFile(false);
    Logger::Instance().enableFile((logDir + "/game.log").c_str());

    Config config;
    ConsoleInput consoleInput;
    ConsoleOutput consoleOutput;
    
    std::string dataDir = logDir;
    std::system(("mkdir -p " + dataDir).c_str());
    History history(dataDir);

    Game game(consoleInput, consoleOutput, history, config);

    LOG_INFO("===Game start===");
    game.Start_Run();
    LOG_INFO("===Game exited normally===")
    return 0;
}
