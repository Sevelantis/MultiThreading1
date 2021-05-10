//
// Created by oskro on 14 mar 2021.
//
#include <chrono>
#include "Philosopher.h"

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
                forks.first->lock(id);
                forks.second->lock(id);
                state = EATING;
                sleepingPoints=0;
            }
        }
        else if (state==EATING)
        {
            if(isFull())
            {
                forks.first->unlock();
                forks.second->unlock();
                state = SLEEPING;
                eatingPoints = 0;
                eatCntr++;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}

Philosopher::Philosopher(Fork *f1, Fork *f2)
{
    this->id = idCntr++;
    this->forks.first = f1;
    this->forks.second = f2;
    this->state = SLEEPING;
}

void Philosopher::kill()
{
    feast = false;
    thr.join();
}

int Philosopher::getId()
{
    return id;
}

int Philosopher::getEatingPoints()
{
    return eatingPoints;
}

int Philosopher::getSleepingPoints()
{
    return sleepingPoints;
}

std::pair<int,int> Philosopher::getForksIds()
{
    return make_pair(forks.first->getId(), forks.second->getId());
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

void Philosopher::start()
{
    this->thr = thread(&Philosopher::run, this);
}

Philosopher::~Philosopher()
{
    
}
