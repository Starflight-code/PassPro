#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "../Cryptography/CryptographyStorage.h"
#include "../Cryptography/Cryptography.cpp"
#include "../Data_Structures/PasswordEntry.h"
#include "../include/json.hpp"
#include "DatabaseObject.h"
#include <iostream>
#include <vector>
#include <fstream>

namespace DataProcessing {
  class DatabaseManager;
}

class DatabaseManager {
  public:
  /**
   * @brief addEntry: Adds an entry to the list of contained password entries
   * @param entry to append to std::vector<PasswordEntry>
   */
  inline void addEntry(PasswordEntry entry);

  /**
   * @brief addEntry: Adds an entry to the list of contained password entries
   * @param entry to append to std::vector<PasswordEntry> (dereferenced before append)
   */
  inline void addEntry(PasswordEntry* entry);

  /**
   * @brief writeDB: Sanitizes current DB state, converts
   * to JSON, encrypts and pushes it to the disk
   * @param credentials an instance of CryptographyStorage containing the current session username and password
   */
  inline void writeDB(CryptographyStorage* credentials);

  /**
   * @brief getEntries: Returns a list of contained password entries
   * @return std::vector<PasswordEntry> of contained entries
   */
  inline std::vector<PasswordEntry>* getEntries();
  /// @brief Vector containing current database of PasswordEntry objects
  std::vector<PasswordEntry> entries;


  /**
   * @brief desanitizeJSON: Generates a vector of PasswordEntry information from JSON data
   * @param jsonObject: A JSON object
   * @return std::vector<PasswordEntry> list of PasswordEntry objects
   */
  inline std::vector<PasswordEntry> desanitizeJSON(nlohmann::json jsonObject);

  /**
   * @brief generateJSON: Generates JSON from embedded entries data
   * @return nlohmann::json object containing all data from entries vector
   */
  inline nlohmann::json sanitizeJSON();

  inline void readDB(CryptographyStorage* credentials, int plaintextlength);
};
#endif // DATABASEMANAGER_H
