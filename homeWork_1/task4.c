// На стандартном потоке ввода задается целое неотрицательное число N и
// последовательность допустимых символов в кодировке ASCII,
// оканчивающаяся точкой. Допустимые символы – латинские буквы 'a' ... 'z', 'A' ...
// 'Z' и пробел. Требуется закодировать латинские буквы ('a' ... 'z', 'A' ... 'Z')
// шифром Цезаря, пробелы вывести без изменения. Число N задает сдвиг в
// шифре. Шифр Цезаря заключается в следующем преобразовании. Пусть буквы
// алфавита пронумерованы от 0 до K - 1, где K - число символов в алфавите.
// Тогда символ с номером n кодируется символом с номером p = (n + N) mod K
// (mod - операция взятия остатка). На стандартном потоке вывода напечатать
// зашифрованное сообщение, оканчивающееся точкой. Преобразование
// требуется выполнять независимо для заглавных и строчных латинских букв.

#include <stdio.h>

#define K 26

typedef unsigned int uint;

char shiftCapitalLetter(uint N, char c)
{
    uint n = c - 'A';
    uint p = (n + N) % K;
    return (char)('A' + p);
}

char shiftSmallLetter(uint N, char c)
{
    uint n = c - 'a';
    uint p = (n + N) % K;
    return (char)('a' + p);
}

int main(int argc, char const *argv[])
{
    uint shift;
    char c;

    scanf("%d ", &shift);

    while (c != '.')
    {
        c = getchar();
        if (c >= 'A' && c <= 'Z')
        {
            c = shiftCapitalLetter(shift, c);
        }
        else if (c >= 'a' && c <= 'z')
        {
            c = shiftSmallLetter(shift, c);
        }
        printf("%c", c);
    }

    return 0;
}