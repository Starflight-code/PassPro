#pragma once

#include "PasswordEntry.cpp"
#include <iostream>
#include <vector>
#include "nlohmann/json.hpp"
#include "DatabaseObject.cpp"

class DatabaseManager {
    std::vector<PasswordEntry> entries;

    /**
     * @brief writeDB: Sanitizes current DB state, converts
     * to JSON, encrypts and pushes it to the disk
     */
    void writeDB() {
        DatabaseObject db;
        for (int i = 0; i < entries.size(); i++) {
            db.addEntry(entries[i]);
        }
        nlohmann::json j;
        j["names"] = db.name;
        j["urls"] = db.url;
        j["s_urls"] = db.searchableURL;
        j["notes"] = db.notes;
        j["usernames"] = db.username;
        j["passwords"] = db.password;

        std::cout << "JSON Data Stored (DEVELOPMENT ONLY / DO NOT LEAVE THIS IN PRODUCTION)";
        std::cout << nlohmann::json::string_t(j);
    }
};
