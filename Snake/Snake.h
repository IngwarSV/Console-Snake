#pragma once

#include <iostream>
#include <vector>

#include "Specifications.h"
#include "Coord.h"

class Snake {
private:
    int snakeLength;
    std::vector<Coord> reptileBody;
    char headForm;
    char bodyForm;
    char tailEndForm_Horiz;
    char tailEndForm_Vert;
         
public:
    Snake(int x = WIDTH / 2, int y = HEIGHT / 2);
    ~Snake();

    bool tailBite;

    int getSnakeLength() const;

    char getHeadForm() const;

    char getBodyForm() const;

    char getTailEndForm() const;

    Coord& getSnakeCoord(int index);

    bool checkIntoSnake(const Coord& coord);

    void move(const Coord& delta);

    void eat(Coord victim);

    void reset();

};
