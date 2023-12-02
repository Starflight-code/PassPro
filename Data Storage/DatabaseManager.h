#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "../Data_Structures/PasswordEntry.h"
#include "../include/json.hpp"
#include "DatabaseObject.h"
#include <iostream>
#include <vector>

namespace DataProcessing {
  class DatabaseManager;
}

class DatabaseManager {

  private:
  std::vector<PasswordEntry> entries;

  /**
   * @brief generateJSON: Generates JSON from embedded entries data
   * @return nlohmann::json object containing all data from entries vector
   */
  inline nlohmann::json sanitizeJSON();

  /**
   * @brief desanitizeJSON: Generates a vector of PasswordEntry information from JSON data
   * @param jsonObject: A JSON object
   * @return std::vector<PasswordEntry> list of PasswordEntry objects
   */
  inline std::vector<PasswordEntry> desanitizeJSON(nlohmann::json jsonObject);

  public:
  /**
   * @brief writeDB: Sanitizes current DB state, converts
   * to JSON, encrypts and pushes it to the disk
   */
  inline void writeDB();

  /**
   * @brief getEntries: Returns a list of contained password entries
   * @return std::vector<PasswordEntry> of contained entries
   */
  inline std::vector<PasswordEntry> getEntries();
};
#endif // DATABASEMANAGER_H
