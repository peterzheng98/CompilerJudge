//
// Created by 郑文鑫 on 2019-06-17.
//

#include "JudgeCore.h"

compilerBackend::JudgeCore::JudgeCore(const std::string &inputAssemblyFile, const std::string &inputStdData,
                                      const std::string &outputStdData, const uint64_t &timeLimit,
                                      const std::string &outputSha1, const std::string& langName) {
    this->inputAssemblyFile = std::fstream(inputAssemblyFile, std::ios::in);
    this->inputStdData = std::fstream(inputStdData, std::ios::in);
    this->outputStdData = std::fstream(outputStdData, std::ios::in);
    this->timeLimit = timeLimit;
    this->outputSha1 = std::fstream(outputSha1, std::ios::app);
    this->langName = langName;
}

compilerBackend::JudgeCore::JudgeCore() {}


void compilerBackend::JudgeCore::run() {
    uint64_t totalTicks = 0;
}

