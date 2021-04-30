//
// Created by oskro on 14 mar 2021.
//

#ifndef P1_PHILOSOPHER_H
#define P1_PHILOSOPHER_H

#include <thread>
#include <random>
#include "../fork/Fork.h"

enum State {SLEEPING, EATING};

class Philosopher
{
public:
    Philosopher();
    Philosopher(Fork*, Fork*);
    ~Philosopher();

    int getId();
    int getVal();
    void start();

private:
    static int idCntr;
    static bool feast;

    int val = rand() % 200;

    int id;
    State state;
    std::thread thr;
    std::pair<Fork*, Fork*> forks;
    int points=0;

    void run();
};


#endif //P1_PHILOSOPHER_H
