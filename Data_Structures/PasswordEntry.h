#ifndef PASSWORDENTRY_H
#define PASSWORDENTRY_H

#include <string>

namespace DataProcessing {
  struct PasswordEntry;
}

/**
 * @brief The PasswordEntry class: A struct containing password entry data
 * @internal std::string password: A string containg a user's password
 * @internal std::string name: A string containg the name for this entry
 * @internal std::string url: A string containg a url
 * @internal std::string username: A string containg a user's username
 * @internal std::string notes: A long string containg arbitrary text
 * @internal std::string searchableURL: A string containg a url, without the "www."
 */
class PasswordEntry {
  private:
  /**
   * @brief Removes the prepend string from the beginning, if it is the first part of the string
   * @param baseString the full string
   * @param prepend the substring to remove (if present) from the front
   * @return std::string without the prepend string in front
   */
  std::string RemovePrepend(std::string baseString, std::string prepend);

  public:
  /// Name of a password entry
  std::string name;
  /// A string 0-64 characters long. Contains the username/email used for secure resource authentication.
  std::string username;
  /// A string 0-512 characters long. TODO: Secure this with the SecureString class. Contains the password used for secure resource authentication.
  std::string password;
  /// URL of the secured resource
  std::string url;
  /// User notes, TODO: Set a size limit
  std::string notes;
  /// A URL with the protocol (https://, http://, tcp://, ssh://) and prefix (www., server., about.) removed. For use with search module.
  std::string searchableURL;

  /**
   * @param password std::string: A string containg a user's password
   * @param name std::string: A string containg the name for this entry
   * @param url std::string: A string containg a url
   * @param username std::string: A string containg a user's username
   * @param notes std::string: A long string containg arbitrary text
   * @param searchableURL std::string: A string containg a url, without the
   * "www." or "https://"
   */
  PasswordEntry(std::string password, std::string name, std::string url,
                std::string username, std::string notes);

  PasswordEntry(const PasswordEntry& otherEntry);

  PasswordEntry();
  ~PasswordEntry();

  bool operator==(PasswordEntry otherEntry);
  // bool equals(PasswordEntry otherEntry);
  bool equals(const PasswordEntry otherEntry);
  bool equals(PasswordEntry* otherEntry);
};

#endif
