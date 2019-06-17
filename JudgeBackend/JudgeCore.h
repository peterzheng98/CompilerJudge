//
// Created by 郑文鑫 on 2019-06-17.
//

#ifndef JUDGEBACKEND_JUDGECORE_H
#define JUDGEBACKEND_JUDGECORE_H

#include <fstream>

namespace compilerBackend {
    class JudgeCore {
    private:
        std::fstream inputAssemblyFile, inputStdData, outputStdData;
        uint64_t timeLimit;
        std::fstream outputSha1;
        std::string langName;
    public:
        JudgeCore(const std::string &inputAssemblyFile, const std::string &inputStdData,
                  const std::string &outputStdData, const uint64_t &timeLimit, const std::string &outputSha1,
                  const std::string &langName);

        JudgeCore();

        void run();
    };
}


#endif //JUDGEBACKEND_JUDGECORE_H
