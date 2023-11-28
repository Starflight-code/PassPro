#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "DatabaseObject.cpp"
#include "PasswordEntry.cpp"
#include "include/json.hpp"
#include <iostream>
#include <vector>

namespace DataProcessing {
  class DatabaseManager;
}

class DatabaseManager {

  private:
  /**
   * @brief generateJSON: Generates JSON from embedded entries data
   * @return nlohmann::json object containing all data from entries vector
   */
  nlohmann::json sanitizeJSON();

  /**
   * @brief desanitizeJSON: Generates a vector of PasswordEntry information from JSON data
   * @param jsonObject: A JSON object
   * @return std::vector<PasswordEntry> list of PasswordEntry objects
   */
  std::vector<PasswordEntry> desanitizeJSON(nlohmann::json jsonObject);

  public:
  /**
   * @brief writeDB: Sanitizes current DB state, converts
   * to JSON, encrypts and pushes it to the disk
   */
  void writeDB();
};
#endif // DATABASEMANAGER_H