#include <iostream>
#include "Utility.h"
#include "init.h"
void help() {
  printf(
      "Compiler Judge Backend %.1lf Build %d"
      "\nDesigned for ACM Honored Class\n"
      "Usage: JudgeBackend <command> <commandArgs...>"
      "\n\nCommands:"
      "\n\tinit\t\tInitialize the Judge with the json file given in commandArg1 and save the configuration file to commandArg2."
      "\n\tstart\t\tStart the Judge with the config json file in <commandArgs>."
      "\n\nHope you all get good scores!", VERSION, BUILD_VERSION);
  exit(0);
}
compilerBackend::init JudgeInit;


int main(int argc, char** argv) {
  if (argc <= 2) help();
  if (argc == 3 && std::string(argv[1]) == std::string("init")){ // init function here
    std::string fileName = std::string(argv[2]);
    JudgeInit.setFileName(fileName);
    JudgeInit.run();
  } else if(argc == 3 && std::string(argv[1]) == std::string("start")){
    std::string configFile = std::string(argv[2]);
  } else help();
}