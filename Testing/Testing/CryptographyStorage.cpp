// CryptographyStorage.cpp
#include "CryptographyStorage.h"

CryptographyStorage::CryptographyStorage(std::string user, std::string password)
	: user(user), key(password) {}

std::string CryptographyStorage::getUser() const {
	return user;
}

std::string CryptographyStorage::getKey() const {
	return key;
}