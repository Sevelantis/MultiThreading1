//
// Created by oskro on 14 mar 2021.
//

#ifndef P1_FORK_H
#define P1_FORK_H

#include <mutex>

class Fork
{
public:
    Fork();
    ~Fork();

    int getId();
    void lock();
    void unlock();

private:
    static int idCntr;

    int id;
    std::mutex mutex;
};


#endif //P1_FORK_H
