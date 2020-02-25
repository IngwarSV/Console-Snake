#ifndef SPECIFICATIONS_H
#define SPECIFICATIONS_H


const int WIDTH = 40;
const int HEIGHT = 20;

const int OBSTACLES_RATIO = 100;

const int INIT_DELAY = 100;

const int ROUND_DELAY = 1;

const int FRUITS_PER_ROUND = 5;

const int SNAKE_MAX_SIZE = 100;

const int MAX_ROUNDS = 3;

const char TOP_SCORE_PATH[] = "topFive.txt";

const int PLAYER_NAME_LENGTH = 11;

const int TOP_SCORE_AMOUNT = 5;

const char SNAKE_HEAD = 'O';
const char SNAKE_BODY = 'o';
const char SNAKE_TAIL_END_HORIZ = '-';
const char SNAKE_TAIL_END_VERT = '|';

const char FRUIT_FORM = '$';

const char OBSTACLE_FORM = 'x';



const int RIGHT_EDGE = WIDTH - 1;
const int BOTTOM_EDGE = HEIGHT - 1;

const int LEFT_START = 1;
const int RIGHT_START = WIDTH - 2;
const int TOP_START = 1;
const int BOTTOM_START = HEIGHT - 2;

#endif // SPECIFICATIONS_H

