#pragma once

#include <string>
#include "nlohmann/json.hpp"
#include "guessNumber/core/model/Config.hpp"

struct GameRecord{
    std::string date;
    Config config;
    int secret, attempt;
    bool won;

    GameRecord(std::string gdate, Config gconfig, int gsecrect, int gattempt, bool gwon):
        date(gdate), config(gconfig), secret(gsecrect), attempt(gattempt), won(gwon){}

    GameRecord() = default;
};

void to_json(nlohmann::json& j, const GameRecord& r);

void from_json(const nlohmann::json& j, GameRecord& r);