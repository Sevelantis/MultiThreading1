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
    bool isUnlocked();
    void lock(int);
    void unlock();

private:

    static int idCntr;

    int id;
    int ownerId;
    std::mutex mutex;
};


#endif //P1_FORK_H
