#ifndef CRYPTOGRAPHYSTORAGE_H
#define CRYPTOGRAPHYSTORAGE_H

#include "../Data_Structures/SecureString.cpp"
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
  CryptographyStorage(std::string user, DataProcessing::secureString password);
};

#endif
