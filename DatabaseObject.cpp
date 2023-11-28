#pragma once

#include "DatabaseObject.h"

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

  void addEntry(PasswordEntry entry) {
    name.push_back(entry.name);
    url.push_back(entry.url);
    password.push_back(entry.password);
    username.push_back(entry.username);
    notes.push_back(entry.notes);
    searchableURL.push_back(entry.searchableURL);
  }
};
