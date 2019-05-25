//
// Created by 郑文鑫 on 2019-05-25.
//

#include "judgeThread.h"

judgeThread::judgeThread(const std::unique_ptr<pthread_t> &threadCore) : thread_core(std::move(threadCore)) {}
judgeThread::judgeThread(const pthread_t *&pthread) : thread_core(pthread){}
