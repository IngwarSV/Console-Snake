#include "Result.h"

Result::Result() {
	this->snakeLength = 0;
	this->gameTime = 0;
	this->score = 0;
	this->date = static_cast<time_t>(0);
}

void Result::toString(char* buffer, int size) {
	int minutes = static_cast<int>(this->gameTime / 60);
	int seconds = static_cast<int>(this->gameTime - minutes * 60);
	char dateBuffer[30];
	ctime_s(dateBuffer, 30, &this->date);

	sprintf_s(buffer, size, "  %-12s %-6d %3d : %-3d  %-9.2g %-40s", this->name, this->snakeLength, minutes, seconds, this->score, dateBuffer);
}

std::ostream& operator<< (std::ostream& out, const Result& result) {
	out 
		<< result.snakeLength << ' ' 
		<< result.gameTime << ' ' 
		<< result.score << ' ' 
		<< result.date << ' ' 
		<< result.name << '\n';

	return out;
}

std::istream& operator>> (std::istream& in, Result& result) {
	in
		>> result.snakeLength
		>> result.gameTime
		>> result.score
		>> result.date;
		in.ignore();
		in.getline(result.name, PLAYER_NAME_LENGTH);

	return in;
}