#pragma once

#include "PasswordEntry.cpp"
#include <iostream>
#include <vector>
#include "nlohmann/json.hpp"
#include "DatabaseObject.cpp"

class DatabaseManager {
    std::vector<PasswordEntry> entries;

    void writeDB() {
        DatabaseObject db;
        for (int i = 0; i < entries.size(); i++) {
            db.addEntry(entries[i]);
        }
        nlohmann::json j;
        j["passwords"] = db.password;
        std::cout << nlohmann::json::string_t(j);
    }
};
