// На стандартном потоке ввода задается натуральное число N (N > 0), после
// которого следует последовательность из N целых чисел.
// На стандартный поток вывода напечатайте, сколько раз в этой
// последовательности встречается максимум.

#include <stdio.h>

int main(int argc, char const *argv[])
{

    int n, input;
    int max = 0, counter = 0;

    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf(" %d", &input);

        if (input > max)
        {
            max = input;
            counter = 1;
        }
        else if (input == max)
        {
            counter++;
        }
    }

    printf("%d", counter);
    
    return 0;
}
