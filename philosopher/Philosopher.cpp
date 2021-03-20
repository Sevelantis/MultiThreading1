//
// Created by oskro on 14 mar 2021.
//
#include<iostream>
#include "Philosopher.h"

using namespace std;

bool Philosopher::feast = true;
int Philosopher::idCntr = 0;

void Philosopher::run()
{
    while(feast)
    {
        cout << id << " ";
    }
}

Philosopher::Philosopher(Fork &f1, Fork &f2)
{
    this->forks.first = &f1;
    this->forks.second = &f2;
    this->id = idCntr++;

    cout << feast << " and "<< id << endl;
}

Philosopher::~Philosopher()
{
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
