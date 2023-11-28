#pragma once

#include "PasswordEntry.h"

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
