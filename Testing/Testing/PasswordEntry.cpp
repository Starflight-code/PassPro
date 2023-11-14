#pragma once

#include <string>

struct PasswordEntry {
public:
    std::string password;
    std::string name;
    std::string url;
    std::string username;
    std::string notes;
    std::string seachableURL;
    // added for testing
    bool operator==(const PasswordEntry& other) const {
      return password == other.password &&
             name == other.name &&
             url == other.url &&
             username == other.username &&
             notes == other.notes &&
             seachableURL == other.seachableURL;
    }
    PasswordEntry(std::string password, std::string name, std::string url, std::string username, std::string notes) {
        this->password = password;
        this->username = username;
        this->name = name;
        this->notes = notes;
        this->url = url;
        if (url.substr(0, 4) == "www.") { // www. prepend will be removed for later searching
            url.replace(0, 4, "");
            this->seachableURL = url;
        }

    }
};
