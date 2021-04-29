# MultiThreading1
C++ project for educational purposes - multithreading in C++ - dining philosophers. 

Student: Miron Oskroba
year, semester: III, 6
Course: Operating Systems 2

# Introduction
The dining philosophers problem is invented by E. W. Dijkstra. Imagine that five philosophers who spend their lives just thinking and easting. In the middle of the dining room is a circular table with five chairs. The table has a big plate of spaghetti. However, there are only five chopsticks available, as shown in the following figure. Each philosopher thinks. When he gets hungry, he sits down and picks up the two chopsticks that are closest to him. If a philosopher can pick up both chopsticks, he eats for a while. After a philosopher finishes eating, he puts down the chopsticks and starts to think.

## Project environment settings
- Linux Ubuntu 20.04
- VS Code with a bunch of handy extensions
- g++ compiler
- ncurses library for better visualisation
- In order to build binary executable file **properly**, there is a need to set appropriate flags *on the end* of compiling command(take a look at file tasks.json):
  - /usr/bin/g++ -g ${file} -o ${fileDirname}/${fileBasenameNoExtension} **-pthread -lncurses**


# Step 1 - learn ncurses
#include<ncurses.h> is used in order to have a nicer look of final product of implementation.

![Alt text](/readme-files/readme-ncurses.png?raw=true "learning ncurses")
