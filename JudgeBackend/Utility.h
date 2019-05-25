//
// Created by 郑文鑫 on 2019-05-24.
//

#ifndef JUDGEBACKEND_UTILITY_H
#define JUDGEBACKEND_UTILITY_H
#define VERSION 1.0
#define BUILD_VERSION 1001
#include <iostream>
#include <string>
#include <vector>

namespace compilerBackend {
class myException : std::exception {
 private:
  std::string mess;

 public:
  myException(const std::string &message) : mess(message) {
    std::cerr << "! Error:\t " << mess << "\n";
  }

  ~myException() override {}

  const char *what() const noexcept { return mess.c_str(); }
};

class IPAddress {
 private:
  int d1, d2, d3, d4;

 public:
  IPAddress() = default;

  IPAddress(const std::string &__r) {
    std::vector<int> __addr;
    std::string __cur;
    for (int __i = 0; __i < __r.size(); ++__i) {
      if (__r[__i] == '.') {
        __addr.push_back(std::atoi(__cur.c_str()));
        __cur = "";
      } else
        __cur.push_back(__r[__i]);
    }
    if (__addr.size() != 4) throw myException("Invalid IP Address.");
    if (__addr[0] > 255 || __addr[0] < 0)
      throw myException("Invalid IP Address.(Pos: 0)" +
                        std::to_string(__addr[0]) + "not in [0, 255]!");
    if (__addr[1] > 255 || __addr[1] < 0)
      throw myException("Invalid IP Address.(Pos: 1)" +
                        std::to_string(__addr[1]) + "not in [0, 255]!");
    if (__addr[2] > 255 || __addr[2] < 0)
      throw myException("Invalid IP Address.(Pos: 2)" +
                        std::to_string(__addr[2]) + "not in [0, 255]!");
    if (__addr[3] > 255 || __addr[3] < 0)
      throw myException("Invalid IP Address.(Pos: 3)" +
                        std::to_string(__addr[3]) + "not in [0, 255]!");
    d1 = __addr[0];
    d2 = __addr[1];
    d3 = __addr[2];
    d4 = __addr[3];
  }

  void modify(const std::string &__r) {
    std::vector<int> __addr;
    std::string __cur;
    for (int __i = 0; __i < __r.size(); ++__i) {
      if (__r[__i] == '.') {
        __addr.push_back(std::atoi(__cur.c_str()));
        __cur = "";
      } else
        __cur.push_back(__r[__i]);
    }
    if (__addr.size() != 4) throw myException("Invalid IP Address.");
    if (__addr[0] > 255 || __addr[0] < 0)
      throw myException("Invalid IP Address.(Pos: 0)" +
                        std::to_string(__addr[0]) + "not in [0, 255]!");
    if (__addr[1] > 255 || __addr[1] < 0)
      throw myException("Invalid IP Address.(Pos: 1)" +
                        std::to_string(__addr[1]) + "not in [0, 255]!");
    if (__addr[2] > 255 || __addr[2] < 0)
      throw myException("Invalid IP Address.(Pos: 2)" +
                        std::to_string(__addr[2]) + "not in [0, 255]!");
    if (__addr[3] > 255 || __addr[3] < 0)
      throw myException("Invalid IP Address.(Pos: 3)" +
                        std::to_string(__addr[3]) + "not in [0, 255]!");
    d1 = __addr[0];
    d2 = __addr[1];
    d3 = __addr[2];
    d4 = __addr[3];
  }

  std::string toString() {
    return std::to_string(d1) + "." + std::to_string(d2) + "." +
           std::to_string(d3) + "." + std::to_string(d4);
  }
};
}  // namespace compilerBackend


#endif  // JUDGEBACKEND_UTILITY_H
