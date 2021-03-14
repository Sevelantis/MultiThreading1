//
// Created by oskro on 14 mar 2021.
//

#ifndef P1_PHILOSOPHER_H
#define P1_PHILOSOPHER_H

#include <thread>
#include "../fork/Fork.h"

enum State {SLEEPING, EATING};

class Philosopher {
public:
    Philosopher(Fork&, Fork&);
    ~Philosopher();

    int getId();


private:
    static int idCntr;
    static bool feast;

    int id;
    State state;
    std::thread thread;
    std::pair<Fork*, Fork*> forks;

    void run();

};


#endif //P1_PHILOSOPHER_H
