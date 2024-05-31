#include <stdio.h>
#include <stdbool.h>

typedef int datatype;

void push(datatype v); // используется для вычислений
datatype pop(void);
bool isEmpty(void); // определяет пустой ли стек st
void operate(char c); // вычисляем два верхних значения на стеке st

#define MAX_STACK_SIZE 255

datatype st[MAX_STACK_SIZE]; // стэк
int pst = 0; // заполненность стэа

void push(datatype v) // используется для вычислений
{
    st[pst++] = v;
}

datatype pop()
{
    if (pst <= 0)
    {
        fprintf(stderr, "Error. Stack underflow");
        return 1;
    }
    else if (pst > MAX_STACK_SIZE)
    {
        fprintf(stderr, "Error. Stack overflow");
        return 1;
    }
    return st[--pst]; // уменьшаем количество на единицу, а затем возвращаем значение
}

bool isEmpty() // определяет пустой ли стек st
{
    return (pst <= 0);
}

void operate(char c) // вычисляем два верхних значения на стеке st
{
    datatype    arg1 = pop(),
                arg2 = pop();

    switch (c)
    {
    case '+':
        push(arg1 + arg2);
        break;
    case '-':
        push(arg2 - arg1);
        break;
    case '*':
        push(arg1 * arg2);
        break;
    case '/':
        push(arg2 / arg1);
        break;
    }

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

int main(int argc, char const *argv[])
{
    char c;
    printf("Input infix string: ");
    char str[1000];
    int len = 0;
    while ((c = getchar()) != '\n')
    {
        str[len++] = c;
    }
    str[len] = '\0';
    // printf("%s\n", str);

    for (int i = 0; i < len; i++)
    {
        if(isDigit(str[i]))
        {
            datatype number;
            for (number = 0; isDigit(str[i]); i++)
            {
                number = number * 10 + str[i] - '0';
            }
            push(number);
        }
        else
        {
            if (i >= len)
            {
                break;
            }

            if (isOperator(str[i]))
            {
                operate(str[i]);
            }
        }
    }

    printf("answer = %d\n", pop());

    return 0;
}
