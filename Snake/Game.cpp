#include "Game.h"

Game::Game() {
    this->gameOver = false;
    this->snake = Snake();
    this->fruit = Coord();
    this->fruitForm = FRUIT_FORM;
    this->obstacleForm = OBSTACLE_FORM;
    this->score = 0;
    this->roundCounter = 0;
    this->gameDuration = 0;
    this->obstaclesList = std::vector<Coord>();
    
    for (int i = 0; i < TOP_SCORE_AMOUNT; ++i) {
        topNScore[i] = Result();
    }
    
    srand(static_cast<size_t>(time(NULL)));
}

void Game::setup() {
    this->snake.reset();
    this->obstacleCreation();
    this->fruitCreation();
    this->fruitCounter = FRUITS_PER_ROUND;
    this->roundCounter += 1;
    this->delta = Coord(0, 0);
}

void Game::obstacleCreation() {
    int obstacleAmount = this->roundCounter * WIDTH * HEIGHT / OBSTACLES_RATIO;
    Coord initSnakeCoord1 = Coord();
    Coord initSnakeCoord2 = Coord(WIDTH / 2, HEIGHT / 2 + 1);
    
    for (int i = 0; i < obstacleAmount; ++i) {
        Coord obstacleCoord = Coord(rand() % (WIDTH - 3) + 1, rand() % (HEIGHT - 3) + 1);

        if (obstacleCoord != initSnakeCoord1 && obstacleCoord != initSnakeCoord2) {
            this->obstaclesList.push_back(obstacleCoord);
        }
    }
}

void Game::fruitCreation() {
    Coord newFruit;
    bool fruitIsCreated = false;

    Coord DELTA_UP = Coord(0, -1);
    Coord DELTA_DOWN = Coord(0, 1);
    Coord DELTA_LEFT = Coord(-1, 0);
    Coord DELTA_RIGHT = Coord(1, 0);

    while (!fruitIsCreated) {
        newFruit.x = rand() % (WIDTH - 3) + 1;
        newFruit.y = rand() % (HEIGHT - 3) + 1;

        if (snake.checkIntoSnake(newFruit)) {
            continue;
        }

        if (this->checkIntoObstacle(newFruit)) {
            continue;
        }

        int freeAxcessToFruit = 4;
        
        if (this->checkIntoObstacle(newFruit + DELTA_UP)) {
            freeAxcessToFruit -= 1;
        }
        if (this->checkIntoObstacle(newFruit + DELTA_DOWN)) {
            freeAxcessToFruit -= 1;
        }
        if (this->checkIntoObstacle(newFruit + DELTA_LEFT)) {
            freeAxcessToFruit -= 1;
        }
        if (this->checkIntoObstacle(newFruit + DELTA_RIGHT)) {
            freeAxcessToFruit -= 1;
        }

        if (freeAxcessToFruit < 2) {
            continue;
        }

        fruitIsCreated = true;
    }
    this->fruit = newFruit;
}

void Game::startMenu() {
    std::cout << std::setfill('#') << std::setw(WIDTH) << '#' << std::endl;

    for (int i = 1, j = HEIGHT / 2 - 3; i < j; ++i) {
        std::cout << '#' << std::setfill(' ') << std::setw(WIDTH - 1) << '#' << std::endl;
    }

    std::cout << '#';
    std::cout.width(WIDTH / 2 + 11);
    std::cout << "\\\\ G A M E  S N A K E //";
    std::cout.width(WIDTH / 2 - 12);
    std::cout << "#" << std::endl;

    for (int i = 1, j = HEIGHT / 2 - 2; i < j; ++i) {
        std::cout << '#' << std::setw(WIDTH - 1) << '#' << std::endl;
    }

    std::cout << '#' << std::setw(WIDTH / 2 + 5) << "loading...";
    std::cout << std::setw(WIDTH / 2 - 6) << "#" << std::endl;

    std::cout << '#' << std::setw(WIDTH - 1) << '#' << std::endl;

    std::cout << '#' << std::setw(WIDTH / 2 + 9) << " 2 0 2 0   K Y I V ";
    std::cout << std::setw(WIDTH / 2 - 10) << "#" << std::endl;

    for (int i = 1, j = HEIGHT / 2 - 8; i < j; ++i) {
        std::cout << '#' << std::setw(WIDTH - 1) << '#' << std::endl;
    }

    std::cout << std::setfill('#') << std::setw(WIDTH) << '#' << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(ROUND_DELAY));
}

