#pragma once

#include <vector>
#include <string>
#include "PasswordEntry.cpp"

class DatabaseObject {

private:
    std::vector<std::string> name;
    std::vector<std::string> url;
    std::vector<std::string> password;
    std::vector<std::string> username;
    std::vector<std::string> notes;
    std::vector<std::string> searchableURL;

public:
    /**
     * @brief addEntry: adds all data from a password entry object to a set of parallel vectors
     * @param entry: a PasswordEntry instance
     * @return void
     */
    void addEntry(PasswordEntry entry) {
        name.push_back(entry.name);
        url.push_back(entry.url);
        password.push_back(entry.password);
        username.push_back(entry.username);
        notes.push_back(entry.notes);
        searchableURL.push_back(entry.seachableURL);
    }
};
