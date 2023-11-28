#pragma once

#include "DatabaseObject.h"

void DatabaseObject::addEntry(PasswordEntry entry) {
  name.push_back(entry.name);
  url.push_back(entry.url);
  password.push_back(entry.password);
  username.push_back(entry.username);
  notes.push_back(entry.notes);
  searchableURL.push_back(entry.searchableURL);
}
