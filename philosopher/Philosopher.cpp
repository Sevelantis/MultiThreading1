//
// Created by oskro on 14 mar 2021.
//
#include <ncurses.h>
#include <chrono>
#include "Philosopher.h"

using namespace std;

bool Philosopher::feast = true;
int Philosopher::idCntr = 0;

void Philosopher::run()
{
    while(feast)
    {
        //TODO
        this->val+=rand()%20-10;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

Philosopher::Philosopher(Fork *f1, Fork *f2)
{
    this->id = idCntr++;
    this->forks.first = f1;
    this->forks.second = f2;
}

Philosopher::~Philosopher()
{
    attron(COLOR_PAIR(2)); printw("philosopher with ID %d is destroyed.\n",id);
    feast = false;
    thr.join();
}

int Philosopher::getVal()
{
    return val;
}

int Philosopher::getId()
{
    return id;
}

void Philosopher::start()
{
    this->thr = thread(&Philosopher::run, this);
}

Philosopher::Philosopher() = default;
