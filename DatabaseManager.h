#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "nlohmann/json.hpp"

#endif // DATABASEMANAGER_H

namespace DataProcessing {
class DatabaseManager;
}

class DatabaseManager {

private:
  nlohmann::json generateJSON();

public:
  void writeDB();
};
