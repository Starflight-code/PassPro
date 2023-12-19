#include "PasswordEntry.h"

std::string PasswordEntry::RemovePrepend(std::string baseString, std::string prepend) {
  std::string substring = baseString.substr(0, prepend.length());
  if(substring == prepend) {
    baseString.replace(0, prepend.length(), "");
  }
  return baseString;
}

PasswordEntry::PasswordEntry(std::string password, std::string name, std::string url,
                             std::string username, std::string notes, std::string searchableURL) {
  this->password = password;
  this->username = username;
  this->name = name;
  this->notes = notes;
  this->url = url;
  this->searchableURL = searchableURL;
}

PasswordEntry::PasswordEntry(std::string password, std::string name, std::string url,
                             std::string username, std::string notes) {
  this->password = password;
  this->username = username;
  this->name = name;
  this->notes = notes;
  this->url = url;
  std::string preURL = (url);
  for(int i = 0; i < preURL.length(); i++) {
    preURL[i] = tolower(preURL[i]);
  }
  preURL = RemovePrepend(preURL, "https://");
  preURL = RemovePrepend(preURL, "http://");
  preURL = RemovePrepend(preURL, "tcp://");
  preURL = RemovePrepend(preURL, "ssh://");
  preURL = RemovePrepend(preURL, "www.");
  preURL = RemovePrepend(preURL, "server.");
  preURL = RemovePrepend(preURL, "about.");
  this->searchableURL = preURL;
}

PasswordEntry::PasswordEntry(const PasswordEntry& otherEntry) {
  this->password = otherEntry.password;
  this->username = otherEntry.username;
  this->name = otherEntry.name;
  this->notes = otherEntry.notes;
  this->url = otherEntry.url;
  this->searchableURL = otherEntry.searchableURL;
}

PasswordEntry::PasswordEntry() {
  this->password = "";
  this->username = "";
  this->name = "";
  this->notes = "";
  this->url = "";
  this->searchableURL = "";
}

bool PasswordEntry::operator==(PasswordEntry otherEntry) {
  bool out = out ? this->name == otherEntry.name : false;
  out = out ? this->username == otherEntry.username : false;
  out = out ? this->password == otherEntry.password : false;
  out = out ? this->url == otherEntry.url : false;
  return out;
}

bool PasswordEntry::equals(PasswordEntry otherEntry) {
  bool out = out ? this->name == otherEntry.name : false;
  out = out ? this->username == otherEntry.username : false;
  out = out ? this->password == otherEntry.password : false;
  out = out ? this->url == otherEntry.url : false;
  return out;
}