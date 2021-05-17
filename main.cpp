#include <ncurses.h>
#include <thread>
#include <vector>
#include <chrono>
#include <string>

#include "philosopher/Philosopher.h"
#include "fork/Fork.h"

using namespace std;

// functions' definitions
void initNcurses();
void initMessages(int);
void checkExit(bool &);
void updateScreen(bool &, vector<Philosopher*> &);

// variables
int N = 5;

int main()
{
    initNcurses();

    // allocate memory for vectors of pointer objects
    vector<Philosopher*> philosophers(N);
    vector<Fork*> forks(N);

    // create forks
    for (int i = 0; i < N; i++)     forks[i] = new Fork();
    
    // create philosophers & assign their forks
    // Solution using the resource hierarchy (last philosopher has to grab his right fork firstly)
    for (int i = 0; i < N-1; i++)   philosophers[i] = new Philosopher(forks[i],forks[i+1]);
    philosophers[N-1] = new Philosopher(forks[0], forks[N-1]);
    
    // handle exit on (press 'q'), screen updating
    bool running = true;
    std::thread threadExit(checkExit, std::ref(running));
    std::thread threadScreen(updateScreen, std::ref(running), std::ref(philosophers));

    // run threads
    for (int i = 0; i < N; i++)     philosophers[i]->start();
    
    // join threads    
    threadExit.join();
    threadScreen.join();

    // join philosopher threads (automatic free all mutexes)
    for (int i = 0; i < N; i++)     philosophers[i]->kill();

    // clear memory
    for (int i = 0; i < N; i++)     delete philosophers[i];
    for (int i = 0; i < N; i++)     delete forks[i];

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

void updateScreen(bool &running, vector<Philosopher*> &pV)
{
    while(running)
    {
        clear();
        int rows = 4;
        int cols = 4;
        // display headers

        attron(COLOR_PAIR(3));
        mvprintw(2, 48, "%s", "EAT %\tSLEEP %\tCNTR");
        attroff(COLOR_PAIR(3));
        for (int i = 0; i < N; i++,rows+=4)
        {
            int color = -1;
            // color for eating philosophers
            if(pV[i]->isEating())   color = 4;
            else                    color = 0;
            attron(COLOR_PAIR(color));
            //display
            mvprintw(rows, cols, "%s", pV[i]->getInfo().c_str());
            attroff(COLOR_PAIR(color));
        }

        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
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