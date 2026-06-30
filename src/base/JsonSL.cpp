#include <fstream>
#include <sstream>
#include <cstdio>
#include <stdexcept>

#include "guessnumber/base/JsonSL.hpp"

#include "nlohmann/json.hpp"
#include "guessnumber/base/Logger.hpp"

bool jsonLoad(nlohmann::json& j, const char filepath[]){
    std::ifstream in;
    in.open(filepath, std::ios::in);
    if(!in.is_open()){
        return false;
    }
    in >> j;
    return true;
}

bool jsonSave(const nlohmann::json& j, const char filepath[]){
    std::string temp_file = std::string(filepath) + ".temp";
    remove(temp_file.c_str());
    {
        std::ofstream out;
        out.open(temp_file, std::ios::out);
        if(!out.is_open()){
            LOG_ERROR("Failed to open temp file for writing: " << temp_file);
            return false;
        }
        out.clear();
        out << j.dump(4);
        out.close();
        if(!out.good()){
            LOG_ERROR("Failed to write data to temp file: " << temp_file)
            remove(temp_file.c_str());
            return false;
        }
    }
    if(std::rename(temp_file.c_str(), filepath) != 0){
        LOG_ERROR("Failed to rename temp file to " << filepath);
        remove(temp_file.c_str());
        return false;
    }
    remove(temp_file.c_str());
    return true;
}