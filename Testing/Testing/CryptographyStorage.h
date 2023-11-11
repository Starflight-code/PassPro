// CryptographyStorage.h
#ifndef CRYPTOGRAPHY_STORAGE_H
#define CRYPTOGRAPHY_STORAGE_H

#include <string>

class CryptographyStorage {
public:
	CryptographyStorage(std::string user, std::string password);
	std::string getUser() const;
	std::string getKey() const;

private:
	std::string user;
	std::string key;
};

#endif
