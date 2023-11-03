#pragma once

#include <string>

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
public:
    std::string password;
    std::string name;
    std::string url;
    std::string username;
    std::string notes;
    std::string seachableURL;
    PasswordEntry(std::string password, std::string name, std::string url, std::string username, std::string notes) {
        this->password = password;
        this->username = username;
        this->name = name;
        this->notes = notes;
        this->url = url;
        if(url.substr(0, 4) == "www.") { // www. prepend will be removed for later searching
            url.replace(0, 4, "");
            this->seachableURL = url; // TODO: Add an area that removes HTTP(s):// prepends from the URL
        }
    }
};
