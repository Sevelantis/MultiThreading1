#include <ncurses.h>
#include <vector>

#include "philosopher/Philosopher.h"
#include "fork/Fork.h"

using namespace std;

void checkExit(bool &running)
{
    while (getch() != 'q');

    running = false;
}

int main()
{
    initscr();
    noecho();
    start_color();
    init_pair(0, COLOR_YELLOW, COLOR_BLACK);
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK);

    int N = 5;
    vector<Philosopher*> philosophers(N);
    vector<Fork*> forks(N);

    // create forks
    for (int i = 0; i < N; ++i)
    {
        forks[i] = new Fork();
    }

    // create philosophers, run their threads
    for (int i = 0; i < N; ++i)
    {
        philosophers[i] = new Philosopher(forks[i],forks[(i+1)%(N-1)]);
        // philosophers[i]->start();
    }

//     bool running = true;
//     std::thread exit(checkExit, std::ref(running));

//     while (running)
//     {

//     }
//     exit.join();

    endwin();
    return 0;
}
