#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "../Cryptography/Cryptography.cpp"
#include "../Cryptography/CryptographyStorage.h"
#include "../Data_Structures/PasswordEntry.h"
#include "../include/json.hpp"
#include "DatabaseObject.h"
#include <fstream>
#include <iostream>
#include <vector>

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
  inline void desanitizeJSON(nlohmann::json jsonObject);

  /**
   * @brief generateJSON: Generates JSON from embedded entries data
   * @return nlohmann::json object containing all data from entries vector
   */
  inline nlohmann::json sanitizeJSON();

  /**
   * @brief reads a file from the disk, attempts decryption and import into the program.
   * @param credentials the file path and decryption key to use when reading
   */
  inline void readDB(CryptographyStorage* credentials);
};
#endif // DATABASEMANAGER_H
