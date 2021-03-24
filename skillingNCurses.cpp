#include<ncurses.h>
#include<thread>
#include<string.h>

#define NUMBER_OF_COLORS 9

void checkExit(bool &running)
{
    while(getch() != 'q');
    running = false;
}

void spawnRectUp(int row, int col)
{

}

void printRainbowText(int row, int col, char *txt)
{
    int it = 0;
    char c = txt[it];
    do
    {
        c = txt[it++];
        attron(COLOR_PAIR((it+rand() % 10)%NUMBER_OF_COLORS));
        mvprintw(row, col++, "%c", c);
        
    }while(c != '\0');

}

void appendIntToFront(char *dst, int x, int dstSize)
{
    char c = char(x+48); // to char
    char txt[] = {c, ' ', '-', '-','>',' '};
    int N = sizeof(txt);
    memmove(&dst[N], dst, dstSize);
    memcpy(&dst[0], txt, N);
}

int main()
{
    srand(time_t(NULL));
    initscr();
    noecho();
    start_color();
    init_pair(0, COLOR_YELLOW, COLOR_BLACK);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    init_pair(6, COLOR_WHITE, COLOR_BLACK);
    init_pair(7, COLOR_YELLOW, COLOR_BLACK);
    init_pair(8, COLOR_RED, COLOR_BLACK);

    const int SIZE = 30;
    char menuItem[][SIZE] = {{"menu 1 itemeeek ;PPP!"},
                                    {"Pusc kwadrata ;ppp!"},
                                    {"wyjdz...... :("},
                                    {"aaaaaaa"},
                                    {"bbbbbb"},
                                    {"ccccccc"},
                                    {"ddddddd"},
                                    {"!!!!!!!!!!!!!!!!!!! H"},
                                    {"#fFFFFFFFFFFFF"},
                                    {"#AARGRERAGH"},
                                    {"#AERGRAWEGH"},
                                    {"#ERHERH"},
                                    {"#fFFFFFFFFFFFF"},
                                    {"#@#^&@#&"},
                                    {"#)(*&^%"},
                                    {"#jytT"}
                                    };

    int amountOfMenuItems = sizeof(menuItem)/sizeof(*menuItem);

    int rows=0, cols=0;
    getmaxyx(stdscr, rows, cols);

    rows = rows/2 - amountOfMenuItems/2;
    cols = cols/2;
    for (size_t i = 0; i < amountOfMenuItems; i++)
    {
        char tmp[SIZE];
        memcpy(tmp, menuItem[i], SIZE);

        appendIntToFront(tmp, i, sizeof(menuItem[i]));
        
        printRainbowText(rows, cols-sizeof(menuItem[i])/2, tmp);
        rows++;

    }
    
    bool running = true;
    std::thread thr(checkExit, std::ref(running));

    thr.join();
    endwin();
    return 0;  
}

