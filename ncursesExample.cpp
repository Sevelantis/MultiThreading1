#include <ncurses.h>
#include <thread>

int cols = 0;
int rows = 0;

char str[] = "EXaMpLe TeStTTTSS LaTeX!!11@@$%";

void checkExit(bool &running)
{
    while(getch() != 'q');
    running = false;
}

int main()
{
    initscr(); //1
    noecho();
    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);

    getmaxyx(stdscr, rows, cols);
    attron(COLOR_PAIR(2)); printw("rows: %d", rows);
    attron(COLOR_PAIR(3)); printw("cols: %d", cols);
    attron(COLOR_PAIR(1)); printw("size: %d", sizeof(str));

    attron(COLOR_PAIR(4)); mvprintw(rows/2, (cols-sizeof(str))/2, str);

    // thread
    bool running = true;
    std::thread thr(checkExit, std::ref(running));
    thr.join();
    endwin(); //4
    return 0;
}