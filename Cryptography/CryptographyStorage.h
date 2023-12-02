#ifndef CRYPTOGRAPHYSTORAGE_H
#define CRYPTOGRAPHYSTORAGE_H

#include "../Data Structures/SecureString.cpp"
#include <string>

class CryptographyStorage {
  public:
  std::string user;
  DataProcessing::secureString key;
  /**
   * @brief Stores a username and password for database saving/loading and cryptography
   * @param user a username, used as the database filename
   * @param password a key, used as the database's cryptography key
   */
  inline CryptographyStorage(std::string user, std::string password);
};

#endif
