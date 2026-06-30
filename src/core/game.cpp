#include "guessnumber/core/game.hpp"

#include "guessnumber/base/Logger.hpp"
#include "guessnumber/base/FormatTime.hpp"

#include "guessnumber/core/model/GameRecord.hpp"

#include <random>
#include <optional>
#include <string>

Game::Game(Input& input, Output& output, History& history, Config config):_input(input), _output(output), _history(history), _config(config){}

void Game::Start_Run(){
    _output.showWelcome(_config);
    _history.load();
    LOG_INFO("New game session: range [" << _config.minNum << "," << _config.maxNum << "], max attempts " << _config.attempts);
    _output.showRecordBoard(_history.getTop(3));
    do{
        auto playResult = playOnce();
        if(!playResult.has_value())break;
        _history.appendRecord(playResult.value());
    }while(_input.askPlayAgain());
    _history.save();
    LOG_INFO("Game session ended");
}

std::optional<GameRecord> Game::playOnce(){
    LOG_INFO("New round started");
    int secret = genSecrect();
    std::string start_time = getFormatTime();
    int temp = 0;
    int invalidTemp = 0;
    while(temp < _config.attempts){
        auto guess = _input.getGuess();
        if(!guess.has_value()){
            LOG_WARN("Invalid guess (not a number or EOF)");
            invalidTemp++;
            if(invalidTemp >= 8){
                LOG_WARN("Ended game due to too many invalid guess");
                _output.showError("Too many invalid guess! Kick you out.");
                return std::nullopt;
            }
            _output.showError("Invalid guess, please try again.");
            continue;
        }

        int ans = guess.value();

        if(ans > _config.maxNum || ans < _config.minNum){
            LOG_WARN("Invalid guess (out of range)");
            invalidTemp++;
            if(invalidTemp >= 8){
                LOG_WARN("Ended game due to too many invalid guess");
                _output.showError("Too many invalid guess! Kick you out.");
                return std::nullopt;
            }
            char msg[100]; //unsafe! need to be repalce.
            sprintf(msg, "Out of range. please guess between %d and %d.", _config.minNum, _config.maxNum);
            _output.showError(msg);
            continue;
        }

        temp++;
        invalidTemp = 0;

        if(ans > secret){
            _output.showTooHigh(ans - secret);
        }else if(ans < secret){
            _output.showTooLow(secret - ans);
        }else{
            LOG_INFO("Correct guess in " << temp << " attemps. Game round finished");
            _output.showSuccess(temp);
            return GameRecord(start_time, _config, secret, temp, true);
            
        }
    }
    LOG_INFO("Game failed with secrect " << secret << ". Game round finished");
    _output.showGameOver(secret);
    return GameRecord(start_time, _config, secret, temp, false);
}

int Game::genSecrect() const{
    try{
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(_config.minNum, _config.maxNum);
        return dist(gen);
    }catch(std::exception& e){
        LOG_FATAL("Failed to initialize secret generator: " << e.what());
        return 0;
    }
}