#include <stdio.h>
#include <string.h>

#define max(a, b) (((a) > (b)) ? (a) : (b))

enum{maxlength = 10001};

int search_prefix(char*, char*);

int main ()
{
    char    str1[maxlength],
            str2[maxlength];
    scanf("%s", str1);
    scanf("%s", str2);

    int res1 = search_prefix(str2, str1);
    int res2 = search_prefix(str1, str2);
    // printf("%d\n", max(res1, res2));
    return 0;
}

int search_prefix(char* str1, char* str2)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    int counter = 0;

    int l = (len1 < len2) ? len1 : len2;
    int i1, i2, max = 0;
    char c1, c2;
    for (i1 = len1 - l; i1 < len1; i1++)
    {
        counter++;
        for (i2 = 0; i2 < len2; i2++)
        {
            counter++;
            c1 = str1[i1 + i2];
            c2 = str2[i2];
            if (c1 != c2 )
                break;
        }
        if (str1[len1 - 1] == str2[i2 - 1] && i2 > max)
        {
            max = i2;
        }
    }
    printf("%d\n", counter);
    return max;
}