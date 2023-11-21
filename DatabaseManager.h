#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "include/json.hpp"

#endif // DATABASEMANAGER_H

namespace DataProcessing {
  class DatabaseManager;
}

class DatabaseManager {

  private:
  nlohmann::json sanitizeJSON();

  public:
  void writeDB();
};
