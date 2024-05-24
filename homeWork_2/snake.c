#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define MAX_X 30
#define MAX_Y 15

#define SLEEP_TIME_MS 200

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
    tail_t * tail;
    size_t tsize;
    command_t currentCommand;
}snake_t;

// @**
snake_t initSnake(int x, int y, size_t tsize)
{
    snake_t snake;
    snake.x = x;
    snake.y = y;
    snake.tsize = tsize;
    snake.tail = (tail_t*)malloc(sizeof(tail_t) * 100);
    for (int i = 0; i < tsize; i++)
    {
        snake.tail[i].x = x + i + 1;
        snake.tail[i].y = y;
    }
    snake.currentCommand = LEFT;
    return snake;
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

void printSnake(snake_t snake)
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
    }
}

int main(int argc, char const *argv[])
{
    snake_t snake = initSnake(10, 5, 5);
    printSnake(snake);
    char command;

    while (1)
    {
        if (kbhit())
        {
            command = getch();
            if (command == 'q' || command == 'Q')
            {
                return 0;
            }
            setCommand(command, &snake);
        }
        moveSnake(&snake);
        Sleep(SLEEP_TIME_MS);
        system("cls");
        printSnake(snake);
    }

    return 0;
}
