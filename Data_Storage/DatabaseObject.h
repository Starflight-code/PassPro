#ifndef DATABASEOBJECT_H
#define DATABASEOBJECT_H

#include "../Data_Structures/PasswordEntry.h"
#include <memory>
#include <string>
#include <vector>

namespace DataProcessing {
  class DatabaseObject;
}

class DatabaseObject {
  public:
  /// Name of a password entry
  std::vector<std::string> name;
  /// URL of the secured resource
  std::vector<std::string> url;
  /// A string 0-512 characters long. TODO: Secure this with the SecureString class. Contains the password used for secure resource authentication.
  std::vector<std::string> password;
  /// A string 0-64 characters long. Contains the username/email used for secure resource authentication.
  std::vector<std::string> username;
  /// User notes, TODO: Set a size limit
  std::vector<std::string> notes;
  /// A URL with the protocol (https://, http://, tcp://, ssh://) and prefix (www., server., about.) removed. For use with search module.
  std::vector<std::string> searchableURL;

  /**
   * @brief addEntry: adds all data from a password entry object to a set of parallel vectors
   * @param entry: a PasswordEntry instance
   */
  void addEntry(PasswordEntry entry);

  /**
   * @brief addEntry: adds all data from a password entry object to a set of parallel vectors
   * @param entry: a PasswordEntry instance pointer
   */
  void addEntry(PasswordEntry* entry);

  /**
   * @brief fetches an entry by index
   * @param index: an integer to fetch a PasswordEntry from
   * @return PasswordEntry object containing the data from the index specified
   */
  PasswordEntry fetchEntry(int index);
};
#endif
