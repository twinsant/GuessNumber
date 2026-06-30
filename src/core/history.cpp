#include "guessnumber/core/history.hpp"

#include <algorithm>
#include <vector>
#include <stdexcept>
#include "guessnumber/version.h"
#include "guessnumber/base/JsonSL.hpp"
#include "guessnumber/base/Logger.hpp"
#include "nlohmann/json.hpp"

History::History(std::string dataDir):
    _version(std::to_string(GUESSNUMBER_VERSION_MAJOR) + "." + std::to_string(GUESSNUMBER_VERSION_MINOR) + "." + std::to_string(GUESSNUMBER_VERSION_PATCH)),
    _filepath(dataDir + "/history.json"){}

bool History::load(){
    nlohmann::json j;
    if(!jsonLoad(j, _filepath.c_str())){
        if(!save()){
            LOG_ERROR("Failed to create an empty history file");
            return false;
        }
        return true;
    }else{
        if(j.contains("records")){
            _records = j.at("records").get<std::vector<GameRecord>>();
        }else{
            LOG_ERROR("Failed to load history from: " << _filepath);
            return false;
        }
        return true;
    }
}

bool History::save(){
    if(!_isDirty)return true;

    nlohmann::json j;
    j["records"] = _records;
    j["version"] = _version;

    bool flag = jsonSave(j, _filepath.c_str());
    if(flag){
        _isDirty = false;
        LOG_INFO("History saved");
    }else{
        LOG_ERROR("Failed to save history");
    }
    return flag;
}

bool History::appendRecord(const GameRecord& record){
    _records.push_back(record);
    _isDirty = true;
    // may be replaced by multiple save strategy someday, such as timely or process-sensitive
    return save();
}

std::vector<GameRecord> History::getRecords() const{
    return _records;
}

std::vector<GameRecord> History::getTop(const int top) const
{
    if(top <= 0)return std::vector<GameRecord>();
    std::vector<GameRecord> wins;
    for(auto& r : _records){
        if(r.won)wins.push_back(r);
    }
    std::sort(wins.begin(), wins.end(), [](const GameRecord& r_a, const GameRecord& r_b){return r_a.attempt < r_b.attempt;});
    if(wins.size() > top)wins.resize(top);
    return wins;
}