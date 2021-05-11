//
// Created by oskro on 14 mar 2021.
//
#define NONE -1

#include "Fork.h"
#include <ncurses.h>

int Fork::idCntr = 0;

Fork::Fork()
{
    this->id = idCntr++;
    this->ownerId = NONE;
}

bool Fork::isUnlocked()
{
    return (ownerId == NONE) ?
    true : false;
} 

void Fork::lock(int ownerId)
{
    mutex.lock();
    this->ownerId = ownerId;
}

void Fork::unlock()
{
    mutex.unlock();
    this->ownerId = NONE;
}

int Fork::getId()
{
    return id;
}

Fork::~Fork()
{
    
}
