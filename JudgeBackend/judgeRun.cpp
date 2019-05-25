//
// Created by 郑文鑫 on 2019-05-25.
//

#include "judgeRun.h"
#include <sqlite3.h>
#include "Utility.h"
namespace compilerBackend {
judgeRun::judgeRun(const std::string &configName) : config_name(configName) {}

void judgeRun::initConfig() {
  std::ifstream _fileIn;
  _fileIn.open(config_name, std::ios::binary);
  std::cerr << "> Info:\t Open file[" + config_name + "]\n";
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


}
}  // namespace compilerBackend
