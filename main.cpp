#include <ncurses.h>
#include <thread>
#include <vector>
#include <chrono>

#include "philosopher/Philosopher.h"
#include "fork/Fork.h"

using namespace std;

// functions' definitions
void initNcurses();
void initMessages(int);
void checkExit(bool &);
void updateScreen(bool &, const vector<Philosopher*> &);


//variables
int N = 5;

int main()
{
    initNcurses();
    initMessages(0);    // 0 is color ID

    // allocate memory for vectors of pointer objects
    vector<Philosopher*> philosophers(N);
    vector<Fork*> forks(N);

    // create forks
    for (int i = 0; i < N; i++)     forks[i] = new Fork();
    
    // create philosophers
    for (int i = 0; i < N; i++)     philosophers[i] = new Philosopher(forks[i],forks[(i+1)%N]);
    
    // handle exit on (press 'q'), screen updating
    bool running = true;
    std::thread updaterExit(checkExit, std::ref(running));
    std::thread updaterScreen(updateScreen, std::ref(running), std::ref(philosophers));

    // run threads
    for (int i = 0; i < N; i++)     philosophers[i]->start();
    
    // join threads
    updaterExit.join();
    updaterScreen.join();

    // quit ncurses
    endwin();

    // quit program
    return 0;
}

void checkExit(bool &running)
{
    while (getch() != 'q');

    running = false;
}

void updateScreen(bool &running, const vector<Philosopher*> &pV)
{
    while(running)
    {
        clear();
        int rows = 4;
        int cols = 4;
        for (int i = 0; i < N; i++,rows++)
        {
            attron(COLOR_PAIR(i)); mvprintw(rows, cols, "philosopher (%d) has value %d", pV[i]->getId(), pV[i]->getVal());
        }
        
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void initNcurses()
{
    initscr();
    noecho();
    start_color();
    init_pair(0, COLOR_YELLOW, COLOR_BLACK);
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
}

void initMessages(int color)
{
    //welcome message
    attron(COLOR_PAIR(color)); printw("--Dinning Philosophers problem--\n");
}