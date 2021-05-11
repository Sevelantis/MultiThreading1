//
// Created by oskro on 14 mar 2021.
//
#include <chrono>
#include <random>
#include "Philosopher.h"

#define CLOCK_RATE 100 //[us] 1000us = 1ms

using namespace std;

bool Philosopher::feast = true;
int Philosopher::idCntr = 0;

void Philosopher::run()
{
    while(feast)
    {
        if(state==SLEEPING)
        {
            if(isHungry())
            {
                state = WAITING;
                updateClockRate();
            }
        }
        else if(state==WAITING)
        {
            if(isForksFree())
            {
                forks.first->lock(id);
                forks.second->lock(id);
                
                state = EATING;
                sleepingPoints=0;
                updateClockRate();
            }
        }
        else if (state==EATING)
        {
            if(isFull())
            {
                forks.second->unlock();
                forks.first->unlock();

                state = SLEEPING;
                eatingPoints = 0;
                eatCntr++;
                updateClockRate();
            }
        }

        std::this_thread::sleep_for(std::chrono::microseconds(clockRate));
    }
}

Philosopher::Philosopher(Fork *f1, Fork *f2)
{
    this->id = idCntr++;
    this->forks.first = f1;
    this->forks.second = f2;
    this->state = SLEEPING;
    this->clockRate = CLOCK_RATE;
    updateClockRate();
}

void Philosopher::kill()
{
    feast = false;
    forks.first->unlock();
    forks.second->unlock();
    thr.join();
}

std::string Philosopher::getInfo()
{
    // build a string to print it on the screen
    string tmp = "Philosopher[";
    tmp.append(to_string(id));
    tmp.append("] has forks ");
    tmp.append("<"+to_string(forks.first->getId())+","+to_string(forks.second->getId())+">,\n\t");
    if(state == SLEEPING)
        tmp.append("SLEEPING... sleeping points\t->\t\t"+to_string(sleepingPoints)+"\t"+to_string(eatCntr));
    else if(state == WAITING)
        tmp.append("WAITING... sleeping points\t->\t\t"+to_string(sleepingPoints)+"\t"+to_string(eatCntr));
    else if(state == EATING)
        tmp.append("EATING... eating points\t\t->\t"+to_string(eatingPoints)+"\t\t"+to_string(eatCntr));

    return tmp;
}

bool Philosopher::isForksFree()
{
    return forks.first->isUnlocked() && forks.second->isUnlocked();
}

bool Philosopher::isFull()
{
    return (++eatingPoints == eatingPointsMax) ? 
    true:false;
}

bool Philosopher::isHungry()
{
    return (++sleepingPoints == sleepingPointsMax)  ? 
    true:false;
}

bool Philosopher::isEating()
{
    return (state==EATING) ? true:false;
}

void Philosopher::updateClockRate()
{
    int left = 0.8*CLOCK_RATE;
    int right= 1.2*CLOCK_RATE;
    int random = rand() % (right-left) + left;
    this->clockRate = random;
}

void Philosopher::start()
{
    this->thr = thread(&Philosopher::run, this);
}

Philosopher::~Philosopher()
{
    
}
