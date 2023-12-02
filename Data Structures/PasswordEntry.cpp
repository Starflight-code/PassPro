#include "PasswordEntry.h"

std::string PasswordEntry::RemovePrepend(std::string baseString, std::string prepend) {
  std::string substring = baseString.substr(0, prepend.length());
  if(substring == prepend) {
    baseString.replace(0, prepend.length(), "");
  }
  return baseString;
}

PasswordEntry::PasswordEntry(std::string password, std::string name, std::string url,
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

bool PasswordEntry::equals(const PasswordEntry otherEntry) {
  bool out = out ? this->name == otherEntry.name : false;
  out = out ? this->username == otherEntry.username : false;
  out = out ? this->password == otherEntry.password : false;
  out = out ? this->url == otherEntry.url : false;
  return out;
}
