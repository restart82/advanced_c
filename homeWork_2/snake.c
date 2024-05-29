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
    int delay;
    tail_t * tail;
    size_t tsize;
    command_t currentCommand;
    bool growing;
    bool pause;
}snake_t;

typedef struct
{
    int x;
    int y;
    unsigned int randSeed;
}food_t;

// @**
snake_t initSnake(int x, int y, size_t tsize)
{
    snake_t snake;
    snake.x = x;
    snake.y = y;
    snake.pointCounter = 0;
    snake.delay = SLEEP_TIME_MS;
    snake.tsize = tsize;
    snake.tail = (tail_t*)malloc(sizeof(tail_t) * 100);
    for (int i = 0; i < tsize; i++)
    {
        snake.tail[i].x = x + i + 1;
        snake.tail[i].y = y;
    }
    snake.currentCommand = LEFT;
    snake.growing = false;
    snake.pause = false;
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

void printSnake(snake_t snake, food_t* food)
{
    char matrix[MAX_X][MAX_Y];
    for (int i = 0; i < MAX_X; i++)
    {
        for (int j = 0; j < MAX_Y; j++)
        {
            matrix[i][j] = ' ';
        }
    }

    matrix[snake.x][snake.y] = '@';
    for (int i = 0; i < snake.tsize; i++)
    {
        matrix[snake.tail[i].x][snake.tail[i].y] = '*';
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
    float speed = 1. / snake.delay * 1000;
    printf("\tpoints:\t%d\n", snake.pointCounter);
    printf("\tspeed:\t%.2f\n", speed);
    (snake.pause) ? printf("\tpause ON\n") : printf("\n");
    

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

void setCommand(char command, snake_t* snake)
{
    switch (command)
    {
    case 'w':
    case 'W':
        if (snake->currentCommand != DOWN)
        {
            snake->currentCommand = UP;
        }
        break;
    case 'd':
    case 'D':
        if (snake->currentCommand != LEFT)
        {
            snake->currentCommand = RIGHT;
        }
        break;
    case 's':
    case 'S':
        if (snake->currentCommand != UP)
        {
            snake->currentCommand = DOWN;
        }
        break;
    case 'a':
    case 'A':
        if (snake->currentCommand != RIGHT)
        {
            snake->currentCommand = LEFT;
        }
        break;
    case 'p':
    case 'P':
        snake->pause = !snake->pause;
        break;
    }
}

void levelUp(snake_t* snake)
{
    if (snake->delay > 50)
    {
        snake->delay -= 50;
    }
}

void eatFood(snake_t* snake, food_t* food)
{
    for (int i = 0; i < NUMBER_OF_FOOD; i++)
    {
        if (snake->x == food[i].x && snake->y == food[i].y)
        {
            snake->pointCounter++;
            snake->growing = true;
            setNewFood(food, i);
            levelUp(snake);
        }
    }
}

void snakeGrow(snake_t* snake)
{
    static int growCounter = 0;
    growCounter++;
    if (growCounter == snake->tsize)
    {
        snake->tsize++;
        snake->tail[snake->tsize].x = snake->tail[snake->tsize - 1].x;
        snake->tail[snake->tsize].y = snake->tail[snake->tsize - 1].y;
        growCounter == 0;
        snake->growing = false;
    }
}



int main(int argc, char const *argv[])
{
    snake_t snake = initSnake(10, 5, 2);
    food_t food[NUMBER_OF_FOOD];
    initFood(food);
    printSnake(snake, food);
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
            setCommand(command, &snake);
        }
        if (!snake.pause)
        {
            eatFood(&snake, food);
            if (snake.growing)
            {
                snakeGrow(&snake);
            }
            moveSnake(&snake);
        }
        Sleep(snake.delay);
        system("cls");
        printSnake(snake, food);
    }
    system("cls");
    printf("\tyour score: %d", snake.pointCounter);

    return 0;
}
