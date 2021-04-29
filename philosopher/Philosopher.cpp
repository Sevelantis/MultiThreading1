//
// Created by oskro on 14 mar 2021.
//
#include <ncurses.h>
#include "Philosopher.h"

using namespace std;

bool Philosopher::feast = true;
int Philosopher::idCntr = 0;

void Philosopher::run()
{
    while(feast)
    {
        attron(COLOR_PAIR(3)); printw("philosopher with ID =  %d is eating", id);
    }
}

Philosopher::Philosopher(Fork *f1, Fork *f2)
{
    this->id = idCntr++;
    this->forks.first = f1;
    this->forks.second = f2;

    attron(COLOR_PAIR(2)); printw("new philosopher created, id\t->\t%d", id);
    printw("\t he has forks with ID's : %d and %d", f1->getId() ,f2->getId());
}

Philosopher::~Philosopher()
{
    attron(COLOR_PAIR(1)); printw("philosopher with ID %d is destroyed.",id);
    feast = false;
    thr.join();
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
