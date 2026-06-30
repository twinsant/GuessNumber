#pragma once

#include "nlohmann/json.hpp"

struct Config{
    int minNum = 1;
    int maxNum = 100;
    int attempts = 7;
};

void to_json(nlohmann::json& j, const Config& c);

void from_json(const nlohmann::json& j, Config& c);