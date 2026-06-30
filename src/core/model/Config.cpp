#include "guessnumber/core/model/Config.hpp"

void to_json(nlohmann::json& j, const Config& c){
    j["minNum"] = c.minNum;
    j["maxNum"] = c.maxNum;
    j["maxAttempts"] = c.attempts;
}

void from_json(const nlohmann::json& j, Config& c){
    j.at("minNum").get_to(c.minNum);
    j.at("maxNum").get_to(c.maxNum);
    j.at("maxAttempts").get_to(c.attempts);
}