void Game::stageMenu() {
    system("cls");

    while (_kbhit()) {
            _getch();
    }

    std::cout << std::setfill('#') << std::setw(WIDTH) << '#' << std::endl;

    for (int i = 1, j = HEIGHT / 2 - 3; i < j; ++i) {
        std::cout << '#' << std::setfill(' ') << std::setw(WIDTH - 1) << '#' << std::endl;
    }

    std::cout << '#';
    std::cout.width(WIDTH / 2 + 11);
    std::cout << "\\\\ G A M E  S N A K E //";
    std::cout.width(WIDTH / 2 - 12);
    std::cout << "#" << std::endl;

    std::cout << '#' << std::setw(WIDTH - 1) << '#' << std::endl;

    std::cout << '#';
    std::cout.width(WIDTH / 2 + 5);
    std::cout << "R O U N D  ";
    std::cout.width(WIDTH / 2 - 7);
    std::cout << std::left << this->roundCounter;
    std::cout << std::right << "#" << std::endl;

    std::cout << '#' << std::setw(WIDTH - 1) << '#' << std::endl;

    std::cout << '#';
    std::cout.width(WIDTH / 2 + 10);
    std::cout << "Y O U R  S C O R E : ";
    std::cout.width(WIDTH / 2 - 12);
    std::cout << std::left << this->score;
    std::cout << std::right << "#" << std::endl;

    for (int i = 1, j = HEIGHT / 2 - 5; i < j; ++i) {
        std::cout << '#' << std::setw(WIDTH - 1) << '#' << std::endl;
    }

    std::cout << '#' << std::setw(WIDTH / 2 + 10) << "press ANY KEY to start";
    std::cout << std::setw(WIDTH / 2 - 11) << "#" << std::endl;

    for (int i = 1, j = HEIGHT / 2 - 7; i < j; ++i) {
        std::cout << '#' << std::setw(WIDTH - 1) << '#' << std::endl;
    }

    std::cout << std::setfill('#') << std::setw(WIDTH) << '#' << std::endl;

    if (this->roundCounter == 1) {
        this->time1 = clock();
        this->time2 = clock();
    }

    _getch();
}

void Game::drawMap() {
    system("cls");

    std::cout << std::setfill('#') << std::setw(WIDTH) << '#' << std::endl;

    for (int i = 1; i < BOTTOM_EDGE; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (j == 0 || j == RIGHT_EDGE) {
                std::cout << '#';
                continue;
            }
            if (i == fruit.y && j == fruit.x) {
                std::cout << this->fruitForm;
                continue;
            }
            if (i == snake.getSnakeCoord(0).y && j == snake.getSnakeCoord(0).x) {
                std::cout << snake.getHeadForm();
                continue;
            }
            else {
                bool flag = false;
                size_t k = 1;
                
                for (size_t l = snake.getSnakeLength() - 1; k < l; ++k) {
                    if (j == snake.getSnakeCoord(k).x && i == snake.getSnakeCoord(k).y) {
                        std::cout << snake.getBodyForm();
                        flag = true;
                        break;
                    }
                }
                if (snake.getSnakeLength() > 1 && !flag) {
                    if (j == snake.getSnakeCoord(k).x && i == snake.getSnakeCoord(k).y) {
                        std::cout << snake.getTailEndForm();
                        continue;
                    }
                }
                if (!flag) {
                    for (k = 0; k < this->obstaclesList.size(); ++k) {
                        if (j == this->obstaclesList[k].x && i == this->obstaclesList[k].y) {
                            std::cout << this->obstacleForm;
                            flag = true;
                            break;
                        }
                    }
                }
                if (!flag) {
                    std::cout << ' ';
                }
            }
        }
        std::cout << std::endl;
    }

    std::cout << std::setfill('#') << std::setw(WIDTH) << '#' << std::endl;

    std::cout << std::endl;

    clock_t tempTime = clock();
    this->gameDuration += static_cast<float>(tempTime - this->time1) / CLOCKS_PER_SEC;
    this->time1 = tempTime;

    std::cout << "Score: " << std::setprecision(2) << std::fixed << this->score << "\tLength: " << snake.getSnakeLength();
    std::cout << "\tDuration: " << std::setprecision(2) << std::fixed << this->gameDuration << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(INIT_DELAY));
}

