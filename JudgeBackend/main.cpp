#include <iostream>
#include "Utility.h"

void help() {
  printf(
      "Compiler Judge Backend 1.0 Build 1001"
      "\nDesigned for ACM Honored Class\n"
      "Usage: JudgeBackend <command> <commandArgs...>"
      "\n\nCommands:"
      "\n\tinit\t\tInitialize the Judge with the json file given in commandArg1 and save the configuration file to commandArg2."
      "\n\tstart\t\tStart the Judge with the config json file in <commandArgs>."
      "\n\nHope you all get good scores!");
  exit(0);
}

int main(int argc, char** argv) {
  if (argc <= 2) help();
  if (argc == 4 && std::string(argv[1]) == std::string("init")){ // init function here
    std::string fileName = std::string(argv[2]);
    std::string targetName = std::string(argv[3]);


  } else if(argc == 3 && std::string(argv[1]) == std::string("start")){
    std::string configFile = std::string(argv[2]);
  } else help();
}