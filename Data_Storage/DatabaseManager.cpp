#ifndef DATABASEMANAGER_CPP
#define DATABASEMANAGER_CPP

#include "DatabaseManager.h"

nlohmann::json DatabaseManager::sanitizeJSON() {
  DatabaseObject db;

  for(int i = 0; i < entries.size(); i++) {
    db.addEntry(entries[i]);
  }

  nlohmann::json j;
  j["names"] = db.name;
  j["urls"] = db.url;
  j["s_urls"] = db.searchableURL;
  j["notes"] = db.notes;
  j["usernames"] = db.username;
  j["passwords"] = db.password;
  j["searchableURL"] = db.searchableURL;
  return j;
}

std::vector<PasswordEntry>* DatabaseManager::getEntries() {
  return &entries;
}

void DatabaseManager::addEntry(PasswordEntry entry) {
  entries.push_back(entry);
}

void DatabaseManager::desanitizeJSON(nlohmann::json jsonObject) {
  std::vector<PasswordEntry> entries;
  for(int i = 0; i < jsonObject["names"].size(); i++) {
    entries.push_back(PasswordEntry(
        jsonObject["passwords"][i],
        jsonObject["names"][i],
        jsonObject["urls"][i],
        jsonObject["usernames"][i],
        jsonObject["notes"][i],
        jsonObject["searchableURL"][i]));
  }
  this->entries.clear();
  for(int i = 0; i < entries.size(); i++) {
    this->entries.push_back(entries[i]);
  }
}

void DatabaseManager::writeDB(CryptographyStorage* credentials) {
  nlohmann::json jsonData = sanitizeJSON();

  Cryptography Crypto(DataProcessing::secureString(credentials->key));

  DataProcessing::secureString plain(jsonData.dump());

  DataProcessing::secureString encryptedText = Crypto.encrypt(plain);

  try {
    std::ofstream outfile(credentials->user + ".db", std::ios::binary);
    outfile.write(encryptedText.c_str(), encryptedText.length());
    outfile.close();
  } catch(const std::exception& e) {
    std::ofstream outfile(credentials->user + ".db", std::ios::binary | std::ios::trunc);
    outfile.write(encryptedText.c_str(), encryptedText.length());
    outfile.close();
  }
}
void DatabaseManager::readDB(CryptographyStorage* credentials) {
  std::ifstream infile(credentials->user + ".db", std::ios::binary);
  infile.seekg(0, infile.end);           // Move read position to the end
  int ciphertextLength = infile.tellg(); // Checks the current read position (file length)
  infile.seekg(0, infile.beg);           // Moves read position to the beginning

  std::vector<unsigned char> ciphertextData(ciphertextLength);
  infile.read((char*)ciphertextData.data(), ciphertextLength);
  infile.close();
  DataProcessing::secureString out((char*)ciphertextData.data(), ciphertextLength);

  Cryptography Cryptography(DataProcessing::secureString(credentials->key));

  DataProcessing::secureString plaintext = Cryptography.decrypt(out);

  // Deserialize the JSON data
  nlohmann::json jsonData = nlohmann::json::parse(plaintext);

  // Process the JSON data
  desanitizeJSON(jsonData);
}
#endif
