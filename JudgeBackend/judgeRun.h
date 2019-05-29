//
// Created by 郑文鑫 on 2019-05-25.
//

#ifndef JUDGEBACKEND_JUDGERUN_H
#define JUDGEBACKEND_JUDGERUN_H

#include <fstream>
#include <iostream>
#include <thread>
#include <sqlite3.h>
#include "Utility.h"
#include "json/json.h"
// Set for socket communication
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <cstdio>
namespace compilerBackend {
class judgeRun {
 private:
  Json::Reader jsonReader;
  Json::Value jsonRoot;
  int thread_count;
  std::string config_name;
  std::string judge_server_name;
  struct DBInfo {
    std::string name, pwd, type, dbfile;
    int typeID = 0;
    sqlite3 *db;
  } dbInfo;
  struct ServerInfo{
      IPAddress addr;
      int port;
  }serverInfo;

  struct SocketInfo{
      int buffer_size;
      int sock_cli;
      fd_set rfds;
      struct timeval tv;
      int retval, maxfd;
  } socketInfo;
  bool socket_sendmess_one_buffer(const std::string &mess);
  std::pair<std::string, bool> socket_recvmess_sync();
 public:
  judgeRun(const std::string &configName);

  void initConfig();
};
}  // namespace compilerBackend

#endif  // JUDGEBACKEND_JUDGERUN_H
