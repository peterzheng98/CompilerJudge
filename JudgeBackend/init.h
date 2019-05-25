//
// Created by 郑文鑫 on 2019-05-24.
//

#ifndef JUDGEBACKEND_INIT_H
#define JUDGEBACKEND_INIT_H

#include <sqlite3.h>
#include "json/json.h"
namespace compilerBackend {
/*
 * Init the Judge
 * Requirements: mysql database connection(SQLite3)
 * Maximum thread count
 */

/*
 * The json file should have the same format within the initSample.json
 */
class init {
 private:
  Json::Reader jsonReader;
  Json::Value jsonRoot;
  std::string fileName;
  struct DBInfo {
    std::string name, pwd, type, dbfile;
    int typeID = 0;
    sqlite3 *db;
  } dbInfo;
  int maxPlatformThread;
  int targetThread;

 public:
  init(const std::string &fileName);
  init() = default;
  void setFileName(const std::string &fileName);

  void run();
  static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for (i = 0; i < argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
  }
  ~init() { sqlite3_close(dbInfo.db); }
};
}  // namespace compilerBackend

#endif  // JUDGEBACKEND_INIT_H
