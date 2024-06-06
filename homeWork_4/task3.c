// Реализовать программу 3-го практического задания более эффективным
// способом со сложностью О(n) (см. код в лекции).

/*
    КОММЕНТАРИЙ ОТ МЕНЯ
    данное задаие ввело меня в ступор, не понял как его делать
    переписал просто готовый код, но все равно не работает
*/

#include <stdio.h>
#include <string.h>

#define SIZE 10001

int min(int a, int b)
{
    return (a < b) ? a : b;
}

void zFunction2(char* s, int z[])
{
    int n = strlen(s);
    for (int i = 1, l = 0, r = 0; i < n; ++i)
    {
        if (i <= r)
        {
            z[i] = min(r - i + 1, z[i - 1]);
        }

        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
        {
            ++z;
        }

        if (i + z[i] - 1 > r)
        {
            l = i;
            r = i + z[i] - 1;
        }
    }
}

int max(int z[], int n)
{
    int max = 0;
    for (size_t i = 0; i < n; i++)
    {
        if (z[i] > max)
        {
            max = z[i];
        }
    }
    return max;
}

int searchPrefix(char* s1, char* s2)
{
    char s[SIZE + SIZE] = {0};
    int z[SIZE + SIZE] = {0};
    size_t s1len = strlen(s1);
    size_t s2len = strlen(s2);
    sprintf(s, "%s#%s", s2, s1);
    zFunction2(s, z);
    return max(z + s2len, s1len);
}

int main(int argc, char const *argv[])
{
    char s1[SIZE] = {0};
    char s2[SIZE] = {0};

    scanf("%10001s", s1);
    scanf("%10001s", s2);
    
    printf("%d\n", searchPrefix(s2, s1));

    return 0;
}
