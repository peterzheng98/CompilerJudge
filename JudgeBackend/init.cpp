//
// Created by 郑文鑫 on 2019-05-24.
//

#include "init.h"
#include <sqlite3.h>
#include <fstream>
#include <iostream>
#include <thread>
#include "Utility.h"

namespace compilerBackend {
init::init(const std::string &fileName, const std::string &targetName)
    : fileName(fileName), targetName(targetName) {}

void init::run() {
  std::ifstream _fileIn;
  _fileIn.open(fileName, std::ios::in);
  std::cerr << "> Info:\t Open file" + fileName + "\n";
  if (jsonReader.parse(_fileIn, jsonRoot, false)) {
    // Check the config file have the module
    std::string command[] = {"database", "host", "update", "thread_count"};
    for (int i = 0; i < 4; ++i)
      if (jsonRoot[command[i]].isNull())
        throw myException("Initial Config file error: No " + command[i] +
                          " member.");

    Json::Value databaseRoot = jsonRoot["database"];
    Json::Value hostRoot = jsonRoot["host"];
    Json::Value update = jsonRoot["update"];
    Json::Value threadCount = jsonRoot["thread_count"];
    /*
     * Requirements in initial phase:
     * 1. Check whether thread_count < sys.thread.count
     * 2. Check whether database is available and create new table
     */
    // Check thread count
    maxPlatformThread = std::thread::hardware_concurrency();
    targetThread = threadCount.asInt();
    if (targetThread + 1 > maxPlatformThread)
      std::cerr << "* Warn:\t Request Thread:" << std::to_string(targetThread)
                << " Platform Thread:" << std::to_string(maxPlatformThread);
    // Check Database
    Json::Value databaseNameVal = databaseRoot["name"];
    Json::Value databasePwdVal = databaseRoot["pwd"];
    Json::Value databaseTypeVal = databaseRoot["type"];
    dbInfo.name = databaseNameVal.asString();
    dbInfo.pwd = databasePwdVal.asString();
    dbInfo.type = databaseTypeVal.asString();
    if (dbInfo.type == "SQLite") {
      dbInfo.typeID = 1;  // SQLite
      Json::Value dbFile = databaseRoot["filename"];
      dbInfo.name = dbFile.asString();

      int return_code = sqlite3_open(dbInfo.name.c_str(), &dbInfo.db);
      if (return_code > 0)
        throw myException("Can't open database: " +
                          std::string(sqlite3_errmsg(dbInfo.db)));
      std::string sql =
          "CREATE TABLE ServerSync("
          "ID INT PRIMARY KEY     NOT NULL auto_increment,"
          "SHA CHAR(40) NOT NULL,"
          "CRC CHAR(16) NOT NULL,"
          "TIME CHAR(30) NOT NULL,"
          "LOG TEXT NOT NULL);";
      char* errmsg = 0;
      return_code = sqlite3_exec(dbInfo.db, sql.c_str(), init::callback, 0, &errmsg);
      if(return_code != SQLITE_OK){
        std::cerr << "! Error:\t SQL error: " << errmsg << "\n";
        sqlite3_free(errmsg);
        throw myException("SQL Error!");
      }
      std::cerr << "> Info:\t Table[Server Sync] Create Success!\n";
      sql = "CREATE TABLE UserRepo("
            "ID INT PRIMARY KEY NOT NULL auto_increment,"
            "Name CHAR(255) NOT NULL,"
            "TIME CHAR(30) NOT NULL,"
            "SHA CHAR(40) NOT NULL,"
            "LOG TEXT NOT NULL,"
            "Status INT NOT NULL);";
      char* errmsg2 = 0;
      return_code = sqlite3_exec(dbInfo.db, sql.c_str(), init::callback, 0, &errmsg2);\
      if(return_code != SQLITE_OK){
        std::cerr << "! Error:\t SQL error: " << errmsg2 << "\n";
        sqlite3_free(errmsg2);
        throw myException("SQL Error!");
      }
      std::cerr << "> Info:\t Table[User Git Data] Create Success!\n";
      sqlite3_close(dbInfo.db);
      std::cerr << "> Info:\t SQLite Closed success!\n";
    }
    // No Support for other databases
  }
}
}  // namespace compilerBackend
