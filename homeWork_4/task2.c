// Написать алгоритм перевода из инфиксной записи в обратную польскую.
// Для его реализации нужны данные по приоритетам операций.
// Реализовать алгоритм, используя побитовые операции (&, |, ^).

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUFFER_SIZE 255
#define STACK_SIZE 255

char oper[STACK_SIZE] = {0};
int oend = 0;

void push(char v)
{
    oper[oend++] = v;
}

char pop()
{
    if (oend <= 0 || oend >= BUFFER_SIZE)
    {
        fprintf(stderr, "Stack overflow\n");
        exit(1);
    }
    return oper[--oend];
}

bool emptyStack()
{
    return (oend == 0);
}

bool isDigit(char c) // проверяем является ли символ цифрой
{
    return ((c >= '0') && (c <= '9'));
}

bool isOperator(char c)
{
    return  (c == '+') ||
            (c == '-') ||
            (c == '*') ||
            (c == '/');
}

int priority(char c)
{
    if (c == '+' || c == '-')
    {
        return 1;
    }
    if (c == '*' || c == '/')
    {
        return 2;
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    char c;
    int pos = 0;

    char answer[BUFFER_SIZE] = {0};
    printf("Input infix string: ");
    char str[1000];
    int len = 0;
    while ((c = getchar()) != '\n')
    {
        str[len++] = c;
    }
    str[len] = '\0';

    for (int i = 0; i < len; i++)
    {
        if (isDigit(str[i]))
        {
            int number,
                size = 0;
            for (number = 0; isDigit(str[i]); i++, size++)
            {
                number = number * 10 + str[i] - '0';
            }
            sprintf(answer + pos, "%d ", number);
            pos += size + 1;
        }
        else
        {
            if (i >= len)
            {
                break;
            }
            c = str[i];
            if (isOperator(c))
            {
                while (!emptyStack())
                {
                    char top = pop();
                    if (priority(top) >= priority(c))
                    {
                        sprintf(answer + pos, "%c ", top);
                        pos += 2;
                    }
                    else
                    {
                        push(top);
                        break;
                    }
                }
                push(c);
            }
            else if (c == '(')
            {
                push(c);
            }
            else if (c == ')')
            {
                while ((c = pop()) != '(')
                {
                    sprintf(answer + pos, "%c ", c);
                    pos += 2;
                }
                
            }
        }
    }
    while (!emptyStack())
    {
        sprintf(answer + pos, "%c ", pop());
        pos += 2;
    }
    printf("Answer: %s\n", answer);
    
    return 0;
}

