#pragma once

#include "nlohmann/json.hpp"

bool jsonLoad(nlohmann::json& j, const char filepath[]);

bool jsonSave(const nlohmann::json& j, const char filepath[]);