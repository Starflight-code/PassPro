#pragma once

#include "DatabaseObject.cpp"
#include "PasswordEntry.cpp"
#include "nlohmann/json.hpp"
#include <iostream>
#include <vector>

class DatabaseManager {
  private:
  std::vector<PasswordEntry> entries;
  friend class DatabaseManagerTest;

  public:
  const std::vector<PasswordEntry>& getEntries() const {
    return entries;
  }

  // Add a method to add entries
  void addEntry(const PasswordEntry& entry) {
    entries.push_back(entry);
  }

  /**
   * @brief writeDB: Sanitizes current DB state, converts
   * to JSON, encrypts and pushes it to the disk
   */
  void writeDB() {
    DatabaseObject db;
    for(int i = 0; i < entries.size(); i++) {
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
    // Comment out line 43 fir testing, uncomment line 44 for implimentation
    //std::cout << nlohmann::json::string_t(j);
    std::cout << j.dump();
  }
};