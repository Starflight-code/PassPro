#ifndef DATABASEMANAGER_CPP
#define DATABASEMANAGER_CPP

#include "DatabaseManager.h"

nlohmann::json DatabaseManager::sanitizeJSON() {
  DatabaseObject db;
  // PasswordEntry n1 = PasswordEntry("pass", "name", "url", "user", "notes");
  //  PasswordEntry n2 = PasswordEntry("pass2", "name2", "url2", "user2", "notes2");
  //  PasswordEntry n3 = PasswordEntry("pass3", "name3", "url3", "user3", "notes3");

  for(int i = 0; i < entries.size(); i++) {
    db.addEntry(entries[i]);
  }

  // db.addEntry(n1);
  //  db.addEntry(n2);
  //  db.addEntry(n3);
  nlohmann::json j;
  j["names"] = db.name;
  j["urls"] = db.url;
  j["s_urls"] = db.searchableURL;
  j["notes"] = db.notes;
  j["usernames"] = db.username;
  j["passwords"] = db.password;
  return j;
}

std::vector<PasswordEntry>* DatabaseManager::getEntries() {
  return &entries;
}

void DatabaseManager::addEntry(PasswordEntry entry) {
  entries.push_back(entry);
}

std::vector<PasswordEntry> DatabaseManager::desanitizeJSON(nlohmann::json jsonObject) {
  std::vector<PasswordEntry> entries;
  for(int i = 0; i < jsonObject["names"].size(); i++) {
    entries.push_back(PasswordEntry(
        jsonObject["passwords"][i],
        jsonObject["names"][i],
        jsonObject["urls"][i],
        jsonObject["usernames"][i],
        jsonObject["notes"][i]));
  }
  return entries;
}

void DatabaseManager::writeDB(CryptographyStorage* credentials) {
  nlohmann::json jsonData = sanitizeJSON();
  unsigned char key[credentials->key.length()];
  // DataProcessing::secureString
  for(int i = 0; i < credentials->key.length(); i++) {
    key[i] = credentials->key[i];
  }
  Cryptography Cryptography(key);

  std::string notEncryptedJson = jsonData.dump();

  unsigned char* plaintext = (unsigned char*)notEncryptedJson.c_str();
  int plaintextLength = notEncryptedJson.length();

  std::string encryptedJsonData = "";
  unsigned char* ciphertext = (unsigned char*)encryptedJsonData.c_str();
  std::vector<unsigned char> ciphertextData(plaintextLength);
  Cryptography.encryptAES256(plaintext, plaintextLength, ciphertextData.data());
  int cipherLen = plaintextLength + 16 - (plaintextLength % 16);
  std::string out2((char*)ciphertextData.data(), cipherLen);
  std::cout << out2;
  unsigned char* plaintextData = (unsigned char*)malloc(cipherLen);

  // Cryptography.decryptAES256(ciphertextData.data(), cipherLen, plaintextData);

  try {
    std::ofstream outfile(credentials->user + ".db", std::ios::binary);
    outfile.write((char*)ciphertextData.data(), cipherLen);
    outfile.close();
  } catch(const std::exception& e) {
    std::ofstream outfile(credentials->user + ".db", std::ios::binary | std::ios::trunc);
    outfile.write((char*)ciphertextData.data(), cipherLen);
    outfile.close();
  }

  readDB(credentials, plaintextLength);
}
void DatabaseManager::readDB(CryptographyStorage* credentials, int plaintextlength) {
  std::ifstream infile(credentials->user + ".db", std::ios::binary);
  infile.seekg(0, infile.end);           // Move read position to the end
  int ciphertextLength = infile.tellg(); // Checks the current read position (file length)
  infile.seekg(0, infile.beg);           // Moves read position to the beginning

  std::vector<unsigned char> ciphertextData(ciphertextLength);
  infile.read((char*)ciphertextData.data(), ciphertextLength);
  infile.close();
  std::string out((char*)ciphertextData.data(), ciphertextLength);
  std::cout << out;
  // Decrypt the JSON data
  unsigned char key[credentials->key.length()];
  for(int i = 0; i < credentials->key.length(); i++) {
    key[i] = credentials->key[i];
  }
  Cryptography Cryptography(key);
  int ciphertext = out.size();

  unsigned char* plaintextData = (unsigned char*)malloc(plaintextlength);
  Cryptography.decryptAES256(ciphertextData.data(), ciphertext, plaintextData);

  // Deserialize the JSON data
  std::string notEncryptedJson((char*)plaintextData, ciphertextLength);
  nlohmann::json jsonData = nlohmann::json::parse(notEncryptedJson);

  // Process the JSON data
  // std::vector<PasswordEntry> entries = desanitizeJSON(jsonData);
  for(int i = 0; i < entries.size(); i++) {
    std::cout << "\n";
    std::cout << entries[i].name + " ";
    std::cout << entries[i].password + " ";
    std::cout << entries[i].notes + " ";
    std::cout << entries[i].searchableURL + " ";
    std::cout << entries[i].username + " ";
  }
  std::cout << "\n";

  // for (int j=0; j < cipherLen; j++)
  // {
  //   if()
  //     }
  // delete[] plaintextData;
}
#endif
