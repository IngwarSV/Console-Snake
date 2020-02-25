#pragma once

#include<iostream>
#include <time.h>

#include "Specifications.h"

class Result {
public:
	char name[PLAYER_NAME_LENGTH+1] = "Noname";
	int snakeLength;
	float gameTime;
	float score;
	time_t date;

	Result();
	~Result() = default;

	void toString(char* buffer, int size = WIDTH);

};

std::ostream& operator<< (std::ostream& out, const Result& result);
std::istream& operator>> (std::istream& in, Result& result);

