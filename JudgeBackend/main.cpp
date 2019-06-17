#include <iostream>
#include "Utility.h"
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


/* The program should run with the following arguments:
 * ./JudgeCore compile <compile bash name> <output file name>
 * ./JudgeCore run <
 */
int main(int argc, char** argv) {
    char* runningMode = argv[1];
}