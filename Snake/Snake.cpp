#include "Snake.h"

Snake::Snake(int x, int y) {
    this->snakeLength = 1;
    this->reptileBody = std::vector<Coord>();
    this->reptileBody.reserve(SNAKE_MAX_SIZE);
    this->reptileBody.push_back(Coord(x, y));
    this->headForm = SNAKE_HEAD;
    this->bodyForm = SNAKE_BODY;
    this->tailEndForm_Horiz = SNAKE_TAIL_END_HORIZ;
    this->tailEndForm_Vert = SNAKE_TAIL_END_VERT;
    this->tailBite = false;
}

Snake::~Snake() = default;

int Snake::getSnakeLength() const {
    return this->snakeLength;
}

char Snake::getHeadForm() const {
    return this->headForm;
}

char Snake::getBodyForm() const {
    return this->bodyForm;
}

char Snake::getTailEndForm() const {
    if (reptileBody[snakeLength - 2].y == reptileBody[snakeLength-1].y) {
        return this->tailEndForm_Horiz;
    }
    else {
        return this->tailEndForm_Vert;
    }
}

Coord& Snake::getSnakeCoord(int index) {
    return this->reptileBody.at(index);
}

bool Snake::checkIntoSnake(const Coord& coord) {
    for (Coord var : this->reptileBody) {
        if (coord == var) {
            return true;
        }
    }
    return false;
}

void Snake::move(const Coord& delta) {
    Coord snakeHead = this->reptileBody[0] + delta;

    for (int i = this->snakeLength - 1; i > 0; --i) {
        this->reptileBody[i] = this->reptileBody[i - 1];
        if (snakeHead == this->reptileBody[i]) {
            this->tailBite = true;
        }
    }
    this->reptileBody[0] += delta;
}

void Snake::eat(Coord victim) {
    this->snakeLength += 1;
    this->reptileBody.push_back(victim);
}

void Snake::reset() {
    this->snakeLength = 1;
    this->reptileBody.clear();
    this->reptileBody.reserve(SNAKE_MAX_SIZE);
    this->reptileBody.push_back(Coord());
    this->tailBite = false;
}

