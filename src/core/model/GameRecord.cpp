#include "guessnumber/core/model/GameRecord.hpp"

void to_json(nlohmann::json& j, const GameRecord& r){
    j["date"] = r.date;
    j["config"] = r.config;
    j["secret"] = r.secret;
    j["attempt"] = r.attempt;
    j["won"] = r.won;
}

void from_json(const nlohmann::json& j, GameRecord& r){
    j.at("date").get_to(r.date);
    j.at("config").get_to(r.config);
    j.at("secret").get_to(r.secret);
    j.at("attempt").get_to(r.attempt);
    j.at("won").get_to(r.won);
}