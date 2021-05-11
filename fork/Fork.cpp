//
// Created by oskro on 14 mar 2021.
//

#include "Fork.h"

int Fork::idCntr = 0;

Fork::Fork()
{
    this->id = idCntr++;
}

void Fork::lock()
{
    mutex.lock();
}

void Fork::unlock()
{
    mutex.unlock();
}

int Fork::getId()
{
    return id;
}

Fork::~Fork()
{

}
