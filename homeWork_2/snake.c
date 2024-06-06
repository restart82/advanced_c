#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>

#define MAX_X           30
#define MAX_Y           15
#define SLEEP_TIME_MS   300
#define NUMBER_OF_FOOD  3

typedef enum
{
    UP,
    DOWN,
    LEFT,
    RIGHT
}command_t;

typedef struct
{
    int x;
    int y;
}tail_t;

typedef struct
{
    int x;
    int y;
    int pointCounter;
    tail_t * tail;
    size_t tsize;
    command_t currentCommand;
    bool growing;
    int growCounter;
}snake_t;

typedef struct
{
    int x;
    int y;
    unsigned int randSeed;
}food_t;

typedef struct
{
    bool pause;
    int delay;
}game_t;

// @**
snake_t initSnake(int x, int y, size_t tsize)
{
    snake_t snake;
    snake.x = x;
    snake.y = y;
    snake.pointCounter = 0;
    snake.tsize = tsize;
    snake.tail = (tail_t*)malloc(sizeof(tail_t) * 100);
    for (int i = 0; i < tsize; i++)
    {
        snake.tail[i].x = x + i + 1;
        snake.tail[i].y = y;
    }
    snake.currentCommand = LEFT;
    snake.growing = false;
    snake.growCounter = 0;
    return snake;
}

int getRandNumber(int bound, int seed)
{
    srand(seed);
    int result = rand() % (bound + 1);
    return result;
}

void initFood(food_t* food)
{
    for (int i = 0; i < NUMBER_OF_FOOD; i++)
    {
        food[i].randSeed = (int)time(NULL) + i;
        food[i].x = getRandNumber(MAX_X, food[i].randSeed);
        food[i].y = getRandNumber(MAX_Y, food[i].randSeed);
    }
}

void setNewFood(food_t* food, int number)
{
    food[number].randSeed = (int)time(NULL);
    food[number].x = getRandNumber(MAX_X, food[number].randSeed);
    food[number].y = getRandNumber(MAX_Y, food[number].randSeed);
}

void printLine()
{
    printf(".");
    for (int i = 0; i < MAX_X; i++)
    {
        printf("_");
    }
    printf(".\n");
}

void view(snake_t snake_1, snake_t snake_2, food_t* food, game_t game)
{
    char matrix[MAX_X][MAX_Y];
    for (int i = 0; i < MAX_X; i++)
    {
        for (int j = 0; j < MAX_Y; j++)
        {
            matrix[i][j] = ' ';
        }
    }

    matrix[snake_1.x][snake_1.y] = '@';
    for (int i = 0; i < snake_1.tsize; i++)
    {
        matrix[snake_1.tail[i].x][snake_1.tail[i].y] = '*';
    }

    matrix[snake_2.x][snake_2.y] = 'Q';
    for (int i = 0; i < snake_2.tsize; i++)
    {
        matrix[snake_2.tail[i].x][snake_2.tail[i].y] = '*';
    }

    for (int i = 0; i < NUMBER_OF_FOOD; i++)
    {
        matrix[food[i].x][food[i].y] = 'o';
    }

    printLine();
    for (int j = 0; j < MAX_Y; j++)
    {
        printf("|");
        for (int i = 0; i < MAX_X; i++)
        {
            printf("%c", matrix[i][j]);
        }
        printf("|\n");
    }
    printLine();
    float speed = 1. / game.delay * 1000;
    printf("\t1-st snake points:  %d\n", snake_1.pointCounter);
    printf("\t2-nd snake points:  %d\n", snake_2.pointCounter);
    printf("\tspeed:\t%.2f\n", speed);
    game.pause ? printf("\tpause ON\n") : printf("\n");
    

}

