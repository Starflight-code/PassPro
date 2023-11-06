#pragma once

#include "DatabaseObject.cpp"
#include "PasswordEntry.cpp"
#include "nlohmann/json.hpp"
#include <iostream>
#include <vector>

class DatabaseManager {
  std::vector<PasswordEntry> entries;

  /**
   * @brief generateJSON: Generates JSON from embedded entries data
   * @return nlohmann::json object containing all data from entries vector
   */
  nlohmann::json sanitizeJSON() {
    DatabaseObject db;
    PasswordEntry n1 = PasswordEntry("pass", "name", "url", "user", "notes");
    PasswordEntry n2 = PasswordEntry("pass2", "name2", "url2", "user2", "notes2");
    PasswordEntry n3 = PasswordEntry("pass3", "name3", "url3", "user3", "notes3");

    for(int i = 0; i < entries.size(); i++) {
      db.addEntry(entries[i]);
    }
    db.addEntry(n1);
    db.addEntry(n2);
    db.addEntry(n3);
    nlohmann::json j;
    j["names"] = db.name;
    j["urls"] = db.url;
    j["s_urls"] = db.searchableURL;
    j["notes"] = db.notes;
    j["usernames"] = db.username;
    j["passwords"] = db.password;
    return j;
  }

  std::vector<PasswordEntry> desanitizeJSON(nlohmann::json jsonObject) {
    std::vector<PasswordEntry> entries;
    for(int i = 0; i < jsonObject["names"].size(); i++) {
      entries.push_back(PasswordEntry(
          jsonObject["passwords"][i],
          jsonObject["names"][i],
          jsonObject["urls"][i],
          jsonObject["usernames"][i],
          jsonObject["notes"][i]));
    }
    return entries;
  }

  public:
  /**
   * @brief writeDB: Sanitizes current DB state, converts
   * to JSON, encrypts and pushes it to the disk
   */
  void writeDB() {
    auto j = sanitizeJSON();
    std::cout << "JSON Data Stored (DEVELOPMENT ONLY / DO NOT LEAVE THIS IN PRODUCTION)";
    // std::cout << nlohmann::json::string_t(j);
    std::cout << j;
    std::vector<PasswordEntry> entries = desanitizeJSON(j);
    for(int i = 0; i < entries.size(); i++) {
      std::cout << "\n";
      std::cout << entries[i].name + " ";
      std::cout << entries[i].password + " ";
      std::cout << entries[i].notes + " ";
      std::cout << entries[i].seachableURL + " ";
      std::cout << entries[i].username + " ";
    }
    std::cout << "\n";
  }
};
