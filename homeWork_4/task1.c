// Реализовать программу 1-го практического задания с помощью биномиального коэффициента.
// Данные на вход: Два целых числа N и M
// Данные на выход: Одно целое число – количество вариантов

#include <stdio.h>

int binom(int n, int k) {
    const int maxn = n;
    int C[maxn + 1][maxn + 1];
    for (int i = 0; i <= maxn; ++i)
    {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; ++j)
        {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }
    return C[n][k];
}

int main(int argc, char const *argv[])
{
    int n, m;
    scanf("%d %d", &n, &m);
    printf("%d", binom(n, m));
    return 0;
}
