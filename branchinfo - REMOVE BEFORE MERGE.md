Cryptography implimentation using OpenSSL's AES symmetric cypher. Keys are stored in plain text in memory, an insecure fashion. We could add one of the libraries mentioned here: https://stackoverflow.com/questions/56888162/is-there-a-good-c-implementation-of-secure-strings for "secure string" datatype implimentation to close a few security holes.

Files that will be impacted
- Cryptography.cpp
- CryptographyStorage.cpp