// Написать алгоритм перевода из инфиксной записи в обратную польскую.
// Для его реализации нужны данные по приоритетам операций.
// Реализовать алгоритм, используя побитовые операции (&, |, ^).

#include <stdio.h>

void normToPolish(char* input, char* output)
{

}

int main(int argc, char const *argv[])
{
    char str[100];
    char polish[100] = {0};
    scanf("%[^\n]s", str);
    normToPolish(str, polish);
    printf("%s", polish);
    return 0;
}
