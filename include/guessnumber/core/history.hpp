#pragma once

#include <string>
#include <sstream>
#include <vector>
#include "guessnumber/core/model/GameRecord.hpp"
#include "nlohmann/json.hpp"

class History{
private:
    std::string _version;
    std::vector<GameRecord> _records;
    std::string _filepath;
    bool _isDirty = false;
public:
    explicit History(std::string dataDir);

    bool load();
    bool save();
    bool appendRecord(const GameRecord& record);
    std::vector<GameRecord> getRecords() const;
    std::vector<GameRecord> getTop(const int top) const;
};