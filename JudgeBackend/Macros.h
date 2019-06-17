//
// Created by 郑文鑫 on 2019-06-17.
//

#ifndef JUDGEBACKEND_MACROS_H
#define JUDGEBACKEND_MACROS_H

#include <iostream>
// Basic Macros
#define VERSION 1.0
#define BUILD_VERSION 1001
#define DEBUG_LEVEL_DEFINED 2
#define DEBUG_VERBOSE 5
#define DEBUG_INFO 4
#define DEBUG_WARN 3
#define DEBUG_FAULT 2
#define DEBUG_ABORT 1

// Basic Macro Functions
#define PRINT_LOG(level, part, e) std::cerr << "Level: " << level << " from part[" << part << "]:" << e << std::endl

#endif //JUDGEBACKEND_MACROS_H
