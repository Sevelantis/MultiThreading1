//
// Created by oskro on 14 mar 2021.
//
#include "Fork.h"
#include <ncurses.h>

int Fork::idCntr = 0;

Fork::Fork()
{
    this->id = idCntr++;
    printw("new fork created, id\t->\t %d",id);
}

void Fork::setOwnerId(int ownerId)
{
    this->ownerId = ownerId;
}

int Fork::getId()
{
    return id;
}

Fork::~Fork()
{
    attron(COLOR_PAIR(1)); printw("fork destroyed");
}
