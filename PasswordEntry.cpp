#pragma once

#include "PasswordEntry.h"

/**
 * @brief The PasswordEntry class: A struct containing password entry data
 * @part std::string password: A string containg a user's password
 * @part std::string name: A string containg the name for this entry
 * @part std::string url: A string containg a url
 * @part std::string username: A string containg a user's username
 * @part std::string notes: A long string containg arbitrary text
 * @part std::string searchableURL: A string containg a url, without the "www."
 */
struct PasswordEntry {
  private:
  std::string RemovePrepend(std::string baseString, std::string prepend) {
    std::string substring = baseString.substr(0, prepend.length());
    if(substring == prepend) {
      baseString.replace(0, prepend.length(), "");
    }
    return baseString;
  }

  public:
  std::string password;
  std::string name;
  std::string url;
  std::string username;
  std::string notes;
  std::string searchableURL;

  PasswordEntry(std::string password, std::string name, std::string url,
                std::string username, std::string notes) {
    this->password = password;
    this->username = username;
    this->name = name;
    this->notes = notes;
    this->url = url;
    std::string preURL = (url);
    for(int i = 0; i < url.length(); i++) {
      preURL[i] = tolower(preURL[i]);
    }
    RemovePrepend(preURL, "https://");
    RemovePrepend(preURL, "http://");
    RemovePrepend(preURL, "ssh://");
    RemovePrepend(preURL, "www.");
    this->searchableURL = url;
  }
};
