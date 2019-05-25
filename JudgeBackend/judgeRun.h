//
// Created by 郑文鑫 on 2019-05-25.
//

#ifndef JUDGEBACKEND_JUDGERUN_H
#define JUDGEBACKEND_JUDGERUN_H

#include <fstream>
#include <iostream>
#include <thread>
#include <sqlite3.h>
#include "json/json.h"
namespace compilerBackend {
class judgeRun {
 private:
  Json::Reader jsonReader;
  Json::Value jsonRoot;
  int thread_count;
  std::string config_name;
  struct DBInfo {
    std::string name, pwd, type, dbfile;
    int typeID = 0;
    sqlite3 *db;
  } dbInfo;

 public:
  judgeRun(const std::string &configName);

  void initConfig();
};
}  // namespace compilerBackend

#endif  // JUDGEBACKEND_JUDGERUN_H
