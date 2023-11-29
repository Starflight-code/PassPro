#include "CryptographyStorage.h"

CryptographyStorage::CryptographyStorage(std::string user, std::string password) {
  this->user = user;
  this->key = password;
}