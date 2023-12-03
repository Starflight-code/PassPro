#include "DatabaseObject.h"
#include <memory>

void DatabaseObject::addEntry(PasswordEntry* entry) {
  name.push_back(entry->name);
  url.push_back(entry->url);
  password.push_back(entry->password);
  username.push_back(entry->username);
  notes.push_back(entry->notes);
  searchableURL.push_back(entry->searchableURL);
}

void DatabaseObject::addEntry(std::shared_ptr<PasswordEntry> entry) {
  name.push_back(entry->name);
  url.push_back(entry->url);
  password.push_back(entry->password);
  username.push_back(entry->username);
  notes.push_back(entry->notes);
  searchableURL.push_back(entry->searchableURL);
}

void DatabaseObject::addEntry(PasswordEntry entry) {
  name.push_back(entry.name);
  url.push_back(entry.url);
  password.push_back(entry.password);
  username.push_back(entry.username);
  notes.push_back(entry.notes);
  searchableURL.push_back(entry.searchableURL);
}
