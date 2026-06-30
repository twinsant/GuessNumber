#pragma once

#include "guessnumber/core/model/Config.hpp"
#include "guessnumber/core/model/GameRecord.hpp"
#include <optional>
#include <vector>
#include <string>

class Input{
public:
    virtual ~Input() = default;
    virtual std::optional<int> getGuess() = 0;
    virtual bool askPlayAgain() = 0;
};

class Output{
public:
    virtual ~Output() = default;
    virtual void showWelcome(Config config) = 0;
    virtual void showRecordBoard(const std::vector<GameRecord>& tops) = 0;
    virtual void showTooHigh(int delta) = 0;
    virtual void showTooLow(int delta) = 0;
    virtual void showSuccess(int attempt) = 0;
    virtual void showGameOver(int secret) = 0;
    virtual void showError(const char msg[]) = 0;
};