void Game::input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a':
                this->delta = Coord(-1, 0);
                break;
            case 'w':
                this->delta = Coord(0, -1);
                break;
            case 'd':
                this->delta = Coord(1, 0);
                break;
            case 's':
                this->delta = Coord(0, 1);
                break;
            case 'x':
                gameOver = true;
                break;
        }
    }
}

void Game::logic() {
    snake.move(delta);
            
    if (snake.getSnakeCoord(0).x == 0) {
        snake.getSnakeCoord(0).x = RIGHT_START;
    }
    else if (snake.getSnakeCoord(0).x == RIGHT_EDGE) {
        snake.getSnakeCoord(0).x = LEFT_START;
    }

    if (snake.getSnakeCoord(0).y == 0) {
        snake.getSnakeCoord(0).y = BOTTOM_START;
    }
    else if (snake.getSnakeCoord(0).y == BOTTOM_EDGE) {
        snake.getSnakeCoord(0).y = TOP_START;
    }

    if (snake.tailBite) {
        this->gameOver = true;
        return;
    }
            
    if (this->fruit == snake.getSnakeCoord(0)) {
        clock_t tempTime = clock();
        clock_t temp = (tempTime - this->time2) / CLOCKS_PER_SEC;
        this->time2 = tempTime;

        score += static_cast<float>(snake.getSnakeLength()) / temp;
        
        if (this->roundCounter != MAX_ROUNDS) {
            this->fruitCounter -= 1;
        }

        this->snake.eat(this->fruit);
        this->fruitCreation();

        this->time1 = clock();
        return;
    }

    if (this->checkIntoObstacle(snake.getSnakeCoord(0))) {
        this->gameOver = true;
    }
}

bool Game::checkIntoObstacle(const Coord& coord) {
    for (Coord var : this->obstaclesList) {
        if (coord == var) {
            return true;
        }
    }
    return false;
}

void Game::endMenu1() {
    system("cls");

    while (_kbhit()) {
        _getch();
    }

    std::cout << std::setfill('#') << std::setw(WIDTH) << '#' << std::endl;

    for (int i = 1, j = HEIGHT / 2 - 3; i < j; ++i) {
        std::cout << '#' << std::setfill(' ') << std::setw(WIDTH - 1) << '#' << std::endl;
    }

    std::cout << '#';
    std::cout.width(WIDTH / 2 + 11);
    std::cout << "\\\\ G A M E  O V E R //";
    std::cout.width(WIDTH / 2 - 12);
    std::cout << "#" << std::endl;

    std::cout << '#' << std::setw(WIDTH - 1) << '#' << std::endl;

    std::cout << '#';
    std::cout.width(WIDTH / 2 + 10);
    std::cout << "Y O U R  S C O R E : ";
    std::cout.width(WIDTH / 2 - 12);
    std::cout << std::left << this->score;
    std::cout << std::right << "#" << std::endl;

    for (int i = 1, j = HEIGHT / 2 - 3; i < j; ++i) {
        std::cout << '#' << std::setw(WIDTH - 1) << '#' << std::endl;
    }

    std::cout << '#' << std::setw(WIDTH / 2 + 10) << "press ANY KEY to start";
    std::cout << std::setw(WIDTH / 2 - 11) << "#" << std::endl;

    for (int i = 1, j = HEIGHT / 2 - 7; i < j; ++i) {
        std::cout << '#' << std::setw(WIDTH - 1) << '#' << std::endl;
    }

    std::cout << std::setfill('#') << std::setw(WIDTH) << '#' << std::setfill(' ') << std::endl;

    _getch();
}

void Game::readTop() {
    std::ifstream fin(TOP_SCORE_PATH);
    
    if (fin) {
        for (int i = 0; i < TOP_SCORE_AMOUNT && !fin.eof(); ++i) {
            fin >> this->topNScore[i];
        }
    }
    fin.close();
}

void Game::writeTop() {
    std::ofstream fout(TOP_SCORE_PATH);

    if (fout) {
        for (int i = 0; i < TOP_SCORE_AMOUNT; ++i) {
            fout << this->topNScore[i] << "\n";
        }
    }
    fout.close();
}

