#ifndef CRYPTOGRAPHYSTORAGE_H
#define CRYPTOGRAPHYSTORAGE_H

#include <string>

namespace Cryptography {
  class CryptographyStorage;
}

class CryptographyStorage {
  std::string user;
  std::string key;
  /**
   * @brief Stores a username and password for database saving/loading and cryptography
   * @param user a username, used as the database filename
   * @param password a key, used as the database's cryptography key
   */
  inline CryptographyStorage(std::string user, std::string password);
};

#endif