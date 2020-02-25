#pragma once

#include <iostream>
#include <stdlib.h>
#include <iomanip> // td::setfill(' ') << std::setw(WIDTH)
#include <time.h>
#include <conio.h> // _kbhit(), _getch()
#include <windows.h>
#include <chrono> // std::chrono::seconds(_)
#include <thread> // std::this_thread::sleep_for
#include <fstream>

#include "Specifications.h"
#include "Snake.h"
#include "Coord.h"
#include "Result.h"

class Game {
private:
    bool gameOver;
    Snake snake;
    Coord fruit;
    char fruitForm;
    char obstacleForm;
    Coord delta;
    float score;
    int roundCounter;
    int fruitCounter;
    float gameDuration;
    clock_t time1;
    clock_t time2;

    std::vector<Coord> obstaclesList;
    Result topNScore[TOP_SCORE_AMOUNT];


    void setup();

    void obstacleCreation();

    void fruitCreation();

    void startMenu();

    void stageMenu();

    void drawMap();

    void input();

    void logic();

    bool checkIntoObstacle(const Coord& coord);

    void endMenu1();

    void readTop();

    void writeTop();
    
    void showTopTable();

    void endGame();

    void endMenu2();

public:
    Game();
    ~Game() = default;

    void gameLoop();
};

int compareResults(const void* first, const void* second); // for qsort();