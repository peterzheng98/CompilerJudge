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

    Json::Value update = jsonRoot["update"];
    // Set Judge Server Information
    Json::Value server_name = jsonRoot["server_name"];
    this->judge_server_name = std::string(server_name.asString());
    // Set Connection Related Settings
    Json::Value hostRoot = jsonRoot["host"];
    this->serverInfo.addr = IPAddress(hostRoot["address"].asString());
    this->serverInfo.port = hostRoot["port"].asInt();
    // Set thread related settings
    Json::Value threadCount = jsonRoot["thread_count"];
    thread_count = threadCount.asInt();
    // Set Database Related settings
    Json::Value databaseRoot = jsonRoot["database"];
    Json::Value database_name = databaseRoot["name"];
    Json::Value database_pwd = databaseRoot["pwd"];
    Json::Value database_type = databaseRoot["type"];
    Json::Value database_fileName = databaseRoot["filename"];
    if (database_type == "SQLite") {
      // Currently, we only support SQLite as Database Engine.

      // Set SQLite related settings
      this->dbInfo.name = std::string(database_name.asString());
      this->dbInfo.pwd = std::string(database_pwd.asString());
      this->dbInfo.type = std::string(database_type.asString());
      this->dbInfo.dbfile = std::string(database_fileName.asString());

      // Initial the *db(sqlite3) cursor
      int return_code = sqlite3_open(dbInfo.name.c_str(), &dbInfo.db);
      if (return_code > 0)
        throw myException("Can't open database: " +
                          std::string(sqlite3_errmsg(dbInfo.db)));
      std::cerr << "> Info:\t Make connection with the database successfully!"
                << std::endl;
      // Connect to the Remote Server and check the availability
      // Checking method: Send welcome and logging message and receive the
      // registration message.
      std::string welcome_mess_send("hello, Server:" + this->judge_server_name);
      bool result_welcome = socket_sendmess_one_buffer(welcome_mess_send);
      if(!result_welcome) throw myException("Error in sending welcome Message");
      std::pair<std::string, bool> result_recv_welcome = socket_recvmess_sync();

      std::string command("RegServer:" + this->judge_server_name + ":" + std::to_string(this->serverInfo.port));
      bool result = socket_sendmess_one_buffer(command);
      if(!result) throw myException("Error in registering Judge");

    }
  }
}

bool judgeRun::socket_sendmess_one_buffer(const std::string &mess) {
  if(mess.length() >= socketInfo.buffer_size) throw myException("Message size larger than buffer");
  this->socketInfo.sock_cli = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in servaddr;
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(serverInfo.port);
  servaddr.sin_addr.s_addr = inet_addr(serverInfo.addr.toString().c_str());
  if (connect(socketInfo.sock_cli, (struct sockaddr *)&servaddr,
              sizeof(servaddr)) < 0) {
    perror("connect");
    throw myException("Connect Error in send Message.");
  }
  int totalSize = 0;

  FD_ZERO(&socketInfo.rfds);
  FD_SET(0, &socketInfo.rfds);
  socketInfo.maxfd = 0;
  FD_SET(socketInfo.sock_cli, &socketInfo.rfds);
  if (socketInfo.maxfd < socketInfo.sock_cli)
    socketInfo.maxfd = socketInfo.sock_cli;
  socketInfo.tv.tv_sec = 5;
  socketInfo.tv.tv_usec = 0;
  socketInfo.retval = select(socketInfo.maxfd + 1, &socketInfo.rfds, NULL, NULL,
                             &socketInfo.tv);
  if (socketInfo.retval == -1) {
    std::cerr << "* Warn:\t Error Occurred in Selecting" << std::endl;
    return false;
  } else if (socketInfo.retval == 0) {
    std::cerr << "> Info:\t No message Detected. Waiting." << std::endl;
    return false;
  } else {
    //      // Received Message from server.
    //      if(FD_ISSET(socketInfo.sock_cli,&socketInfo.rfds)){
    //        char recvbuf[socketInfo.buffer_size];
    //        int len;
    //        len = recv(socketInfo.sock_cli, recvbuf, sizeof(recvbuf),0);
    //        std::cerr << "> Info:\t Receive:[" << recvbuf << "]" << std::endl;
    //        totalSize = strlen(recvbuf);
    //        memset(recvbuf, 0, sizeof(recvbuf));
    //      }
    if (FD_ISSET(0, &socketInfo.rfds)) {
      char sendbuf[socketInfo.buffer_size];
      std::string command(mess);
      strcpy(sendbuf, command.c_str());
      send(socketInfo.sock_cli, sendbuf, strlen(sendbuf), 0);
      memset(sendbuf, 0, sizeof(sendbuf));
    }
  }
  return true;
}

std::pair<std::string, bool> socket_recvmess_sync(){

}
}  // namespace compilerBackend