void Game::showTopTable() {
    system("cls");
   
    std::cout << "\n" << std::setw(WIDTH / 2 + 10) << "\\\\ TOP " << TOP_SCORE_AMOUNT << " SCORES //\n" << '\n';

    std::cout << std::setw(WIDTH) << "  NAME:        Length: Duration: Score:    Date:\n" << '\n';

    char tempBuffer[100];

    for (int i = 0; i < TOP_SCORE_AMOUNT; ++i) {
        this->topNScore[i].toString(tempBuffer, 100);
        std::cout << tempBuffer << '\n';
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));

    _getch();
}

void Game::endGame() {
    std::cout << '\n' << std::setw(WIDTH + 4) << "\\\\ Y O U R  R E S U L T //" << '\n';

    char tempBuffer[100];
    int minutes = static_cast<int>(this->gameDuration / 60);
    int seconds = static_cast<int>(this->gameDuration - minutes * 60);
    time_t date = time(NULL);
    char dateBuffer[30];

    ctime_s(dateBuffer, 30, &date);

    sprintf_s(tempBuffer, 100, "\n  %-12s %-6d %3d : %-3d  %-9.2g %-40s\n", "Player", this->snake.getSnakeLength(), minutes, seconds, this->score, dateBuffer);

    std::cout << tempBuffer << '\n';

    if (this->score > this->topNScore[TOP_SCORE_AMOUNT - 1].score) {
        
        this->topNScore[TOP_SCORE_AMOUNT - 1].snakeLength = this->snake.getSnakeLength();
        this->topNScore[TOP_SCORE_AMOUNT - 1].gameTime = this->gameDuration;
        this->topNScore[TOP_SCORE_AMOUNT - 1].score = this->score;
        this->topNScore[TOP_SCORE_AMOUNT - 1].date = date;

        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::cout << "Enter yor name (max 10 symbols): ";

        std::cin >> std::ws;

        char playerName[PLAYER_NAME_LENGTH + 1];

        std::cin.getline(playerName, PLAYER_NAME_LENGTH + 1);

        strcpy_s(this->topNScore[TOP_SCORE_AMOUNT - 1].name, playerName);

        qsort(this->topNScore, TOP_SCORE_AMOUNT, sizeof(Result), compareResults);

        this->showTopTable();
    }


}

void Game::endMenu2() {
    system("cls");

    while (_kbhit()) {
        _getch();
    }

    std::cout << std::setfill('#') << std::setw(WIDTH) << '#' << std::endl;

    for (int i = 1, j = HEIGHT / 2 - 3; i < j; ++i) {
        std::cout << '#' << std::setfill(' ') << std::setw(WIDTH - 1) << '#' << std::endl;
    }

    std::cout << '#';
    std::cout.width(WIDTH / 2 + 11);
    std::cout << "\\\\ C O N T I N U E //";
    std::cout.width(WIDTH / 2 - 12);
    std::cout << "#" << std::endl;

    std::cout << '#' << std::setw(WIDTH - 1) << '#' << std::endl;

    std::cout << '#' << std::setw(WIDTH / 2 + 7) << "y e s  /  n o  ?";
    std::cout << std::setw(WIDTH / 2 - 8) << "#" << std::endl;

    for (int i = 1, j = HEIGHT / 2 + 1; i < j; ++i) {
        std::cout << '#' << std::setw(WIDTH - 1) << '#' << std::endl;
    }
    
    std::cout << std::setfill('#') << std::setw(WIDTH) << '#' << std::setfill(' ') << std::endl;

    bool flag = true;

    while (flag) {
        switch (_getch()) {
        case 'y':
            system("cls");
            this->gameOver = false;
            this->score = 0;
            this->roundCounter = 0;
            this->gameDuration = 0;
            this->obstaclesList.clear();
            this->gameLoop();
            flag = false;
            break;
        case 'n':
            flag = false;
            break;
        }
    }
  
}

void Game::gameLoop() {
    this->startMenu();
  
    while (!this->gameOver) {
        this->setup();
        this->stageMenu();

        while (!this->gameOver && this->fruitCounter) {
            this->drawMap();
            this->input();
            this->logic();
        }
    }
    
    this->endMenu1();
    this->readTop();
    this->showTopTable();
    this->endGame();
    this->writeTop();
    this->endMenu2();
}

int compareResults(const void* first, const void* second) {
    const Result* op1 = static_cast<const Result*>(first);
    const Result* op2 = static_cast<const Result*>(second);
    return static_cast<int>(op2->score - op1->score);
}

