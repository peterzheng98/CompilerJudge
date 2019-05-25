//
// Created by 郑文鑫 on 2019-05-25.
//

#ifndef JUDGEBACKEND_JUDGETHREAD_H
#define JUDGEBACKEND_JUDGETHREAD_H

#include <pthread.h>
#include <memory>

class judgeThread {
private:
    std::unique_ptr<pthread_t> thread_core;
public:
    judgeThread(const std::unique_ptr<pthread_t> &threadCore);
    judgeThread(const pthread_t* &pthread);
};


#endif //JUDGEBACKEND_JUDGETHREAD_H
