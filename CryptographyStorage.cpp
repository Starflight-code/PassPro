#include <string>

class CryptographyStorage {
  std::string user;
  std::string key;
  CryptographyStorage(std::string user, std::string password) {
    this->user = user;
    this->key = password;
  }
}
