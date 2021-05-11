//
// Created by oskro on 14 mar 2021.
//

#ifndef P1_PHILOSOPHER_H
#define P1_PHILOSOPHER_H

#include <thread>
#include <random>
#include <string>
#include "../fork/Fork.h"

enum State {SLEEPING, EATING, WAITING};

class Philosopher
{
public:
    Philosopher(Fork*, Fork*);
    ~Philosopher();

    void start();
    void kill();

    bool isEating();
    std::string getInfo();


private:
    static int idCntr;
    static bool feast;

    int id;
    State state;
    std::thread thr;
    std::pair<Fork*, Fork*> forks;
    int sleepingPoints=0, sleepingPointsMax=100;
    int eatingPoints=0, eatingPointsMax=100;
    int eatCntr=0;
    int clockRate;

    void run();
    bool isFull();
    bool isHungry();
    bool isForksFree();

    void updateClockRate();
};


#endif //P1_PHILOSOPHER_H
