// На вход программе подается беззнаковое 32-битное целое число N. Требуется
// изменить значения всех битов старшего байта числа на противоположные и
// вывести полученное таким образом число.

#include <stdio.h>
#include <stdint.h>

int main(int argc, char const *argv[])
{
    uint32_t n;
    scanf("%u", &n);

    uint32_t mask = (~0) << (8 * (sizeof(uint32_t) - 1));
    uint32_t temp = n & (~mask);

    n = ~n;
    n &= mask;
    n |= temp;

    printf("%u", n);
    
    return 0;
}

