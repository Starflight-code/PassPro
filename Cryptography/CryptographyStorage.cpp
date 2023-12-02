#include "CryptographyStorage.h"

CryptographyStorage::CryptographyStorage(std::string user, DataProcessing::secureString password) {
  this->user = user;
  this->key = password;
}