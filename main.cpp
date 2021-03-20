#include <iostream>
#include <vector>
#include <cursesapp.h>
#include "philosopher/Philosopher.h"

using namespace std;

void checkExit(bool &running)
{
    while (getch() != 'q');
    running = false;
}

int main()
{
    int N = 5;
    Fork f1, f2;
    vector<Philosopher*> philosophers(N);

    // create philosophers, start their threads
//    for (int i = 0; i < N; ++i)
//    {
//        philosophers[i] = new Philosopher(f1,f2);
//        philosophers[i]->start();
//    }

    bool running = true;
    std::thread exit(checkExit, ref(running));

    while (running)
    {

    }
    exit.join();
    return 0;
}
