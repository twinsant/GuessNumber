#pragma once

#include <optional>

#include "guessnumber/core/model/Config.hpp"
#include "guessnumber/core/io_interface.hpp"
#include "guessnumber/core/history.hpp"
#include "guessnumber/core/model/GameRecord.hpp"

class Game{
private:
    Input& _input;
    Output& _output;
    History& _history;
    Config _config;

    std::optional<GameRecord> playOnce();
    int genSecrect() const;
    
public:
    Game(Input& input, Output& output, History& history, Config config = {});
    void Start_Run();
};