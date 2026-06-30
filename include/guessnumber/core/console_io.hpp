#pragma once

#include "io_interface.hpp"
#include "guessnumber/core/model/Config.hpp"
#include "guessnumber/core/model/GameRecord.hpp"

#include <vector>

class ConsoleInput : public Input{
public:
    std::optional<int> getGuess() override;
    bool askPlayAgain() override;
};

class ConsoleOutput : public Output{
public:
    void showWelcome(Config config) override;
    void showRecordBoard(const std::vector<GameRecord>& tops) override;
    void showTooHigh(int delta) override;
    void showTooLow(int delta) override;
    void showSuccess(int attempt) override;
    void showGameOver(int secret) override;
    void showError(const char msg[]) override;
};