void moveSnake(snake_t* snake)
{
    for (int i = snake->tsize - 1; i > 0; i--)
    {
        snake->tail[i] = snake->tail[i - 1];
    }
    snake->tail[0].x = snake->x;
    snake->tail[0].y = snake->y;

    switch (snake->currentCommand)
    {
    case UP:
        snake->y = snake->y - 1;
        if (snake->y < 0)
        {
            snake->y = MAX_Y - 1;
        }
        break;
    case DOWN:
        snake->y = snake->y + 1;
        if (snake->y >= MAX_Y)
        {
            snake->y = 0;
        }
        break;
    case LEFT:
        snake->x = snake->x - 1;
        if (snake->x < 0)
        {
            snake->x = MAX_X - 1;
        }
        break;
    case RIGHT:
        snake->x = snake->x + 1;
        if (snake->x >= MAX_X)
        {
            snake->x = 0;
        }
        break;
    }
}

void setCommand(char command, snake_t* snake_1, snake_t* snake_2)
{
    switch (command)
    {
    case 'w':
    case 'W':
        if (snake_1->currentCommand != DOWN)
        {
            snake_1->currentCommand = UP;
        }
        break;
    case 'd':
    case 'D':
        if (snake_1->currentCommand != LEFT)
        {
            snake_1->currentCommand = RIGHT;
        }
        break;
    case 's':
    case 'S':
        if (snake_1->currentCommand != UP)
        {
            snake_1->currentCommand = DOWN;
        }
        break;
    case 'a':
    case 'A':
        if (snake_1->currentCommand != RIGHT)
        {
            snake_1->currentCommand = LEFT;
        }
        break;
    case 'i':
    case 'I':
        if (snake_2->currentCommand != DOWN)
        {
            snake_2->currentCommand = UP;
        }
        break;
    case 'l':
    case 'L':
        if (snake_2->currentCommand != LEFT)
        {
            snake_2->currentCommand = RIGHT;
        }
        break;
    case 'k':
    case 'K':
        if (snake_2->currentCommand != UP)
        {
            snake_2->currentCommand = DOWN;
        }
        break;
    case 'j':
    case 'J':
        if (snake_2->currentCommand != RIGHT)
        {
            snake_2->currentCommand = LEFT;
        }
        break;
    }
}

void levelUp(game_t* game)
{
    if (game->delay > 50)
    {
        game->delay -= 25;
    }
}

void eatFood(snake_t* snake, food_t* food, game_t* game)
{
    for (int i = 0; i < NUMBER_OF_FOOD; i++)
    {
        if (snake->x == food[i].x && snake->y == food[i].y)
        {
            snake->pointCounter++;
            snake->growing = true;
            setNewFood(food, i);
            levelUp(game);
        }
    }
}

void snakeGrow(snake_t* snake)
{
    snake->growCounter++;
    if (snake->currentCommand == snake->tsize)
    {
        snake->tsize++;
        snake->tail[snake->tsize].x = snake->tail[snake->tsize - 1].x;
        snake->tail[snake->tsize].y = snake->tail[snake->tsize - 1].y;
        snake->growCounter == 0;
        snake->growing = false;
    }
}



int main(int argc, char const *argv[])
{
    game_t game;
    game.delay = SLEEP_TIME_MS;
    game.pause = false;
    snake_t snake = initSnake(10, 5, 2);
    snake_t secondSnake = initSnake(10, 10, 2);
    food_t food[NUMBER_OF_FOOD];
    initFood(food);
    view(snake, secondSnake, food, game);
    char command;

    while (1)
    {
        if (kbhit())
        {
            command = getch();
            if (command == 'q' || command == 'Q')
            {
                break;
            }
            if (command == 'p'|| command == 'P')
            {
                game.pause = !game.pause;
            }
            setCommand(command, &snake, &secondSnake);
        }

        if (!game.pause)
        {
            eatFood(&snake, food, &game);
            eatFood(&secondSnake, food, &game);
            if (snake.growing)
            {
                snakeGrow(&snake);
            }
            if (secondSnake.growing)
            {
                snakeGrow(&secondSnake);
            }
            moveSnake(&snake);
            moveSnake(&secondSnake);
        }

        Sleep(game.delay);
        system("cls");
        view(snake, secondSnake, food, game);
    }
    system("cls");
    printf("\n");
    printf("\t1-st snake score: %d\n", snake.pointCounter);
    printf("\t2-nd snake score: %d\n", secondSnake.pointCounter);

    return 0;
}
