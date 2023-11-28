#ifndef DATABASEOBJECT_H
#define DATABASEOBJECT_H

#include "DatabaseObject.h"
#include "PasswordEntry.cpp"
#include <string>
#include <vector>

namespace DataProcessing {
  class DatabaseObject;
}

class DatabaseObject {
  public:
  std::vector<std::string> name;
  std::vector<std::string> url;
  std::vector<std::string> password;
  std::vector<std::string> username;
  std::vector<std::string> notes;
  std::vector<std::string> searchableURL;

  /**
   * @brief addEntry: adds all data from a password entry object to a set of parallel vectors
   * @param entry: a PasswordEntry instance
   */
  void addEntry(PasswordEntry entry);
};
#endif