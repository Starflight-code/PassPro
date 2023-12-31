#ifndef CRYPTOGRAPHYSTORAGE_H
#define CRYPTOGRAPHYSTORAGE_H

#include "../Data_Structures/SecureString.cpp"
#include <string>

class CryptographyStorage {
  public:
  std::string user;
  DataProcessing::secureString key;
  enum passwordStatus { valid,
                        noFile,
                        invalid };
  passwordStatus status;
  /**
   * @brief Stores a username and password for database saving/loading and cryptography
   * @param user a username, used as the database filename
   * @param password a key, used as the database's cryptography key
   */
  CryptographyStorage(std::string user, DataProcessing::secureString password);

  /**
   * @brief Stores a username and password for database saving/loading and cryptography
   */
  CryptographyStorage();
};

#endif
