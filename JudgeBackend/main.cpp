#include <iostream>
#include <fstream>
#include "JudgeCore.h"
#include "Utility.h"

void help() {
    printf(
            "Compiler Judge Backend %.1lf Build %d"
            "\nDesigned for ACM Honored Class\n"
            "Usage: JudgeCore run <lang/function name> <input assembly> <input data> <output data> <standard limit of score> <output sha1>"
            "\n\nHope you all get good scores!", VERSION, BUILD_VERSION);
    exit(0);
}

// Variable Name Rules: g_ indicates global variables
uint64_t g_timeLimit;
std::string g_outputSha1;
std::unique_ptr<compilerBackend::JudgeCore> g_judger = nullptr;

/* The program should run with the following arguments:
 * ./JudgeCore run <lang/function name> <input assembly> <input data> <output data> <standard limit of score> <output sha1>
 */
int main(int argc, char **argv) {
    if (argc != 8) help();
    char *runningMode = argv[1]; // Remaining for further use, here only have run
    char *langName = argv[2]; // Indicates x86_64, riscv, arm...
    char *inputAssemblyFileName = argv[3];
    char *inputStdData = argv[4];
    char *outputStdData = argv[5];
    char *timeLimit = argv[6];
    char *outputSha1 = argv[7];
    // Check timeLimit only contains digits
    int length = strlen(timeLimit);
    for (int i = 0; i < length; ++i) {
        if (!isdigit(timeLimit[i])) {
            std::cout << "Configuration Failed: Parameter <Standard limit of score> must be unsigned numbers.\n";
            help();
        }
    }
    g_timeLimit = compilerBackend::toUint64_t(std::string(timeLimit));
    if (DEBUG_LEVEL_DEFINED >= DEBUG_VERBOSE)
        PRINT_LOG(DEBUG_VERBOSE, "main", std::string("Runtime Limit:") + std::to_string(g_timeLimit));
    // Check output sha1 requires 40 (16-based) digits
    length = strlen(outputSha1);
    if (length != 40) {
        std::cout << "Configuration Failed: Parameter <Output sha1> must have 40 digits.\n";
        help();
    }
    g_outputSha1 = std::string(outputSha1);
    if (DEBUG_LEVEL_DEFINED >= DEBUG_VERBOSE)
        PRINT_LOG(DEBUG_VERBOSE, "main", std::string("Request SHA-1: ") + g_outputSha1);
    std::string str_inputAssemblyFileName(inputAssemblyFileName), str_inputStdData(inputStdData), str_outputStdData(
            outputStdData), str_outputSha1(outputSha1), str_lang(langName);
    g_judger = std::make_unique<compilerBackend::JudgeCore>(
            str_inputAssemblyFileName, str_inputStdData, str_outputStdData, g_timeLimit, str_outputSha1, str_lang);
    g_judger->run();
    return 0;
}